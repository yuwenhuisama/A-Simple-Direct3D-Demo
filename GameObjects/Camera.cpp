#include "Camera.h"
#include "DxUtils/InputManager.h"
#include "GameObject.h"

#include "math.h"

Camera& Camera::Instance() {
    static Camera instance;
    return instance;
}

void Camera::Update() {
    if (!m_pBoundGameObject) {
        return;
    }

    const auto& iManager = InputManager::Instance();

    if (m_eMode == CameraMode::ThirdPerson) {
        auto& fTheta = m_tiThirdPersonInfo.m_fTheta;
        auto& fPhi = m_tiThirdPersonInfo.m_fPhi;
        auto& fDistance = m_tiThirdPersonInfo.m_fDistance;

        if (InputManager::Instance().IsMouseLeftButtonDown()) {
            const auto fDx = InputManager::Instance().GetMouseDX();
            const auto fDy = InputManager::Instance().GetMouseDY();

            // TODO: move magic number to configure
            fTheta += fDy * 0.005f;
            fPhi -= fDx * 0.005f;

            if (fTheta >= DirectX::XM_PI) {
                fTheta = DirectX::XM_PI - 0.1f;
            } else if (fTheta <= 0.0f) {
                fTheta = 0.1f;
            }
        }

        const auto uMiddleOffset = InputManager::Instance().GetMouseDZ();
        fDistance -= uMiddleOffset * 0.01f;
        if (fDistance <= 2.5f) {
            fDistance = 2.5f;
        } else if (fDistance >= 12.0f) {
            fDistance = 12.0f;
        }
        
        DirectX::XMVECTOR v3Dist = {
            fDistance * sinf(m_tiThirdPersonInfo.m_fTheta) * cosf(m_tiThirdPersonInfo.m_fPhi),
            fDistance * cosf(m_tiThirdPersonInfo.m_fTheta),
            fDistance * sinf(m_tiThirdPersonInfo.m_fTheta) * sinf(m_tiThirdPersonInfo.m_fPhi),
        };

        const auto v3ObjPos = m_pBoundGameObject->Position();
        const auto vObjPos = DirectX::XMLoadFloat3(&v3ObjPos);

        m_tiThirdPersonInfo.m_v32EyePos = DirectX::XMVectorSubtract(vObjPos, v3Dist);
    } else {
        if (InputManager::Instance().IsMouseLeftButtonDown()) {
            const auto fDx = InputManager::Instance().GetMouseDX();
            const auto fDy = InputManager::Instance().GetMouseDY();

            auto& v3Direction = m_fiFirstPersonInfo.m_v32Direction;
            v3Direction = DirectX::XMVector3Transform(v3Direction, DirectX::XMMatrixRotationY(fDx * 0.001f));

            auto v3Right = DirectX::XMVector3Cross(m_fiFirstPersonInfo.m_v32Up, v3Direction);
            v3Direction = DirectX::XMVector3Transform(m_fiFirstPersonInfo.m_v32Direction, DirectX::XMMatrixRotationAxis(v3Right, fDy * 0.001f));
        }

        const auto v3ObjPos = m_pBoundGameObject->Position();
        auto& v3EyePos = m_fiFirstPersonInfo.m_v32EyePos;

        v3EyePos = DirectX::XMLoadFloat3(&v3ObjPos);
        v3EyePos = DirectX::XMVectorAdd(v3EyePos, { 0.0f, 0.6f, -2.0f });
    }
}

void Camera::SwitchMode() {
    if (m_eMode == CameraMode::FirstPerson) {
        m_eMode = CameraMode::ThirdPerson;
    } else {
        m_eMode = CameraMode::FirstPerson;
    }
}


DirectX::XMMATRIX Camera::GetViewMatrix() const{
    if (m_eMode == CameraMode::ThirdPerson) {
        auto v3ObjPos = m_pBoundGameObject->Position();
        auto vObjPos = DirectX::XMLoadFloat3(&v3ObjPos);
        return DirectX::XMMatrixLookAtLH(m_tiThirdPersonInfo.m_v32EyePos, vObjPos, m_tiThirdPersonInfo.m_v32Up);
    } else {
        return DirectX::XMMatrixLookToLH(m_fiFirstPersonInfo.m_v32EyePos, m_fiFirstPersonInfo.m_v32Direction, m_fiFirstPersonInfo.m_v32Up);
    }
}
