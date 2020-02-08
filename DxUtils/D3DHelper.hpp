#ifndef _H_D3DHELPER_
#define _H_D3DHELPER_

#include <array>
#include <DirectXMath.h>
#include <functional>

namespace D3DHelper {
    template<class T>
    void SafeRelease(T& p) {
        if (p) {
            p->Release();
            p = nullptr;
        }
    }

    DirectX::XMMATRIX CalcWorldMatrix(const DirectX::XMFLOAT3& v3Translation, const  DirectX::XMFLOAT3& v3Rotation, const  DirectX::XMFLOAT3& v3Scale);
};

struct InstancedInfo {
    DirectX::XMFLOAT3 m_v3Position;
    DirectX::XMFLOAT3 m_v3Rotation;
    DirectX::XMFLOAT3 m_v3Scale;
    std::function<void(InstancedInfo&)> m_fUpdate;
};

#endif // !_H_D3DHELPER_
