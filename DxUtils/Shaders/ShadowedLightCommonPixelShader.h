#ifndef _H_SHADOWEDLIGHTCOMMONPIXELSHADER_
#define _H_SHADOWEDLIGHTCOMMONPIXELSHADER_

#include "LightCommonPixelShader.h"
class ShadowedLightCommonPixelShader : public LightCommonPixelShader {
public:
    ShadowedLightCommonPixelShader() : LightCommonPixelShader() {}
    virtual ~ShadowedLightCommonPixelShader() = default;

    virtual std::wstring GetShaderFile() override {
        return L"HLSL/shadowed_light_shape_ps.fx";
    }
};

#endif // !_H_SHADOWEDLIGHTCOMMONPIXELSHADER_
