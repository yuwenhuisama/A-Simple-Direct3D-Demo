#include "SkyBoxPixelShader.h"

SkyBoxPixelShader::SkyBoxPixelShader() : PixelShaderBase() {
}

SkyBoxPixelShader::~SkyBoxPixelShader() {

}

std::wstring SkyBoxPixelShader::GetShaderFile() {
    return L"HLSL/skybox_ps.fx";
}

std::string SkyBoxPixelShader::GetShaderEntryName() {
    return "PSMain";
}

std::string SkyBoxPixelShader::GetShaderVersion() {
    return "ps_5_0";
}

bool SkyBoxPixelShader::DefineShaderSubResource() {
    return true;
}

void SkyBoxPixelShader::Apply(const RenderCommand& rcCommand) {

}
