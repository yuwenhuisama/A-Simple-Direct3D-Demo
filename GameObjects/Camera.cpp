#include "Camera.h"
#include "DxUtils/InputManager.h"

Camera& Camera::Instance() {
    static Camera instance;
    return instance;
}

void Camera::Update() {
    float fUnit = 0.1f;

    const auto& iManager = InputManager::Instance();

    // move front
    if (iManager.IsKeyDown(DIK_W)) {
        auto v4DirUnit = DirectX::XMVector3Normalize(m_v32Direction);
        m_v32EyePos = DirectX::XMVectorAdd(DirectX::XMVectorScale(v4DirUnit, fUnit), m_v32EyePos);
    // move back
    } else if (iManager.IsKeyDown(DIK_S)) {
        auto v4DirUnit = DirectX::XMVector3Normalize(m_v32Direction);
        m_v32EyePos = DirectX::XMVectorSubtract(m_v32EyePos, DirectX::XMVectorScale(v4DirUnit, fUnit));
    // move left
    } else if (iManager.IsKeyDown(DIK_A)) {
        auto v4DirUnit = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(m_v32Up, m_v32Direction));
        m_v32EyePos = DirectX::XMVectorSubtract(m_v32EyePos, DirectX::XMVectorScale(v4DirUnit, fUnit));
    // move right
    } else if (iManager.IsKeyDown(DIK_D)) {
        auto v4DirUnit = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(m_v32Up, m_v32Direction));
        m_v32EyePos = DirectX::XMVectorAdd(m_v32EyePos, DirectX::XMVectorScale(v4DirUnit, fUnit));
    // left rotate
    } else if (iManager.IsKeyDown(DIK_Q)) {
        auto mtTransform =  DirectX::XMMatrixRotationAxis(m_v32Up, DirectX::XM_PI / 100.0f);
        m_v32Direction = DirectX::XMVector3Transform(m_v32Direction, mtTransform);
    // right rotate
    } else if (iManager.IsKeyDown(DIK_E)) {
        auto mtTransform = DirectX::XMMatrixRotationAxis(m_v32Up, -DirectX::XM_PI / 100.0f);
        m_v32Direction = DirectX::XMVector3Transform(m_v32Direction, mtTransform);
    // move up
    } else if (iManager.IsKeyDown(DIK_SPACE)) {
        auto v4DirUnit = DirectX::XMVector3Normalize(m_v32Up);
        m_v32EyePos = DirectX::XMVectorAdd(m_v32EyePos, DirectX::XMVectorScale(v4DirUnit, fUnit));
    // move down
    } else if (iManager.IsKeyDown(DIK_LCONTROL)) {
        auto v4DirUnit = DirectX::XMVector3Normalize(m_v32Up);
        m_v32EyePos = DirectX::XMVectorSubtract(m_v32EyePos, DirectX::XMVectorScale(v4DirUnit, fUnit));
    }
}

DirectX::XMMATRIX Camera::GetViewMatrix() const{
    return DirectX::XMMatrixLookToLH(m_v32EyePos, m_v32Direction, m_v32Up);
}
