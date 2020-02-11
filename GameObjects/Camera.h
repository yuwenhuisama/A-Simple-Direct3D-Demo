#ifndef _H_CAMERA_
#define _H_CAMERA_

#include <DirectXMath.h>
#include <memory>

enum CameraMode {
    FirstPerson,
    ThirdPerson,
};

struct ThirdPersonCameraInfo {
    DirectX::XMVECTOR m_v32EyePos = { 0, 0, -5.0f, 0 };
    DirectX::XMVECTOR m_v32Up = { 0, 1.0f, 0.0f, 0 };

    float m_fTheta = DirectX::XM_PI / 8 * 5;
    float m_fPhi = DirectX::XM_PI / 2;
    float m_fDistance = 7.0f;
};

struct FirstPersonCameraInfo {
    DirectX::XMVECTOR m_v32EyePos = { 0, 0.6f, -2.0f, 0 };
    DirectX::XMVECTOR m_v32Up = { 0, 1.0f, 0.0f, 0 };
    DirectX::XMVECTOR m_v32Direction = { 0.0f, 0.0f, 1.0f };

};

class GameObject;
class Camera {
private:
    CameraMode m_eMode = CameraMode::ThirdPerson;
    std::shared_ptr<GameObject> m_pBoundGameObject = nullptr;

    ThirdPersonCameraInfo m_tiThirdPersonInfo;
    FirstPersonCameraInfo m_fiFirstPersonInfo;

private:
    Camera() = default;

public:
    static Camera& Instance();

    void Initialize();
    void Update();
    void SwitchMode();

    void BindTo(std::shared_ptr<GameObject> pObject) { m_pBoundGameObject = pObject; }

    DirectX::XMVECTOR GetEyePos() const { 
        if (m_eMode == CameraMode::ThirdPerson) {
            return m_tiThirdPersonInfo.m_v32EyePos;
        } else {
            return m_fiFirstPersonInfo.m_v32EyePos;
        }
    }

    DirectX::XMMATRIX GetViewMatrix() const;

};

#endif // !_H_CAMERA_
