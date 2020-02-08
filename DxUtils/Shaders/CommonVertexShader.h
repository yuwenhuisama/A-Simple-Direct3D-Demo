#ifndef _H_COMMONVERTEXSHADER_
#define _H_COMMONVERTEXSHADER_

#include "VertexShaderBase.h"

class CommonVertexShader : public VertexShaderBase {
private:
    ID3D11Buffer* m_pWVPBuffer = nullptr;

public:
    CommonVertexShader();
    virtual ~CommonVertexShader();

    virtual std::wstring GetShaderFile() override;
    virtual std::string GetShaderEntryName() override;
    virtual std::string GetShaderVersion() override;
    virtual bool DefineShaderSubResource() override;
    virtual const D3D11_INPUT_ELEMENT_DESC* GetInputLayoutDescArray() override;
    virtual UINT GetInputLayoutDescArraySize() override;

public:
    virtual void Apply(const RenderCommand& rcCommand) override;

    void UpdateWVPMatrix(const DirectX::XMMATRIX& mtMatrix);
};

#endif // !_H_COMMONVERTEXSHADER_
