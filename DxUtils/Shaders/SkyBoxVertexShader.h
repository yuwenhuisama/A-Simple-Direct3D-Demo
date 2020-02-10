#ifndef _H_SKYBOXVERTEXSHADER_
#define _H_SKYBOXVERTEXSHADER_

#include "VertexShaderBase.h"

class SkyBoxVertexShader : public VertexShaderBase {
private:
    ID3D11Buffer* m_pWVPBuffer = nullptr;

public:
    SkyBoxVertexShader();
    virtual ~SkyBoxVertexShader();

    virtual std::wstring GetShaderFile() override;
    virtual std::string GetShaderEntryName() override;
    virtual std::string GetShaderVersion() override;
    virtual bool DefineShaderSubResource() override;
    virtual const D3D11_INPUT_ELEMENT_DESC* GetInputLayoutDescArray() override;
    virtual UINT GetInputLayoutDescArraySize() override;

    virtual void Apply(const RenderCommand& rcCommand) override;

    void UpdateWVPMatrix(const DirectX::XMMATRIX& mtMatrix);
};

#endif // !_H_SKYBOXVERTEXSHADER_
