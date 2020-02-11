#ifndef _H_LIGHTCOMMONPIXELSHADER_
#define _H_LIGHTCOMMONPIXELSHADER_

#include "PixelShaderBase.h"
#include "DxUtils/ShaderBuffer.h"

class LightCommonPixelShader : public PixelShaderBase {
private:
    ID3D11Buffer* m_pLightInfo = nullptr;

public:
    LightCommonPixelShader();
    virtual ~LightCommonPixelShader();

    virtual std::wstring GetShaderFile() override;
    virtual std::string GetShaderEntryName() override;
    virtual std::string GetShaderVersion() override;
    virtual bool DefineShaderSubResource() override;

    virtual void Apply(const RenderCommand& rcCommand) override;

    void UpdateLightInfo(const LightCommonPixelShaderBuffer& bfLightInfo);
};

#endif // !_H_LIGHTCOMMONPIXELSHADER_
