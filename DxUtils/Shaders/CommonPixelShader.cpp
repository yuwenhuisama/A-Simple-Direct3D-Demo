#include "CommonPixelShader.h"

CommonPixelShader::CommonPixelShader(): PixelShaderBase() {

}

CommonPixelShader::~CommonPixelShader() {

}

std::wstring CommonPixelShader::GetShaderFile() {
    return L"HLSL/shape_ps.fx";
}

std::string CommonPixelShader::GetShaderEntryName() {
    return "PSMain";
}

std::string CommonPixelShader::GetShaderVersion() {
    return "ps_5_0";
}

bool CommonPixelShader::DefineShaderSubResource() {
    return true;
}

void CommonPixelShader::Apply(const RenderCommand& rcCommand) {

}
