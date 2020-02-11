#include "ShaderBase.h"
#include "DxUtils/D3DHelper.hpp"

bool ShaderBase::Initialize() {
    DWORD m_dwShaderFlag = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined(DEBUG) || defined(_DEBUG)
    m_dwShaderFlag |= D3DCOMPILE_DEBUG;
#endif // DEBUG

    ID3DBlob* pShaderBuffer = nullptr;
    ID3DBlob* pErrorBuffer = nullptr;

    auto hResult = D3DCompileFromFile(
        this->GetShaderFile().c_str(),
        nullptr, 
        nullptr, 
        GetShaderEntryName().c_str(), 
        GetShaderVersion().c_str(),
        m_dwShaderFlag, 
        0, 
        &pShaderBuffer, 
        &pErrorBuffer
    );

    if (pErrorBuffer) {
        // OutputDebugStringA(static_cast<char*>(pErrorBuffer->GetBufferPointer()));
        ::MessageBoxA(nullptr, static_cast<char*>(pErrorBuffer->GetBufferPointer()), "Shader Msg", 0);
        goto failed_exit;
    }

    if (FAILED(hResult)) {
        goto failed_exit;
    }

    if (!CreateShader(pShaderBuffer)) {
        goto failed_exit;
    }

    if (!DefineShaderSubResource()) {
        goto failed_exit;
    }

    D3DHelper::SafeRelease(pShaderBuffer);
    D3DHelper::SafeRelease(pErrorBuffer);
    return true;

failed_exit:
    D3DHelper::SafeRelease(pShaderBuffer);
    D3DHelper::SafeRelease(pErrorBuffer);

    assert(false);
    return false;
}
