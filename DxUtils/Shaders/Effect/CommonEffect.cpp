#include "CommonEffect.h"
#include "DxUtils/D3DHelper.hpp"

std::vector<EffectPassInfo> CommonEffect::GetPassInfo() {
    return {
        {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        },
    };
}

std::wstring CommonEffect::GetEffectFilePath() {
    return L"HLSL/cube.fx";
}

void CommonEffect::PostInitialize() {
    m_pTech = m_pEffect->GetTechniqueByName("ColorTech");
    m_pMatrix = m_pEffect->GetVariableByName("gWorldViewProj")->AsMatrix();
}

CommonEffect::~CommonEffect() {
    D3DHelper::SafeRelease(m_pMatrix);
}
