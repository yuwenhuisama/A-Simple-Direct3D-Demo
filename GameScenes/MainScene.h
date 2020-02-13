#ifndef _H_MAINSCENE_
#define _H_MAINSCENE_

#include <memory>
#include "Scene.h"

struct Light;
class CarController;
class VertexShaderBase;
class PixelShaderBase;
class MainScene: public Scene {
private:
    std::shared_ptr<CarController> m_pCarController;
    std::shared_ptr<Light> m_pLight = nullptr;

    std::shared_ptr<VertexShaderBase> m_pShadowedVetexShader = nullptr;
    std::shared_ptr<VertexShaderBase> m_pCommonVetexShader = nullptr;

    std::shared_ptr<PixelShaderBase> m_pShadowedPixelShader = nullptr;
    std::shared_ptr<PixelShaderBase> m_pCommonPixelShader = nullptr;

    bool m_bIsRenderShadow = true;

public:
    MainScene() = default;
    ~MainScene() = default;

    virtual std::shared_ptr<Light> GetLight() const { return m_pLight; }
    virtual void SetLight(std::shared_ptr<Light> pLight) { m_pLight = pLight; }

    virtual void OnReady() override;
    virtual void OnUpdate() override;
    virtual void OnRelease() override;
    virtual void Render() override;
};

#endif // !_H_MAINSCENE_
