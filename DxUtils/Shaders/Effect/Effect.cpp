#include "Effect.h"
#include <fstream>
#include <vector>
#include "DxUtils/D3DHelper.hpp"
#include "DxUtils/Direct3DManager.h"

#include <algorithm> 

bool Effect::Initialize() {
    const auto& wstrFxFile = this->GetEffectFilePath();

    if (Direct3DManager::Instance().CreateEffectFromFile(wstrFxFile, m_pEffect)) {
        this->PostInitialize();

        const auto& vcPassInfo = this->GetPassInfo();
        auto nIndex = 0u;

        m_vcInputLayout.clear();
        D3DX11_PASS_DESC pdscPassDesc;
        for (auto& vcDescArr : vcPassInfo) {
            m_pTech->GetPassByIndex(nIndex)->GetDesc(&pdscPassDesc);
            ID3D11InputLayout* pInputLayout = nullptr;

            // Create Input Layout
            if (!Direct3DManager::Instance().CreateInputLayout(vcDescArr, pdscPassDesc, pInputLayout)) {
                _ReleaseInputLayout();
                return false;
            }

            m_vcInputLayout.push_back(pInputLayout);
            ++nIndex;
        }

        return true;
    }

    _ReleaseInputLayout();
    return false;
}

void Effect::_ReleaseInputLayout() {
    std::for_each(m_vcInputLayout.begin(), m_vcInputLayout.end(),
        [](auto& elem)-> void {
            D3DHelper::SafeRelease(elem);
        });
}

Effect::~Effect() {
    D3DHelper::SafeRelease(m_pEffect);
    D3DHelper::SafeRelease(m_pTech);
    _ReleaseInputLayout();
}
