#include "MainScene.h"
#include "GameControllers/CarController.h"
#include "GameObjects/JsonObjects/Ground.h"

#include "DxUtils/Direct3DManager.h"

#include "DxUtils/Shaders/CommonVertexShader.h"
#include "DxUtils/Shaders/CommonPixelShader.h"

#include "DxUtils/InputManager.h"

#include "GameObjects/Camera.h"

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
    auto pPixelShader = std::make_shared<CommonPixelShader>();
    pPixelShader->Initialize();

    auto pVertexShader = std::make_shared<CommonVertexShader>();
    pVertexShader->Initialize();

    Direct3DManager::Instance().SetPixelShader(pPixelShader);
    Direct3DManager::Instance().SetVertexShader(pVertexShader);
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
