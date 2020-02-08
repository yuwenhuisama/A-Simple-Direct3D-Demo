#include "VertexShaderBase.h"
#include "DxUtils/D3DHelper.hpp"
#include "DxUtils/Direct3DManager.h"

VertexShaderBase::VertexShaderBase() : ShaderBase() {}

VertexShaderBase::~VertexShaderBase() {
    D3DHelper::SafeRelease(this->m_pVertexShader);
    D3DHelper::SafeRelease(this->m_pInputLayout);
}

bool VertexShaderBase::CreateShader(ID3DBlob* pBlob) {
    auto result = Direct3DManager::Instance().CreateVertexShader(pBlob, m_pVertexShader);
    if (!result) {
        return false;
    }

    result = Direct3DManager::Instance().CreateInputLayout(
        this->GetInputLayoutDescArray(),
        this->GetInputLayoutDescArraySize(),
        pBlob,
        m_pInputLayout);

    if (!result) {
        return false;
    }

    return true;
}
