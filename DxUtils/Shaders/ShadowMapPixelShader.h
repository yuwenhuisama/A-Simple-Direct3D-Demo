#ifndef _H_SHADOWMAPPIXELSHADER_
#define _H_SHADOWMAPPIXELSHADER_

#include "PixelShaderBase.h"

class ShadowMapPixelShader : public PixelShaderBase {
public:
    ShadowMapPixelShader();
    virtual ~ShadowMapPixelShader() = default;

    virtual std::wstring GetShaderFile() override;
    virtual std::string GetShaderEntryName() override;
    virtual std::string GetShaderVersion() override;
    virtual bool DefineShaderSubResource() override;

    virtual void Apply(const RenderCommand& rcCommand) override;
};

#endif // !_H_SHADOWMAPPIXELSHADER_
