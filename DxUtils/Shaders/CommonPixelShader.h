#ifndef _H_COMMONPIXELSHADER_
#define _H_COMMONPIXELSHADER_

#include "PixelShaderBase.h"

class CommonPixelShader : public PixelShaderBase {
public:
    CommonPixelShader();
    virtual ~CommonPixelShader();

    virtual std::wstring GetShaderFile() override;
    virtual std::string GetShaderEntryName() override;
    virtual std::string GetShaderVersion() override;
    virtual bool DefineShaderSubResource() override;

public:
    virtual void Apply(const RenderCommand& rcCommand) override;
};

#endif // !_H_COMMONPIXELSHADER_
