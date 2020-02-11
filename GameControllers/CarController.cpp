#include "CarController.h"
#include "DxUtils/InputManager.h"
#include "GameObjects/JsonObjects/Car.h"

#include "GameUtils/GameConfigure.h"

#include <math.h>

constexpr DirectX::XMFLOAT4 c_f4Region = { -145.0f, -145.0f, 145.0f, 145.0f };

CarController::CarController(std::shared_ptr<Car> pCar) : m_pCar(pCar) {}

void CarController::Update() {
    const auto& cCarConfigure = GameConfigure::Instance().GetCarConfigure();
    auto& iManager = InputManager::Instance();

    // move up
    if (iManager.IsKeyDown(DIK_W)) {
        m_fSpeed += cCarConfigure.m_fAccSpeedForward;
    }
    // move back
    else if (iManager.IsKeyDown(DIK_S)) {
        m_fSpeed -= cCarConfigure.m_fAccSpeedBack;
    }
    else {
        if (m_fSpeed > 0) {
            m_fSpeed -= cCarConfigure.m_fAccStop;
        } else if (m_fSpeed < 0){
            m_fSpeed += cCarConfigure.m_fAccStop;
        }
    }

    auto pLockedCar = m_pCar.lock();
    // move left
    if (m_fSpeed != 0.0f) {
        if (iManager.IsKeyDown(DIK_A)) {
            m_v3Direction = DirectX::XMVector3Normalize(DirectX::XMVector3Transform(m_v3Direction, DirectX::XMMatrixRotationY(-cCarConfigure.m_fTurnAngle * DirectX::XM_PI)));
            m_fAngle -= cCarConfigure.m_fTurnAngle * DirectX::XM_PI;

            if (pLockedCar) {
                pLockedCar->SetWheelAngle(-DirectX::XM_PI * cCarConfigure.m_fTurnWheelAngle);
            }
        }
        // move right
        else if (iManager.IsKeyDown(DIK_D)) {
            m_v3Direction = DirectX::XMVector3Normalize(DirectX::XMVector3Transform(m_v3Direction, DirectX::XMMatrixRotationY(+cCarConfigure.m_fTurnAngle * DirectX::XM_PI)));
            m_fAngle += cCarConfigure.m_fTurnAngle * DirectX::XM_PI;

            if (pLockedCar) {
                pLockedCar->SetWheelAngle(DirectX::XM_PI * cCarConfigure.m_fTurnWheelAngle);
            }
        } else {
            pLockedCar->SetWheelAngle(0.0f);
        }
    } else {
        if (iManager.IsKeyDown(DIK_A)) {
            auto pLockedCar = m_pCar.lock();
            if (pLockedCar) {
                pLockedCar->SetWheelAngle(-DirectX::XM_PI * cCarConfigure.m_fTurnWheelAngle);
            }
        }
        // move right
        else if (iManager.IsKeyDown(DIK_D)) {
            auto pLockedCar = m_pCar.lock();
            if (pLockedCar) {
                pLockedCar->SetWheelAngle(DirectX::XM_PI * cCarConfigure.m_fTurnWheelAngle);
            }
        } else {
            pLockedCar->SetWheelAngle(0.0f);
        }
    }

    // m_fSpeed = std::clamp(m_fSpeed, -0.5f, 0.5f);
    if (m_fSpeed < cCarConfigure.m_fMinSpeedBack) {
        m_fSpeed = cCarConfigure.m_fMinSpeedBack;
    } else if (m_fSpeed > cCarConfigure.m_fMaxSpeedForward){
        m_fSpeed = cCarConfigure.m_fMaxSpeedForward;
    }

    if (std::abs(m_fSpeed) <= 1e-4f) {
        m_fSpeed = 0;
    }

    m_v3Position = DirectX::XMVectorAdd(m_v3Position, DirectX::XMVectorScale(m_v3Direction, m_fSpeed));
    auto fRollAngle = m_fSpeed / pLockedCar->GetWheelRadius();
    m_fWheelAngle += fRollAngle;
    pLockedCar->SetWheelRollAngle(-m_fWheelAngle);

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

    if (pLockedCar) {
        DirectX::XMStoreFloat3(&pLockedCar->Position(), m_v3Position);
        pLockedCar->Rotation().y = m_fAngle;
    }
    
}
