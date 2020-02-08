#ifndef _H_SHADER_BASE_
#define _H_SHADER_BASE_

#include <memory>
#include <string>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DxUtils/RenderCommandQueue/RenderCommand.h>

class GameObject;
class ShaderBase
{
public:
    ShaderBase() = default;
    virtual ~ShaderBase() = default;

    virtual bool Initialize();

protected:
    virtual std::wstring GetShaderFile() = 0;
    virtual std::string GetShaderEntryName() = 0;
    virtual std::string GetShaderVersion() = 0;
    virtual bool DefineShaderSubResource() = 0;
    virtual bool CreateShader(ID3DBlob* pBlob) = 0;

public:
    virtual void Apply(const RenderCommand& rcCommand) = 0;
};

#endif // !_H_SHADER_BASE_
