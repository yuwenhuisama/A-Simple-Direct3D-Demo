#include "Camera.h"
#include "DxUtils/InputManager.h"
#include "GameObject.h"

#include "GameUtils/GameConfigure.h"

#include "math.h"

Camera& Camera::Instance() {
    static Camera instance;
    return instance;
}

void Camera::Initialize() {
    const auto& cCamearaConfigure = GameConfigure::Instance().GetCameraConfigure();

    m_tiThirdPersonInfo.m_fDistance = cCamearaConfigure.m_fDefaultThirdDistance;
    m_tiThirdPersonInfo.m_fPhi = cCamearaConfigure.m_fDefaultThirdPhi * DirectX::XM_PI;
    m_tiThirdPersonInfo.m_fTheta = cCamearaConfigure.m_fDefaultThirdTheta * DirectX::XM_PI;
    m_tiThirdPersonInfo.m_v32EyePos = { cCamearaConfigure.m_f3DefaultThirdEyePos.x,
          cCamearaConfigure.m_f3DefaultThirdEyePos.y,
          cCamearaConfigure.m_f3DefaultThirdEyePos.z };
    m_tiThirdPersonInfo.m_v32Up = { cCamearaConfigure.m_f3DefaultThirdEyeUp.x,
          cCamearaConfigure.m_f3DefaultThirdEyeUp.y,
          cCamearaConfigure.m_f3DefaultThirdEyeUp.z };

    m_fiFirstPersonInfo.m_v32Direction = {
        cCamearaConfigure.m_f3DefaultFirstEyeDirection.x,
        cCamearaConfigure.m_f3DefaultFirstEyeDirection.y,
        cCamearaConfigure.m_f3DefaultFirstEyeDirection.z };
    m_fiFirstPersonInfo.m_v32Up = {
        cCamearaConfigure.m_f3DefaultFirstEyeUp.x,
        cCamearaConfigure.m_f3DefaultFirstEyeUp.y,
        cCamearaConfigure.m_f3DefaultFirstEyeUp.z };
    m_fiFirstPersonInfo.m_v32EyePos = {
        cCamearaConfigure.m_f3DefaultFirstEyePos.x,
        cCamearaConfigure.m_f3DefaultFirstEyePos.y,
        cCamearaConfigure.m_f3DefaultFirstEyePos.z };
}

void Camera::Update() {
    if (!m_pBoundGameObject) {
        return;
    }

    const auto& cCamearaConfigure = GameConfigure::Instance().GetCameraConfigure();
    const auto& iManager = InputManager::Instance();

    if (m_eMode == CameraMode::ThirdPerson) {
        auto& fTheta = m_tiThirdPersonInfo.m_fTheta;
        auto& fPhi = m_tiThirdPersonInfo.m_fPhi;
        auto& fDistance = m_tiThirdPersonInfo.m_fDistance;

        if (InputManager::Instance().IsMouseLeftButtonDown()) {
            const auto fDx = InputManager::Instance().GetMouseDX();
            const auto fDy = InputManager::Instance().GetMouseDY();

            fTheta += fDy * cCamearaConfigure.m_fDefaultThirdRotationFactorX;
            fPhi -= fDx * cCamearaConfigure.m_fDefaultThirdRotationFactorY;

            if (fTheta >= DirectX::XM_PI) {
                fTheta = DirectX::XM_PI - 0.1f;
            } else if (fTheta <= 0.0f) {
                fTheta = 0.1f;
            }
        }

        const auto uMiddleOffset = InputManager::Instance().GetMouseDZ();
        fDistance -= uMiddleOffset * 0.01f;
        if (fDistance <= cCamearaConfigure.m_fThirdMinDistance) {
            fDistance = cCamearaConfigure.m_fThirdMinDistance;
        } else if (fDistance >= cCamearaConfigure.m_fThirdMaxDistance) {
            fDistance = cCamearaConfigure.m_fThirdMaxDistance;
        }
        
        DirectX::XMVECTOR v3Dist = {
            fDistance * sinf(m_tiThirdPersonInfo.m_fTheta) * cosf(m_tiThirdPersonInfo.m_fPhi),
            fDistance * cosf(m_tiThirdPersonInfo.m_fTheta),
            fDistance * sinf(m_tiThirdPersonInfo.m_fTheta) * sinf(m_tiThirdPersonInfo.m_fPhi),
        };

        const auto& v3ObjPos = m_pBoundGameObject->Position();
        const auto vObjPos = DirectX::XMLoadFloat3(&v3ObjPos);

        m_tiThirdPersonInfo.m_v32EyePos = DirectX::XMVectorSubtract(vObjPos, v3Dist);
    } else {
        if (InputManager::Instance().IsMouseLeftButtonDown()) {
            const auto fDx = InputManager::Instance().GetMouseDX();
            const auto fDy = InputManager::Instance().GetMouseDY();

            auto& v3Direction = m_fiFirstPersonInfo.m_v32Direction;
            v3Direction = DirectX::XMVector3Transform(v3Direction, DirectX::XMMatrixRotationY(fDx * cCamearaConfigure.m_fFirstRotationFactorX));

            auto v3Right = DirectX::XMVector3Cross(m_fiFirstPersonInfo.m_v32Up, v3Direction);
            v3Direction = DirectX::XMVector3Transform(m_fiFirstPersonInfo.m_v32Direction, DirectX::XMMatrixRotationAxis(v3Right, fDy * cCamearaConfigure.m_fFirstRotationFactorY));
        }

        const auto& v3ObjPos = m_pBoundGameObject->Position();
        auto& v3EyePos = m_fiFirstPersonInfo.m_v32EyePos;

        v3EyePos = DirectX::XMLoadFloat3(&v3ObjPos);
        v3EyePos = DirectX::XMVectorAdd(v3EyePos, { cCamearaConfigure.m_f3FirstEyePosAdjust.x, cCamearaConfigure.m_f3FirstEyePosAdjust.y, cCamearaConfigure.m_f3FirstEyePosAdjust.z } );
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
    if (m_pBoundGameObject) {
        if (m_eMode == CameraMode::ThirdPerson) {
            auto v3ObjPos = m_pBoundGameObject->Position();
            auto vObjPos = DirectX::XMLoadFloat3(&v3ObjPos);
            return DirectX::XMMatrixLookAtLH(m_tiThirdPersonInfo.m_v32EyePos, vObjPos, m_tiThirdPersonInfo.m_v32Up);
        } else {
            return DirectX::XMMatrixLookToLH(m_fiFirstPersonInfo.m_v32EyePos, m_fiFirstPersonInfo.m_v32Direction, m_fiFirstPersonInfo.m_v32Up);
        }
    } else {
        return DirectX::XMMatrixLookAtLH({ 10.0f, 0.0f, -100.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
    }
}
