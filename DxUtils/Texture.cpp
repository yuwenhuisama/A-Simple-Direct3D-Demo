#include "Texture.h"
#include "DxUtils/Direct3DManager.h"
#include "DxUtils/D3DHelper.hpp"

bool Texture::Load(std::wstring& wstrFilePath) {
    return Direct3DManager::Instance().CreateTexture(wstrFilePath, m_pResourceView, m_pTexture);
}

Texture::~Texture() {
    D3DHelper::SafeRelease(m_pResourceView);
    D3DHelper::SafeRelease(m_pTexture);
}
