#ifndef _H_LIGHT_
#define _H_LIGHT_
#include <DirectXMath.h>

struct Light {
    DirectX::XMFLOAT3 m_f3LightPos = { 0.0f, 0.0f, 0.0f };
};

#endif // !_H_LIGHT_