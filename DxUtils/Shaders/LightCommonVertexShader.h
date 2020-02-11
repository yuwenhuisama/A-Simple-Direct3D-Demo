#ifndef _H_LIGHTCOMMONVERTEXSHADER_
#define _H_LIGHTCOMMONVERTEXSHADER_

#include "VertexShaderBase.h"
#include "DxUtils/ShaderBuffer.h"

class LightCommonVertexShader : public VertexShaderBase {
private:
    ID3D11Buffer* m_pWVPBuffer = nullptr;

public:
    LightCommonVertexShader();
    virtual ~LightCommonVertexShader();

    virtual std::wstring GetShaderFile() override;
    virtual std::string GetShaderEntryName() override;
    virtual std::string GetShaderVersion() override;
    virtual bool DefineShaderSubResource() override;
    virtual const D3D11_INPUT_ELEMENT_DESC* GetInputLayoutDescArray() override;
    virtual UINT GetInputLayoutDescArraySize() override;

    virtual void Apply(const RenderCommand& rcCommand) override;

    void UpdateWVPMatrix(const LightCommonVertexShaderBuffer& mtBuffer);
    
};

#endif // !_H_LIGHTCOMMONVERTEXSHADER_