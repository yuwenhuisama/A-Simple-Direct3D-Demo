#ifndef _H_EFFECT_
#define _H_EFFECT_

#include <string>
#include <vector>
#include "DxEffect/d3dx11effect.h"

typedef std::vector<D3D11_INPUT_ELEMENT_DESC> EffectPassInfo;

class Effect {
protected:
    ID3DX11Effect* m_pEffect = nullptr;
    ID3DX11EffectTechnique* m_pTech = nullptr;
    std::vector<ID3D11InputLayout*> m_vcInputLayout;

private:

    void _ReleaseInputLayout();

public:
    Effect() = default;
    virtual ~Effect();

    virtual bool Initialize();
    virtual std::wstring GetEffectFilePath() = 0;

    virtual std::vector<EffectPassInfo> GetPassInfo() = 0;

    virtual void PostInitialize() = 0;

    const std::vector<ID3D11InputLayout*>& GetInputLayouts() const { return m_vcInputLayout; }
    ID3DX11EffectTechnique* GetTechnique() const { return m_pTech; }
};

#endif
