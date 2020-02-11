#include "GameObject.h"
#include "DxUtils/D3DHelper.hpp"

DirectX::XMMATRIX GameObject::GetWorldMatrix() const {
    return D3DHelper::CalcWorldMatrix(m_v3Position, m_v3Rotation, m_v3Scale, m_arrRotationOrder);
}

std::shared_ptr<GameObject> GameObject::FindGameObjectByTag(std::string_view strTag) {
    if (strTag == this->GetTag()) {
        return shared_from_this();
    } else {
        return nullptr;
    }
}
