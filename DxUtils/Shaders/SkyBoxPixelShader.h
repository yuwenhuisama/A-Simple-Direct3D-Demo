#ifndef _H_SKYBOXPIXELSHADER_
#define _H_SKYBOXPIXELSHADER_

#include "PixelShaderBase.h"

class SkyBoxPixelShader : public PixelShaderBase{
public:
    SkyBoxPixelShader();
    ~SkyBoxPixelShader();

    virtual std::wstring GetShaderFile() override;
    virtual std::string GetShaderEntryName() override;
    virtual std::string GetShaderVersion() override;
    virtual bool DefineShaderSubResource() override;

    virtual void Apply(const RenderCommand& rcCommand) override;
};

#endif // !_H_SKYBOXPIXELSHADER_
