#ifndef _H_SKYBOX_
#define _H_SKYBOX_

#include <memory>
#include "DxUtils/Shaders/VertexShaderBase.h"
#include "DxUtils/Shaders/PixelShaderBase.h"

class Texture;
class GameObject;
class SkyBox {
private:
    ID3D11Buffer* m_pVertexBuffer = nullptr;
    ID3D11Buffer* m_pIndexedBuffer = nullptr;

    std::shared_ptr<Texture> m_pTexture = nullptr;

    std::shared_ptr<VertexShaderBase> m_pVertexShader = nullptr;
    std::shared_ptr<PixelShaderBase> m_pPixelShader = nullptr;

    std::shared_ptr<GameObject> m_pBoundObject = nullptr;

private:
    bool _InitializeBuffer();

public:
    SkyBox() = default;
    ~SkyBox();

    bool Initialize();

    void SetCubeTexture(std::shared_ptr<Texture> pTexture) { m_pTexture = pTexture; }
    std::shared_ptr<Texture> GetCubuTexture() const { return m_pTexture; }

    void SetPixelShader(std::shared_ptr<PixelShaderBase> pPixelShader) { m_pPixelShader = pPixelShader; }
    std::shared_ptr<PixelShaderBase> GetPixelShader() const { return m_pPixelShader; }

    void SetVertexShader(std::shared_ptr<VertexShaderBase> pVertexShader) { m_pVertexShader = pVertexShader; }
    std::shared_ptr<VertexShaderBase> GetVertexShader() const { return m_pVertexShader; }

    void Render();

    void BindTo(std::shared_ptr<GameObject> pObject) { m_pBoundObject = pObject; }

    std::shared_ptr<GameObject> GetBoundObject() const { return m_pBoundObject; }

};

#endif // !_H_SKYBOX_
