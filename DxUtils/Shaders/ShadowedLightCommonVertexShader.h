#ifndef _H_SHADOWEDLIGHTVERTEXSHADER_
#define _H_SHADOWEDLIGHTVERTEXSHADER_

#include "LightCommonVertexShader.h"
class ShadowedLightCommonVertexShader : public VertexShaderBase {
private:
    ID3D11Buffer* m_pWVPBuffer = nullptr;
    DirectX::XMFLOAT3 m_f3LightPos = { 0.0f, 0.0f, 0.0f };

public:
    ShadowedLightCommonVertexShader();
    virtual ~ShadowedLightCommonVertexShader() = default;

    virtual std::wstring GetShaderFile() override;
    virtual std::string GetShaderEntryName() override;
    virtual std::string GetShaderVersion() override;
    virtual bool DefineShaderSubResource() override;
    virtual const D3D11_INPUT_ELEMENT_DESC* GetInputLayoutDescArray() override;
    virtual UINT GetInputLayoutDescArraySize() override;

    virtual void Apply(const RenderCommand& rcCommand) override;

    void UpdateWVPMatrix(const ShadowedLightCommonVertexShaderBuffer& mtBuffer);

};

#endif