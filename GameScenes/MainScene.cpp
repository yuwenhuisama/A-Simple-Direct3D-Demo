#include "MainScene.h"
#include "GameControllers/CarController.h"
#include "GameObjects/JsonObjects/Ground.h"

#include "DxUtils/Direct3DManager.h"

#include "DxUtils/Shaders/LightCommonVertexShader.h"
#include "DxUtils/Shaders/LightCommonPixelShader.h"

#include "DxUtils/Shaders/ShadowedLightCommonVertexShader.h"
#include "DxUtils/Shaders/ShadowedLightCommonPixelShader.h"

#include "DxUtils/Shaders/SkyBoxVertexShader.h"
#include "DxUtils/Shaders/SkyBoxPixelShader.h"

#include "DxUtils/InputManager.h"

#include "GameObjects/Camera.h"
#include "GameObjects/SkyBox.h"

#include "DxUtils/Texture.h"

#include "DxUtils/RenderCommandQueue/RenderCommandQueueManager.h"

#include "DxUtils/Light.h"
#include "DxUtils/ShaderBuffer.h"

#include "GameUtils/GameConfigure.h"

void MainScene::OnReady() {
    auto pCar = std::make_shared<Car>();
    pCar->Initialize();
    this->AddChild(pCar);

    auto pCarController = std::make_shared<CarController>(pCar);
    m_pCarController = pCarController;
    
    // ----------
    Camera::Instance().Initialize();
    Camera::Instance().BindTo(pCar);

    //----------
    auto pGround = std::make_shared<Ground>();
    pGround->Initialize();
    pGround->Position().y = -0.5f;
    this->AddChild(pGround);

    // ----------
    auto pCubeTexture = std::make_shared<Texture>();
    pCubeTexture->LoadCube(
        D3DHelper::StringToWString(
            GameConfigure::Instance().GetSkyBoxConfigure().m_strTexture
        )
    );

    auto pSkyBox = std::make_shared<SkyBox>();
    pSkyBox->Initialize();
    pSkyBox->SetCubeTexture(pCubeTexture);
    pSkyBox->BindTo(pCar);
    this->SetSkyBox(pSkyBox);

    // ----------
    auto pLight = std::make_shared<Light>();
    pLight->m_f3LightPos = GameConfigure::Instance().GetLightConfigure().m_f3Position;
    this->SetLight(pLight);

    // ----------
    std::shared_ptr<PixelShaderBase> pPixelShader = std::make_shared<ShadowedLightCommonPixelShader>();
    pPixelShader->Initialize();

    std::shared_ptr<VertexShaderBase> pVertexShader = std::make_shared<ShadowedLightCommonVertexShader>();
    pVertexShader->Initialize();

    Direct3DManager::Instance().SetPixelShader(pPixelShader);
    Direct3DManager::Instance().SetVertexShader(pVertexShader);

    m_pShadowedVetexShader = pVertexShader;
    m_pShadowedPixelShader = pPixelShader;

    // ----------
    pPixelShader = std::make_shared<LightCommonPixelShader>();
    pPixelShader->Initialize();

    pVertexShader = std::make_shared<LightCommonVertexShader>();
    pVertexShader->Initialize();

    m_pCommonVetexShader = pVertexShader;
    m_pCommonPixelShader = pPixelShader;

    // ----------
    auto pSkyBoxPixelShader = std::make_shared<SkyBoxPixelShader>();
    pSkyBoxPixelShader->Initialize();

    auto pSkyBoxVertexShader = std::make_shared<SkyBoxVertexShader>();
    pSkyBoxVertexShader->Initialize();
    
    pSkyBox->SetPixelShader(pSkyBoxPixelShader);
    pSkyBox->SetVertexShader(pSkyBoxVertexShader);
}

void MainScene::OnUpdate() {
    if (InputManager::Instance().IsKeyTrigger(DIK_R)) {
        Camera::Instance().SwitchMode();
    }

    if (InputManager::Instance().IsKeyTrigger(DIK_Y)) {
        m_bIsRenderShadow = !m_bIsRenderShadow ;
        if (m_bIsRenderShadow) {
            Direct3DManager::Instance().SetPixelShader(m_pShadowedPixelShader);
            Direct3DManager::Instance().SetVertexShader(m_pShadowedVetexShader);
        } else {
            Direct3DManager::Instance().SetPixelShader(m_pCommonPixelShader);
            Direct3DManager::Instance().SetVertexShader(m_pCommonVetexShader);
        }
    }

    m_pCarController->Update();    
    Camera::Instance().Update();
}

void MainScene::OnRelease(){
}

void MainScene::Render() {
    if (m_bIsRenderShadow) {
        // render shadow map
        RenderCommandQueueManager::Instance().Push(RenderCommand {
            RenderCommandType::BeginRenderShadowMap,
            nullptr
        });

        RenderCommandQueueManager::Instance().Push(RenderCommand {
            RenderCommandType::ClearDepthStencilBuffer,
            nullptr
        });

        if (m_pLight) {
            std::function<LightCommonPixelShaderBuffer(void)> fCallback = [this]() {
                const auto v4EyePose = Camera::Instance().GetEyePos();
                LightCommonPixelShaderBuffer bfBuffer;
                bfBuffer.m_f3LightPos = m_pLight->m_f3LightPos;
                bfBuffer.m_f3ViewPos = { DirectX::XMVectorGetX(v4EyePose), DirectX::XMVectorGetY(v4EyePose), DirectX::XMVectorGetZ(v4EyePose)};

                return bfBuffer;
            };

            RenderCommandQueueManager::Instance().Push(RenderCommand {
                    RenderCommandType::SetLightInfo,
                    fCallback
                }
            );
        }
        this->RenderGameObjects();

        RenderCommandQueueManager::Instance().Push(RenderCommand {
            RenderCommandType::EndRenderShadowMap,
            nullptr
        });

        // render scene
        RenderCommandQueueManager::Instance().Push(RenderCommand {
            RenderCommandType::ClearColorBuffer,
            nullptr
        });

        RenderCommandQueueManager::Instance().Push(RenderCommand {
            RenderCommandType::ClearDepthStencilBuffer,
            nullptr
        });

        if (m_pLight) {
            std::function<LightCommonPixelShaderBuffer(void)> fCallback = [this]() {
                const auto v4EyePose = Camera::Instance().GetEyePos();
                LightCommonPixelShaderBuffer bfBuffer;
                bfBuffer.m_f3LightPos = m_pLight->m_f3LightPos;
                bfBuffer.m_f3ViewPos = { DirectX::XMVectorGetX(v4EyePose), DirectX::XMVectorGetY(v4EyePose), DirectX::XMVectorGetZ(v4EyePose)};

                return bfBuffer;
            };

            RenderCommandQueueManager::Instance().Push(RenderCommand {
                    RenderCommandType::SetLightInfo,
                    fCallback
                }
            );
        }

        RenderCommandQueueManager::Instance().Push(RenderCommand {
            RenderCommandType::SetShadowMapTexture,
            nullptr
        });

        this->RenderGameObjects();
        this->RenderSkyBox();
    } else {
        Scene::Render();
    }
}
