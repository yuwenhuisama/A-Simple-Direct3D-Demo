#include "ShadowMapPixelShader.h"

ShadowMapPixelShader::ShadowMapPixelShader() : PixelShaderBase() {}

std::wstring ShadowMapPixelShader::GetShaderFile(){
    return L"HLSL/shadow_map_shape_ps.fx";
}

std::string ShadowMapPixelShader::GetShaderEntryName() {
    return "PSMain";
}

std::string ShadowMapPixelShader::GetShaderVersion() {
    return "ps_5_0";
}

bool ShadowMapPixelShader::DefineShaderSubResource() {
    return true;
}

void ShadowMapPixelShader::Apply(const RenderCommand& rcCommand) {

}
