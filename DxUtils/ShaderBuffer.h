#ifndef _SHADERBUFFER_
#define _SHADERBUFFER_

#include <DirectXMath.h>

struct LightCommonPixelShaderBuffer {
    DirectX::XMFLOAT3 m_f3LightPos;
    float m_fUnused0;
    DirectX::XMFLOAT3 m_f3ViewPos;
    float m_fUnsused1;
};

struct LightCommonVertexShaderBuffer {
    DirectX::XMMATRIX m_mtWorld;
    DirectX::XMMATRIX m_mtWorldNormal;
    DirectX::XMMATRIX m_mtView;
    DirectX::XMMATRIX m_mtProj;
};

struct ShadowMapVertexShaderBuffer {
    DirectX::XMMATRIX m_mtWorld;
    DirectX::XMMATRIX m_mtView;
    DirectX::XMMATRIX m_mtProj;
};

struct ShadowedLightCommonVertexShaderBuffer {
    DirectX::XMMATRIX m_mtWorld;
    DirectX::XMMATRIX m_mtWorldNormal;
    DirectX::XMMATRIX m_mtView;
    DirectX::XMMATRIX m_mtProj;

    DirectX::XMMATRIX m_mtLightView;
    DirectX::XMMATRIX m_mtLightProj;
};

#endif // !_SHADERBUFFER_
