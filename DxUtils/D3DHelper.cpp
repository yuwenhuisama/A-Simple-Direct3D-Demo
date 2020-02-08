#include "D3DHelper.hpp"

namespace D3DHelper {
    DirectX::XMMATRIX CalcWorldMatrix(const DirectX::XMFLOAT3& v3Translation, const  DirectX::XMFLOAT3& v3Rotation, const  DirectX::XMFLOAT3& v3Scale) {
        DirectX::XMMATRIX mtWorld = DirectX::XMMatrixIdentity();

        const auto mtTranslation = DirectX::XMMatrixTranslation(v3Translation.x, v3Translation.y, v3Translation.z);
        const auto mtRotationX = DirectX::XMMatrixRotationX(v3Rotation.x);
        const auto mtRotationY = DirectX::XMMatrixRotationY(v3Rotation.y);
        const auto mtRotationZ = DirectX::XMMatrixRotationZ(v3Rotation.z);
        const auto mtScale = DirectX::XMMatrixScaling(v3Scale.x, v3Scale.y, v3Scale.z);

        mtWorld = mtScale * mtRotationX * mtRotationY * mtRotationZ * mtTranslation;

        return mtWorld;
    }
}
