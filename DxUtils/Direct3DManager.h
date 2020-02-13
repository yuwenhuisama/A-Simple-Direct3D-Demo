#ifndef _H_DIRECT3D_MANAGER_
#define _H_DIRECT3D_MANAGER_

#include <Windows.h>
#include <d3d11.h>
#include <D3DCompiler.h>
#include <DirectXMath.h>
#include <dxgi1_2.h>
#include <wincodec.h>
#include <wrl.h>
#include <dwrite_3.h>
#include "DxUtils/Shaders/PixelShaderBase.h"
#include "DxUtils/Shaders/VertexShaderBase.h"
#include "DxUtils/Shaders/ShadowMapVertexShader.h"
#include "DxUtils/Shaders/ShadowMapPixelShader.h"
#include "DxUtils/DepthStencilTexture.h"

#include "DxUtils/D3DHelper.hpp"

#include "DxUtils/Texture.h"

#include <string>
#include <memory>

enum class ApplicationState {
    Pending = 0,
    Running,
    Quite
};

class Direct3DManager {
private:
    ID3D11Device* m_pDevice = nullptr;
    ID3D11DeviceContext* m_pDeviceContext = nullptr;
    IDXGISwapChain* m_pSwapChain = nullptr;

    ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
    ID3D11DepthStencilView* m_pDepthStencilView = nullptr;

    ID3D11Texture2D* m_pDepthStencilBuffer = nullptr;
    ID3D11SamplerState* m_pColorMapSampler = nullptr;

    HWND m_hWND = nullptr;
    HINSTANCE m_hInstance = nullptr;

    ApplicationState m_eState = ApplicationState::Pending;

    std::shared_ptr<VertexShaderBase> m_pVertexShader = nullptr;
    std::shared_ptr<PixelShaderBase> m_pPixelShader = nullptr;

    std::shared_ptr<VertexShaderBase> m_pShadowMapVertexShader = std::make_shared<ShadowMapVertexShader>();
    std::shared_ptr<PixelShaderBase> m_pShadowMapPixelShader = std::make_shared<ShadowMapPixelShader>();

    std::unique_ptr<DepthStencilTexture> m_pDepthStencilTexture = std::make_unique<DepthStencilTexture>();

    bool m_bIsRenderShadowMap = false;

    UINT m_uWidth = 0;
    UINT m_uHeight = 0;

private:
    Direct3DManager() = default;
    ~Direct3DManager() = default;

    bool _InitSamplerState();
    bool _InitSwapChain(UINT uWidth, UINT uHeight, bool bEnable4xMsaa);
    bool _InitRenderTargetView();
    bool _InitDepthStencilView(UINT uWidth, UINT uHeight, bool bEnable4xMsaa);
    bool _InitWindow(HINSTANCE hInstance, UINT uWidth, UINT uHeight);

    static LRESULT _WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
    
    void _SetFrontCounterClockwise(bool bState);
    void _SetStencilStateCmpFunc(D3D11_COMPARISON_FUNC eCmpFunc);

public:
    static Direct3DManager& Instance();

    float GetWindowAspect() const {
        if (m_uHeight != 0) {
            return static_cast<float>(m_uWidth) / static_cast<float>(m_uHeight);
        } else {
            return 0.0f;
        }
    }

    UINT GetWindowWidth() const { return m_uWidth; }
    UINT GetWindowHeight() const { return m_uHeight; }

    void SetIsRenderShadowMap(bool bIsRenderShadowMap) {
        m_bIsRenderShadowMap = bIsRenderShadowMap;

        if (bIsRenderShadowMap) {
            ID3D11RenderTargetView* pRenderTargetView[] = { 0 };
            m_pDeviceContext->OMSetRenderTargets(1, pRenderTargetView, m_pDepthStencilTexture->GetDpethStencilView());
            m_pDeviceContext->RSSetViewports(1, &m_pDepthStencilTexture->GetViewport());
        } else {
            m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
            D3D11_VIEWPORT vpViewport;
            vpViewport.TopLeftX = 0;
            vpViewport.TopLeftY = 0;
            vpViewport.Width = static_cast<float>(m_uWidth);
            vpViewport.Height = static_cast<float>(m_uHeight);
            vpViewport.MinDepth = 0.0f;
            vpViewport.MaxDepth = 1.0f;

            m_pDeviceContext->RSSetViewports(1, &vpViewport);
        }
    }
    bool IsRenderShadowMap() const { return m_bIsRenderShadowMap; }

