#ifndef _SHADERBUFFER_
#define _SHADERBUFFER_

#include <DirectXMath.h>

struct LightCommonPixelShaderBuffer {
    DirectX::XMFLOAT3 m_f3LightPos;
    float m_fUnused0;
    DirectX::XMFLOAT3 m_f3ViewPos;
    float m_fUnsused1;
};

#endif // !_SHADERBUFFER_
