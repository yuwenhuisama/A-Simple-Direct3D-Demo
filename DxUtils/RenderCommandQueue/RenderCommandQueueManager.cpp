#include "RenderCommandQueueManager.h"
#include "DxUtils/Direct3DManager.h"
#include "DxUtils/D3DHelper.hpp"

RenderCommandQueueManager& RenderCommandQueueManager::Instance() {
    static RenderCommandQueueManager instance;
    return instance;
}

void RenderCommandQueueManager::Initialize() {
    m_lsQueue.clear();
    m_eState = RenderCommandState::Normal;
}

void RenderCommandQueueManager::Push(RenderCommand& rcCommand) {
    m_lsQueue.push_back(rcCommand);
}

void RenderCommandQueueManager::_SetWorldMatrix(RenderCommand& rcCommand) {
    if (m_eState == RenderCommandState::Normal) {
        Direct3DManager::Instance().GetVertexShader()->Apply(rcCommand);
    }
}

using RenderInfo = std::tuple<ID3D11Buffer*, ID3D11Buffer*, size_t, UINT>;
void RenderCommandQueueManager::_RenderObject(RenderCommand& rcCommand){
    auto [pVertexBuffer, pIndexedBuffer, uStride, uIndicesCount] = std::any_cast<RenderInfo>(rcCommand.m_objRenderInfo);

    if (m_eState == RenderCommandState::Normal) {
        Direct3DManager::Instance().DrawObjectWithShader(
            pVertexBuffer,
            pIndexedBuffer,
            static_cast<UINT>(uStride),
            uIndicesCount
        );
    } else {
        if (m_pCurInfo) {
            for (auto&& info : *m_pCurInfo) {
                std::function<DirectX::XMMATRIX(void)> fCallback = [this, &info]() -> DirectX::XMMATRIX {
                    return D3DHelper::CalcWorldMatrix(info.m_v3Position, info.m_v3Rotation, info.m_v3Scale) * this->m_mtBuffer;
                };

                Direct3DManager::Instance().GetVertexShader()->Apply(
                    RenderCommand { RenderCommandType::SetWorldMatrix, fCallback }
                );

                Direct3DManager::Instance().DrawObjectWithShader(
                    pVertexBuffer,
                    pIndexedBuffer,
                    static_cast<UINT>(uStride),
                    uIndicesCount
                );
            }
        }
    }
}

void RenderCommandQueueManager::_BeginInstance(RenderCommand& rcCommand) {
    m_eState = RenderCommandState::Instanced;
}

void RenderCommandQueueManager::_EndInstance(RenderCommand& rcCommand) {
    m_eState = RenderCommandState::Normal;
}

void RenderCommandQueueManager::_SetInstancedInfo(RenderCommand& rcCommand) {
    m_pCurInfo = std::any_cast<std::list<InstancedInfo>*>(rcCommand.m_objRenderInfo);
}

void RenderCommandQueueManager::_SetBaseModelRenderInfo(RenderCommand& rcCommand) {
    m_mtBuffer = std::any_cast<std::function<DirectX::XMMATRIX(void)>>(rcCommand.m_objRenderInfo)();
}

void RenderCommandQueueManager::Render() {
    if (!m_lsQueue.empty()) {
        auto iter = m_lsQueue.begin();
        while (iter != m_lsQueue.end()) {
            auto eType = iter->m_eType;
            // dispatch
            switch(eType) {
                case RenderCommandType::Render:
                    this->_RenderObject(*iter);
                    break;
                case RenderCommandType::SetWorldMatrix:
                    this->_SetWorldMatrix(*iter);
                    break;
                case RenderCommandType::BeginInstance:
                    this->_BeginInstance(*iter);
                    break;
                case RenderCommandType::EndInstance:
                    this->_EndInstance(*iter);
                    break;
                case RenderCommandType::SetInstancedInfo:
                    this->_SetInstancedInfo(*iter);
                    break;
                case RenderCommandType::SetBaseModelRenderInfo:
                    this->_SetBaseModelRenderInfo(*iter);
                    break;
                default:
                    break;
            }
            ++iter;
        }

        m_lsQueue.clear();
    }
}
