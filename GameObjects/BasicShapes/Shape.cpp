#include "Shape.h"
#include "DxUtils/Direct3DManager.h"
#include "DxUtils/Vertex.h"

#include "DxUtils/D3DHelper.hpp"

#include "DxUtils/RenderCommandQueue/RenderCommandQueueManager.h"

#include <d3d11.h>

Shape::Shape(): GameObject() {}

void Shape::Initialize() {
    this->PreInitialize();

    // --------------- Vertex Buffer ----------------
    D3D11_BUFFER_DESC bdDesc;
    bdDesc.Usage = D3D11_USAGE_IMMUTABLE;
    bdDesc.ByteWidth = sizeof(Vertex) * this->GetVertexesCount();
    bdDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bdDesc.CPUAccessFlags = 0;
    bdDesc.MiscFlags = 0;
    bdDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA ssInitData;
    ssInitData.pSysMem = this->GetVertexes();

    auto result = Direct3DManager::Instance().CreateBuffer(bdDesc, ssInitData, m_pVertexBuffer);

    if (!result) {
        throw("Error when create buffer.");
    }

    // --------------- Index Buffer ----------------
    D3D11_BUFFER_DESC bdiDesc;
    bdiDesc.Usage = D3D11_USAGE_IMMUTABLE;
    bdiDesc.ByteWidth = sizeof(UINT) * this->GetIndicesCount();
    bdiDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bdiDesc.CPUAccessFlags = 0;
    bdiDesc.MiscFlags = 0;
    bdiDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA ssiInitData;
    ssiInitData.pSysMem = this->GetIndices();

    result = Direct3DManager::Instance().CreateBuffer(bdiDesc, ssiInitData, m_pIndexedBuffer);

    if (!result) {
        throw("Error when create buffer.");
    }
}

void Shape::Update() {

}

void Shape::Render() {
    std::function<DirectX::XMMATRIX(void)> fCallback = 
            [this]() -> DirectX::XMMATRIX { return this->GetWorldMatrix(); };

    RenderCommandQueueManager::Instance().Push(
        RenderCommand { RenderCommandType::SetWorldMatrix,
            fCallback,
        }
    );

    RenderCommandQueueManager::Instance().Push(
        RenderCommand { RenderCommandType::Render,
            std::make_tuple(this->m_pVertexBuffer, this->m_pIndexedBuffer, sizeof(Vertex), this->GetIndicesCount())
        }
    );
}

Shape::~Shape() {
    D3DHelper::SafeRelease(m_pIndexedBuffer);
    D3DHelper::SafeRelease(m_pVertexBuffer);
}
