#ifndef _H_VERTEX_
#define _H_VERTEX_

#include <DirectXMath.h>

struct Vertex {
    DirectX::XMFLOAT3 m_f3Pos;
    DirectX::XMFLOAT3 m_f3Normal;
    DirectX::XMFLOAT3 m_f3Tangent;
    DirectX::XMFLOAT2 m_f2Tex0;
};

struct SkyBoxVertex {
    DirectX::XMFLOAT3 m_f3Pos;
};

#endif // !_H_VERTEX_
