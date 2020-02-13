#ifndef _H_DEPTHTEXTURE_
#define _H_DEPTHTEXTURE_

#include <d3d11.h>
#include <string>

class DepthStencilTexture final {
private:
    ID3D11ShaderResourceView* m_pShaderResourceView = nullptr;
    ID3D11Texture2D* m_pDepthStencilTexture = nullptr;
    ID3D11DepthStencilView* m_pDepthStencilView = nullptr;
    D3D11_VIEWPORT m_vViewPort;

private:
    bool _InitializeDepthStencilTexture();
    bool _InitialzieDepthStencilView();
    bool _InitializeShaderResourceView();

    void _Release();

public:
    DepthStencilTexture() = default;
    ~DepthStencilTexture();

    bool Initialize();

    ID3D11ShaderResourceView* GetShaderResourceView() const { return m_pShaderResourceView; }
    ID3D11Texture2D* GetDepthStencilTexture() const { return m_pDepthStencilTexture; }
    ID3D11DepthStencilView* GetDpethStencilView() const { return m_pDepthStencilView; }
    const D3D11_VIEWPORT& GetViewport() const { return m_vViewPort; }

    bool SaveToFile(std::wstring_view wstrvFile);
};

#endif // !_H_DEPTHTEXTURE_
