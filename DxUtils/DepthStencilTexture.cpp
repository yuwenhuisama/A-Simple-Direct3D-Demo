#include "DepthStencilTexture.h"
#include "DxUtils/D3DHelper.hpp"
#include "DxUtils/Direct3DManager.h"
#include "DirectXTex.h"

#include "GameUtils/GameConfigure.h"

DepthStencilTexture::~DepthStencilTexture() {
    this->_Release();
}

bool DepthStencilTexture::_InitializeDepthStencilTexture() {
    D3D11_TEXTURE2D_DESC t2ddDepthBufferDesc;
    memset(&t2ddDepthBufferDesc, 0, sizeof(D3D11_TEXTURE2D_DESC));
    t2ddDepthBufferDesc.Width = GameConfigure::Instance().GetLightConfigure().m_i2ShadowMapTextureSize.x;
    t2ddDepthBufferDesc.Height = GameConfigure::Instance().GetLightConfigure().m_i2ShadowMapTextureSize.y;
    t2ddDepthBufferDesc.MipLevels = 1;
    t2ddDepthBufferDesc.ArraySize = 1;
    t2ddDepthBufferDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
    t2ddDepthBufferDesc.SampleDesc.Count = 1;
    t2ddDepthBufferDesc.SampleDesc.Quality = 0;
    t2ddDepthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    t2ddDepthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
    t2ddDepthBufferDesc.CPUAccessFlags = 0;
    t2ddDepthBufferDesc.MiscFlags = 0;

    return Direct3DManager::Instance().CreateDepthStencilTexture(t2ddDepthBufferDesc, m_pDepthStencilTexture);
}

bool DepthStencilTexture::_InitialzieDepthStencilView() {
    D3D11_DEPTH_STENCIL_VIEW_DESC ddsvdDepthStencilViewDesc;
    memset(&ddsvdDepthStencilViewDesc, 0, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
    ddsvdDepthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    ddsvdDepthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    ddsvdDepthStencilViewDesc.Texture2D.MipSlice = 0;

    return Direct3DManager::Instance().CreateDepthStencilView(ddsvdDepthStencilViewDesc, m_pDepthStencilTexture, m_pDepthStencilView);
}

bool DepthStencilTexture::_InitializeShaderResourceView() {
    D3D11_SHADER_RESOURCE_VIEW_DESC srvdShaderResourceViewDesc;
    memset(&srvdShaderResourceViewDesc, 0, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
    srvdShaderResourceViewDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
    srvdShaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvdShaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
    srvdShaderResourceViewDesc.Texture1D.MipLevels = 1;

    return Direct3DManager::Instance().CreateShaderResourceView(srvdShaderResourceViewDesc, m_pDepthStencilTexture, m_pShaderResourceView);
}

bool DepthStencilTexture::Initialize() {
    if (!this->_InitializeDepthStencilTexture()) {
        goto failed_exit;
    }

    if (!this->_InitialzieDepthStencilView()) {
        goto failed_exit;
    }

    if (!this->_InitializeShaderResourceView()) {
        goto failed_exit;
    }

    m_vViewPort.Width = static_cast<float>(GameConfigure::Instance().GetLightConfigure().m_i2ShadowMapTextureSize.x);
    m_vViewPort.Height = static_cast<float>(GameConfigure::Instance().GetLightConfigure().m_i2ShadowMapTextureSize.y);
    m_vViewPort.MinDepth = 0.0f;
    m_vViewPort.MaxDepth = 1.0f;
    m_vViewPort.TopLeftX = 0.0f;
    m_vViewPort.TopLeftY = 0.0f;

    return true;
failed_exit:
    assert(false);
    return false;
}

void DepthStencilTexture::_Release() {
    D3DHelper::SafeRelease(m_pDepthStencilTexture);
    D3DHelper::SafeRelease(m_pDepthStencilView);
    D3DHelper::SafeRelease(m_pShaderResourceView);
}

bool DepthStencilTexture::SaveToFile(std::wstring_view wstrvFile) {
    DirectX::ScratchImage siImage;
    auto result = DirectX::CaptureTexture(
        Direct3DManager::Instance().GetDevice(),
        Direct3DManager::Instance().GetDeviceContext(),
        m_pDepthStencilTexture,
        siImage
    );

    if (FAILED(result)) {
        return false;
    }

    result = DirectX::SaveToWICFile(
        *siImage.GetImages(),
        DirectX::WIC_FLAGS_NONE,
        GUID_ContainerFormatBmp,
        wstrvFile.data(),
        &GUID_WICPixelFormat32bppBGRA);

    if (FAILED(result)) {
        return false;
    }

    return true;
}

