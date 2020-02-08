#include "CarController.h"
#include "DxUtils/InputManager.h"
#include "GameObjects/JsonObjects/Car.h"

CarController::CarController(std::shared_ptr<Car> pCar) : m_pCar(pCar) {}

void CarController::Update() {
    auto& iManager = InputManager::Instance();

    // move up
    if (iManager.IsKeyDown(DIK_UP)) {
        if (m_fSpeed <= 0.10f) {
            m_fSpeed += 0.01f;
        }
        m_v3Position = DirectX::XMVectorAdd(m_v3Position, DirectX::XMVectorScale(m_v3Direction, m_fSpeed));
    }
    // move back
    else if (iManager.IsKeyDown(DIK_DOWN)) {
        m_fSpeed -= 0.01f;
        if (m_fSpeed > 0.0f) {
            m_v3Position = DirectX::XMVectorSubtract(m_v3Position, DirectX::XMVectorScale(m_v3Direction, m_fSpeed));
        } else {
            if (m_fSpeed <= -0.10f) {
                m_fSpeed = -0.10f;
                m_v3Position = DirectX::XMVectorAdd(m_v3Position, DirectX::XMVectorScale(m_v3Direction, m_fSpeed));
            }
        }
    }
    // move left
    else if (iManager.IsKeyDown(DIK_LEFT)) {

    }
    // move right
    else if (iManager.IsKeyDown(DIK_RIGHT)) {

    }

    auto pCarLocked = m_pCar.lock();
    if (pCarLocked) {
        DirectX::XMStoreFloat3(&pCarLocked->Position(), m_v3Position);
    }
}
