#include "InstancedGameObject.h"
#include "DxUtils/Direct3DManager.h"
#include "DxUtils/RenderCommandQueue/RenderCommandQueueManager.h"

InstancedGameObject::InstancedGameObject(std::shared_ptr<GameObject> pInstancedGameObject)
    : GameObject(), m_pInstancedGameObject(pInstancedGameObject) {
}

void InstancedGameObject::Update() {
    for (auto&& info : m_lsInstancedInfoList) {
        info.m_fUpdate(info);
    }
}

DirectX::XMMATRIX InstancedGameObject::GetWorldMatrix() const {
    return DirectX::XMMatrixIdentity();
}

void InstancedGameObject::Render() {
    auto& rManager = RenderCommandQueueManager::Instance();
    
    rManager.Push(RenderCommand { RenderCommandType::BeginInstance, nullptr });
    rManager.Push(RenderCommand { RenderCommandType::SetInstancedInfo, &m_lsInstancedInfoList });
    this->m_pInstancedGameObject->Render();

    rManager.Push(RenderCommand { RenderCommandType::EndInstance, nullptr });
}

void InstancedGameObject::AppendInstancedInfo(InstancedInfo& iiInfo) {
    m_lsInstancedInfoList.push_back(iiInfo);
}
