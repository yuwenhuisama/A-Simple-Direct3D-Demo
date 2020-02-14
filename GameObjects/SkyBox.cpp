#include "SkyBox.h"
#include "DxUtils/RenderCommandQueue/RenderCommandQueueManager.h"
#include "DxUtils/Vertex.h"
#include "DxUtils/Direct3DManager.h"
#include "GameUtils/GameConfigure.h"

#include "DxUtils/D3DHelper.hpp"

#include "GameObject.h"

#include <functional>

SkyBox::~SkyBox() {
    D3DHelper::SafeRelease(m_pIndexedBuffer);
    D3DHelper::SafeRelease(m_pVertexBuffer);
}


constexpr UINT c_arrIndices[] = {
    0, 1, 2,
    0, 2, 3,

    4, 5, 6,
    4, 6, 7,

    8, 9, 10,
    8, 10, 11,

    12, 13, 14,
    12, 14, 15,

    16, 17, 18,
    16, 18, 19,

    20, 21, 22,
    20, 22, 23,
};

bool SkyBox::_InitializeBuffer() {
    const float uWidth = GameConfigure::Instance().GetSkyBoxConfigure().m_f3Size.x;

    SkyBoxVertex c_arrVertecies[] = {
        { DirectX::XMFLOAT3(-uWidth, -uWidth, -uWidth)},
        { DirectX::XMFLOAT3(-uWidth, +uWidth, -uWidth)},
        { DirectX::XMFLOAT3(+uWidth, +uWidth, -uWidth)},
        { DirectX::XMFLOAT3(+uWidth, -uWidth, -uWidth)},

        { DirectX::XMFLOAT3(-uWidth, -uWidth, +uWidth)},
        { DirectX::XMFLOAT3(+uWidth, -uWidth, +uWidth)},
        { DirectX::XMFLOAT3(+uWidth, +uWidth, +uWidth)},
        { DirectX::XMFLOAT3(-uWidth, +uWidth, +uWidth)},

        { DirectX::XMFLOAT3(-uWidth, +uWidth, -uWidth)},
        { DirectX::XMFLOAT3(-uWidth, +uWidth, +uWidth)},
        { DirectX::XMFLOAT3(+uWidth, +uWidth, +uWidth)},
        { DirectX::XMFLOAT3(+uWidth, +uWidth, -uWidth)},

        { DirectX::XMFLOAT3(-uWidth, -uWidth, +uWidth)},
        { DirectX::XMFLOAT3(-uWidth, +uWidth, +uWidth)},
        { DirectX::XMFLOAT3(-uWidth, +uWidth, -uWidth)},
        { DirectX::XMFLOAT3(-uWidth, -uWidth, -uWidth)},

        { DirectX::XMFLOAT3(-uWidth, -uWidth, -uWidth)},
        { DirectX::XMFLOAT3(+uWidth, -uWidth, -uWidth)},
        { DirectX::XMFLOAT3(+uWidth, -uWidth, +uWidth)},
        { DirectX::XMFLOAT3(-uWidth, -uWidth, +uWidth)},

        { DirectX::XMFLOAT3(+uWidth, -uWidth, -uWidth)},
        { DirectX::XMFLOAT3(+uWidth, +uWidth, -uWidth)},
        { DirectX::XMFLOAT3(+uWidth, +uWidth, +uWidth)},
        { DirectX::XMFLOAT3(+uWidth, -uWidth, +uWidth)},
    };

    // --------------- Vertex Buffer ----------------
    D3D11_BUFFER_DESC bdDesc;
    bdDesc.Usage = D3D11_USAGE_IMMUTABLE;
    bdDesc.ByteWidth = sizeof(c_arrVertecies);
    bdDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bdDesc.CPUAccessFlags = 0;
    bdDesc.MiscFlags = 0;
    bdDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA ssInitData;
    ssInitData.pSysMem = c_arrVertecies;

    auto result = Direct3DManager::Instance().CreateBuffer(bdDesc, ssInitData, m_pVertexBuffer);

    if (!result) {
        throw("Error when create buffer.");
    }

    // --------------- Index Buffer ----------------
    D3D11_BUFFER_DESC bdiDesc;
    bdiDesc.Usage = D3D11_USAGE_IMMUTABLE;
    bdiDesc.ByteWidth = sizeof(c_arrIndices);
    bdiDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bdiDesc.CPUAccessFlags = 0;
    bdiDesc.MiscFlags = 0;
    bdiDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA ssiInitData;
    ssiInitData.pSysMem = c_arrIndices;

    result = Direct3DManager::Instance().CreateBuffer(bdiDesc, ssiInitData, m_pIndexedBuffer);

    if (!result) {
        throw("Error when create buffer.");
    }

    return true;
}

bool SkyBox::Initialize() {
    if (!_InitializeBuffer()) {
        return false;
    }

    return true;
}

void SkyBox::Render() {
    std::function<DirectX::XMMATRIX(void)> fCallBack = [this]() -> DirectX::XMMATRIX {
        if (this->GetBoundObject()) {
            return DirectX::XMMatrixTranslation(
                this->GetBoundObject()->Position().x,
                this->GetBoundObject()->Position().y,
                this->GetBoundObject()->Position().z
            );
        } else {
            return DirectX::XMMatrixIdentity();
        }
    };

    RenderCommandQueueManager::Instance().Push(RenderCommand {
        RenderCommandType::SetTexture,
        m_pTexture
    });

    RenderCommandQueueManager::Instance().Push(RenderCommand {
        RenderCommandType::RenderSkyBox,
        std::make_tuple(m_pVertexBuffer, m_pIndexedBuffer, sizeof(SkyBoxVertex), std::size(c_arrIndices), m_pVertexShader, m_pPixelShader, fCallBack)
    });
}
