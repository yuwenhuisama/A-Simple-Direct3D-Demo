#include "MainScene.h"
#include "GameObjects/BasicShapes/Cuboid.h"
#include "GameObjects/BasicShapes/Cylinder.h"
#include "GameObjects/BasicShapes/Sphare.h"
#include "GameObjects/BasicShapes/Triangle.h"
// #include "GameObjects/JsonObjects/Car.h"
#include "GameControllers/CarController.h"

#include "DxUtils/Direct3DManager.h"
// #include "DxUtils/Shaders/CommonEffect.h"

#include "DxUtils/Shaders/CommonVertexShader.h"
#include "DxUtils/Shaders/CommonPixelShader.h"

#include "GameObjects/Camera.h"

void MainScene::OnReady() {
    // auto pTriangle = std::make_shared<Triangle>();
    // pTriangle->Initialize();
    // this->AddChild(pTriangle);

    // auto pCuboid = std::make_shared<Cuboid>(2.0f, 1.0f, 1.5f);
    // pCuboid->Initialize();
    // pCuboid->SetTag("cuboid");
    // this->AddChild(pCuboid);

    // auto pCylinder = std::make_shared<Cylinder>(1.0f, 0.5f, 2.0f, 3, 10);
    // pCylinder->Initialize();
    // this->AddChild(pCylinder);

    // auto pSphare = std::make_shared<Sphare>(1.0f, 10, 10);
    // pSphare->Initialize();
    // this->AddChild(pSphare);

    // auto pEffect = std::make_shared<CommonEffect>();
    // pEffect->Initialize();
    // Direct3DManager::Instance().SetEffect(pEffect);

    auto pCar = std::make_shared<Car>();
    pCar->Initialize();
    this->AddChild(pCar);

    auto pCarController = std::make_shared<CarController>(pCar);
    m_pCarController = pCarController;
    // ----------

    auto pPixelShader = std::make_shared<CommonPixelShader>();
    pPixelShader->Initialize();

    auto pVertexShader = std::make_shared<CommonVertexShader>();
    pVertexShader->Initialize();

    Direct3DManager::Instance().SetPixelShader(pPixelShader);
    Direct3DManager::Instance().SetVertexShader(pVertexShader);
}

void MainScene::OnUpdate() {
    m_pCarController->Update();
    Camera::Instance().Update();
}

void MainScene::OnRelease(){

}
