#include "Texture.h"
#include "DxUtils/Direct3DManager.h"
#include "DxUtils/D3DHelper.hpp"

bool Texture::Load(std::wstring_view wstrFilePath) {
    auto result = Direct3DManager::Instance().CreateTexture(wstrFilePath, m_pResourceView, m_pTexture);
    assert(result == true);
    return result;
}

bool Texture::LoadCube(std::wstring_view wstrFilePath) {
    auto result = Direct3DManager::Instance().CreateCubeTexture(wstrFilePath, m_pResourceView, m_pTexture);
    assert(result == true);
    return result;
}

Texture::~Texture() {
    D3DHelper::SafeRelease(m_pResourceView);
    D3DHelper::SafeRelease(m_pTexture);
}
