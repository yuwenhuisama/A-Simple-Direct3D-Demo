#include "CarController.h"
#include "DxUtils/InputManager.h"
#include "GameObjects/JsonObjects/Car.h"

#include <math.h>

CarController::CarController(std::shared_ptr<Car> pCar) : m_pCar(pCar) {}

void CarController::Update() {
    auto& iManager = InputManager::Instance();

    // move up
    if (iManager.IsKeyDown(DIK_UP)) {
        m_fSpeed += 0.01f;
    }
    // move back
    else if (iManager.IsKeyDown(DIK_DOWN)) {
        m_fSpeed -= 0.01f;
    }
    else {
        if (m_fSpeed > 0) {
            m_fSpeed -= 0.005f;
        } else if (m_fSpeed < 0){
            m_fSpeed += 0.005f;
        }
    }
    
    // move left
    if (iManager.IsKeyDown(DIK_LEFT)) {
        m_v3Direction = DirectX::XMVector3Normalize(DirectX::XMVector3Transform(m_v3Direction, DirectX::XMMatrixRotationY(-0.01f)));
        m_fAngle -= 0.01f;
    }
    // move right
    else if (iManager.IsKeyDown(DIK_RIGHT)) {
        m_v3Direction = DirectX::XMVector3Normalize(DirectX::XMVector3Transform(m_v3Direction, DirectX::XMMatrixRotationY(+0.01f)));
        m_fAngle += 0.01f;
    }

    // m_fSpeed = std::clamp(m_fSpeed, -0.5f, 0.5f);
    if (m_fSpeed < -0.5f) {
        m_fSpeed = -0.5f;
    } else if (m_fSpeed > 0.5f){
        m_fSpeed = 0.5f;
    }

    if (std::abs(m_fSpeed) <= 1e-4f) {
        m_fSpeed = 0;
    }

    m_v3Position = DirectX::XMVectorAdd(m_v3Position, DirectX::XMVectorScale(m_v3Direction, m_fSpeed));

    auto pCarLocked = m_pCar.lock();
    if (pCarLocked) {
        DirectX::XMStoreFloat3(&pCarLocked->Position(), m_v3Position);
        pCarLocked->Rotation().y = m_fAngle;
    }
    
}
