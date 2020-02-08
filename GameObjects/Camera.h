#ifndef _H_CAMERA_
#define _H_CAMERA_

#include <DirectXMath.h>

class Camera {
private:
    DirectX::XMVECTOR m_v32Direction = { 0, 0, 1.0f, 0.0f };
    DirectX::XMVECTOR m_v32EyePos = { 0, 0, -5.0f, 0 };
    DirectX::XMVECTOR m_v32Up = { 0, 1.0f, 0.0f, 0};
    Camera() = default;

public:
    static Camera& Instance();

    void Update();

    DirectX::XMMATRIX GetViewMatrix() const;

};

#endif // !_H_CAMERA_
