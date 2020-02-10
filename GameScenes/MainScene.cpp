#include "MainScene.h"
#include "GameControllers/CarController.h"
#include "GameObjects/JsonObjects/Ground.h"

#include "DxUtils/Direct3DManager.h"

#include "DxUtils/Shaders/CommonVertexShader.h"
#include "DxUtils/Shaders/CommonPixelShader.h"

#include "DxUtils/Shaders/SkyBoxVertexShader.h"
#include "DxUtils/Shaders/SkyBoxPixelShader.h"

#include "DxUtils/InputManager.h"

#include "GameObjects/Camera.h"
#include "GameObjects/SkyBox.h"

#include "DxUtils/Texture.h"

void MainScene::OnReady() {
    auto pCar = std::make_shared<Car>();
    pCar->Initialize();
    this->AddChild(pCar);

    auto pCarController = std::make_shared<CarController>(pCar);
    m_pCarController = pCarController;
    
    // ----------
    Camera::Instance().BindTo(pCar);

    // ----------
    auto pGround = std::make_shared<Ground>();
    pGround->Initialize();
    pGround->Position().y = -0.5f;
    this->AddChild(pGround);

    // ----------
    auto pCubeTexture = std::make_shared<Texture>();
    // TODO: move hard code to configure
    pCubeTexture->LoadCube(L"Textures/skybox.jpg");

    auto pSkyBox = std::make_shared<SkyBox>();
    pSkyBox->Initialize();
    pSkyBox->SetCubeTexture(pCubeTexture);
    pSkyBox->BindTo(pCar);
    this->SetSkyBox(pSkyBox);

    // ----------
    auto pPixelShader = std::make_shared<CommonPixelShader>();
    pPixelShader->Initialize();

    auto pVertexShader = std::make_shared<CommonVertexShader>();
    pVertexShader->Initialize();

    Direct3DManager::Instance().SetPixelShader(pPixelShader);
    Direct3DManager::Instance().SetVertexShader(pVertexShader);

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

    m_pCarController->Update();    
    Camera::Instance().Update();
}

void MainScene::OnRelease(){

}
