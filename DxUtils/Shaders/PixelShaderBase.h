#ifndef _H_PIXELSHADERBASE_
#define _H_PIXELSHADERBASE_

#include "ShaderBase.h"

class PixelShaderBase : public ShaderBase {
private:
    ID3D11PixelShader* m_pPixelShader = nullptr;

public:
    PixelShaderBase();
    ~PixelShaderBase();

    virtual bool CreateShader(ID3DBlob* pBlob) override;

    ID3D11PixelShader* GetPixelShader() { return m_pPixelShader; }
};

#endif // !_H_PIXELSHADERBASE_
