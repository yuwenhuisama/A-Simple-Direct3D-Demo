#include "PixelShaderBase.h"
#include "DxUtils/D3DHelper.hpp"
#include "DxUtils/Direct3DManager.h"

PixelShaderBase::PixelShaderBase(): ShaderBase() {}

PixelShaderBase::~PixelShaderBase() {
    D3DHelper::SafeRelease(this->m_pPixelShader);
}

bool PixelShaderBase::CreateShader(ID3DBlob* pBlob) {
    return Direct3DManager::Instance().CreatePixelShader(pBlob, m_pPixelShader);
}
