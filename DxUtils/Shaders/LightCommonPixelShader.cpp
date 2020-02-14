#include "LightCommonPixelShader.h"
#include "DxUtils/Direct3DManager.h"
#include "DxUtils/D3DHelper.hpp"

#include <functional>

LightCommonPixelShader::LightCommonPixelShader(): PixelShaderBase() {

}

LightCommonPixelShader::~LightCommonPixelShader() {
    D3DHelper::SafeRelease(m_pLightInfo);
}

std::wstring LightCommonPixelShader::GetShaderFile() {
    return L"HLSL/light_shape_ps.fx";
}

std::string LightCommonPixelShader::GetShaderEntryName() {
    return "PSMain";
}

std::string LightCommonPixelShader::GetShaderVersion() {
    return "ps_5_0";
}

bool LightCommonPixelShader::DefineShaderSubResource() {
    D3D11_BUFFER_DESC dbdMatrix;
    memset(&dbdMatrix, 0, sizeof(D3D11_BUFFER_DESC));
    dbdMatrix.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    dbdMatrix.ByteWidth = sizeof(LightCommonPixelShaderBuffer);
    dbdMatrix.Usage = D3D11_USAGE_DEFAULT;

    const auto result = Direct3DManager::Instance().CreateBuffer(dbdMatrix, m_pLightInfo);

    if (FAILED(result)) {
        return false;
    }

    return true;
}

void LightCommonPixelShader::UpdateLightInfo(const LightCommonPixelShaderBuffer& bfLightInfo) {
    const auto pDeviceContext = Direct3DManager::Instance().GetDeviceContext();
    pDeviceContext->UpdateSubresource(m_pLightInfo, 0, nullptr, &bfLightInfo, 0, 0);
    pDeviceContext->PSSetConstantBuffers(0, 1, &m_pLightInfo);
}

void LightCommonPixelShader::Apply(const RenderCommand& rcCommand) {
    if (rcCommand.m_eType == RenderCommandType::SetLightInfo) {
        auto fCallback = std::any_cast<std::function<LightCommonPixelShaderBuffer(void)>>(rcCommand.m_objRenderInfo);
        auto bfLightInfo = fCallback();
        this->UpdateLightInfo(bfLightInfo);
    }
}
