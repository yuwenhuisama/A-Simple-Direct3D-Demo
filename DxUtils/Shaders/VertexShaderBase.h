#ifndef _H_VERTEXSHADERBASE_
#define _H_VERTEXSHADERBASE_

#include "ShaderBase.h"
#include <vector>

class VertexShaderBase : public ShaderBase {
private:
    ID3D11VertexShader* m_pVertexShader = nullptr;
    ID3D11InputLayout* m_pInputLayout = nullptr;

public:
    VertexShaderBase();
    ~VertexShaderBase();

    virtual bool CreateShader(ID3DBlob* pBlob) override;

    virtual const D3D11_INPUT_ELEMENT_DESC* GetInputLayoutDescArray() = 0;
    virtual UINT GetInputLayoutDescArraySize() = 0;

    ID3D11VertexShader* GetVertexShader() const { return m_pVertexShader; }
    ID3D11InputLayout* GetInputLayout() const { return m_pInputLayout; }
};

#endif // !_H_PIXELSHADERBASE_
