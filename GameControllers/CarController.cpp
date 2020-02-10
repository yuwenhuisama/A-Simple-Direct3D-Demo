#include "CarController.h"
#include "DxUtils/InputManager.h"
#include "GameObjects/JsonObjects/Car.h"

#include <math.h>

constexpr DirectX::XMFLOAT4 c_f4Region = { -145.0f, -145.0f, 145.0f, 145.0f };

CarController::CarController(std::shared_ptr<Car> pCar) : m_pCar(pCar) {}

void CarController::Update() {
    auto& iManager = InputManager::Instance();

    // move up
    if (iManager.IsKeyDown(DIK_W)) {
        m_fSpeed += 0.01f;
    }
    // move back
    else if (iManager.IsKeyDown(DIK_S)) {
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
    if (iManager.IsKeyDown(DIK_A)) {
        m_v3Direction = DirectX::XMVector3Normalize(DirectX::XMVector3Transform(m_v3Direction, DirectX::XMMatrixRotationY(-0.01f)));
        m_fAngle -= 0.01f;
    }
    // move right
    else if (iManager.IsKeyDown(DIK_D)) {
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

    auto fPosX = DirectX::XMVectorGetX(m_v3Position);
    auto fPosZ = DirectX::XMVectorGetZ(m_v3Position);

    if (fPosX <= c_f4Region.x) {
        m_v3Position = DirectX::XMVectorSetX(m_v3Position, c_f4Region.z);
    } else if (fPosX >= c_f4Region.z) {
        m_v3Position = DirectX::XMVectorSetX(m_v3Position, c_f4Region.x);
    }

    if (fPosZ <= c_f4Region.y) {
        m_v3Position = DirectX::XMVectorSetZ(m_v3Position, c_f4Region.w);
    } else if (fPosZ >= c_f4Region.w) {
        m_v3Position = DirectX::XMVectorSetZ(m_v3Position, c_f4Region.y);
    }

    auto pCarLocked = m_pCar.lock();
    if (pCarLocked) {
        DirectX::XMStoreFloat3(&pCarLocked->Position(), m_v3Position);
        pCarLocked->Rotation().y = m_fAngle;
    }
    
}