    ID3D11DeviceContext* GetDeviceContext() const { return m_pDeviceContext; }
    ID3D11Device* GetDevice() const { return m_pDevice; }

    HWND GetHWND() const { return m_hWND; }

    bool Initialize(HINSTANCE hInstance, UINT uWidth, UINT uHeight, bool bEnable4xMsaa);
    void StartWindow(int nShowCmd);
    void Update();
    void _Render();

    void SetVertexShader(std::shared_ptr<VertexShaderBase> pVertexShader) { m_pVertexShader = pVertexShader; }
    void SetPixelShader(std::shared_ptr<PixelShaderBase> pPixelShader) { m_pPixelShader = pPixelShader; }

    std::shared_ptr<VertexShaderBase> GetVertexShader() const {
        if (m_bIsRenderShadowMap) {
            return m_pShadowMapVertexShader;
        } else {
            return m_pVertexShader;
        }
    }

    std::shared_ptr<PixelShaderBase> GetPixelShader() const {
        if (m_bIsRenderShadowMap) {
            return m_pShadowMapPixelShader;
        } else {
            return m_pPixelShader;
        }
     }

    void ClearColorBuffer();
    void Direct3DManager::ClearDepthStencilBuffer();

    bool CreateBuffer(const D3D11_BUFFER_DESC& dscBufferDesc,
        const D3D11_SUBRESOURCE_DATA& ssInitData,
        ID3D11Buffer*& pBuffer);
    bool CreateBuffer(const D3D11_BUFFER_DESC& dscBufferDesc,
        ID3D11Buffer*& pBuffer);

    bool CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* vcInputLayoutDescArr,
        UINT uDescArrSize,
        ID3DBlob* pBuffer,
        ID3D11InputLayout*& pInputLayout);

    bool CreatePixelShader(ID3DBlob* pBlob, ID3D11PixelShader*& pPixelShader);
    bool CreateVertexShader(ID3DBlob* pBlob, ID3D11VertexShader*& pVertexShader);

    bool DrawObjectWithShader(
        ID3D11Buffer* pVertexBuffer,
        ID3D11Buffer* pIndexedBuffer,
        UINT nStride,
        UINT nIndexCount);

    bool DrawSkyBoxWithShader(
        ID3D11Buffer* pVertexBuffer,
        ID3D11Buffer* pIndexedBuffer,
        UINT nStride,
        UINT nIndexCount,
        std::shared_ptr<VertexShaderBase> pVertexShader,
        std::shared_ptr<PixelShaderBase> pPixelShader
    );

    bool CreateTexture(std::wstring_view strvFilePath, ID3D11ShaderResourceView*& pResourceView, ID3D11Texture2D*& pTexture);
    bool CreateCubeTexture(std::wstring_view strvFilePath, ID3D11ShaderResourceView*& pResourceView, ID3D11Texture2D*& pTexture);

    bool CreateDepthStencilTexture(const D3D11_TEXTURE2D_DESC& d2ddDesc, ID3D11Texture2D*& pTexture);
    bool CreateDepthStencilView(const D3D11_DEPTH_STENCIL_VIEW_DESC ddsvdDepthStencilViewDesc,
        ID3D11Texture2D* pDepthStencilTexture,
        ID3D11DepthStencilView*& pDepthStencilView);
    bool CreateShaderResourceView(const D3D11_SHADER_RESOURCE_VIEW_DESC& dsrvdShaderResourceViewDesc,
        ID3D11Texture2D* pTexture,
        ID3D11ShaderResourceView*& pResourceView);

    void ApplyTexture(std::shared_ptr<Texture> pTexture);
    void ApplyShadowMapTexture();

    ApplicationState GetApplicationState() const {
        return m_eState;
    }
};

#endif // !_H_DIRECT3D_MANAGER_
