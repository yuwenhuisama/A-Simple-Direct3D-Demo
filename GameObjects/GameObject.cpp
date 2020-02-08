#include "GameObject.h"
#include "DxUtils/D3DHelper.hpp"

DirectX::XMMATRIX GameObject::GetWorldMatrix() const {
    // DirectX::XMMATRIX mtWorld = DirectX::XMMatrixIdentity();

    // const auto mtTranslation = DirectX::XMMatrixTranslation(m_v3Position.x, m_v3Position.y, m_v3Position.z);
    // const auto mtRotationX = DirectX::XMMatrixRotationX(m_v3Rotation.x);
    // const auto mtRotationY = DirectX::XMMatrixRotationY(m_v3Rotation.y);
    // const auto mtRotationZ = DirectX::XMMatrixRotationZ(m_v3Rotation.z);
    // const auto mtScale = DirectX::XMMatrixScaling(m_v3Scale.x, m_v3Scale.y, m_v3Scale.z);

    // mtWorld = mtScale * mtRotationX * mtRotationY * mtRotationZ * mtTranslation;

    // return mtWorld;

    return D3DHelper::CalcWorldMatrix(m_v3Position, m_v3Rotation, m_v3Scale);
}

std::shared_ptr<GameObject> GameObject::FindGameObjectByTag(std::string_view strTag) {
    if (strTag == this->GetTag()) {
        return shared_from_this();
    } else {
        return nullptr;
    }
}
