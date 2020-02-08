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
    
public:
    static Direct3DManager& Instance();

    float GetWindowAspect() const {
        if (m_uHeight != 0) {
            return static_cast<float>(m_uWidth) / static_cast<float>(m_uHeight);
        } else {
            return 0.0f;
        }
    }

    ID3D11DeviceContext* GetDeviceContext() const { return m_pDeviceContext; }
    ID3D11Device* GetDevice() const { return m_pDevice; }

    HWND GetHWND() const { return m_hWND; }

    bool Initialize(HINSTANCE hInstance, UINT uWidth, UINT uHeight, bool bEnable4xMsaa);
    void StartWindow(int nShowCmd);
    void Update();
    void _Render();

    void SetVertexShader(std::shared_ptr<VertexShaderBase> pVertexShader);
    void SetPixelShader(std::shared_ptr<PixelShaderBase> pPixelShader);

    std::shared_ptr<VertexShaderBase> GetVertexShader() const { return m_pVertexShader; }
    std::shared_ptr<PixelShaderBase> GetPixelShader() const { return m_pPixelShader; }

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

    bool DrawObjectWithEffect(ID3D11Buffer* pVertexBuffer, ID3D11Buffer* pIndexedBuffer, UINT nStride, UINT nIndexCount);
    bool DrawObjectWithShader(
        ID3D11Buffer* pVertexBuffer,
        ID3D11Buffer* pIndexedBuffer,
        UINT nStride,
        UINT nIndexCount);

    bool CreateTexture(std::wstring_view strvFilePath, ID3D11ShaderResourceView*& pResourceView, ID3D11Resource*& pTexture);

    void ApplyTexture(std::shared_ptr<Texture> pTexture);

    ApplicationState GetApplicationState() const {
        return m_eState;
    }
};

#endif // !_H_DIRECT3D_MANAGER_
