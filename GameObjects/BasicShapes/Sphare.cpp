#include "Sphare.h"
#include "DxUtils/Colors.h"

Sphare::Sphare(float fRadius, UINT uStackCount, UINT uSliceCount): 
        Shape(),
        m_fRadius(fRadius),
        m_uSliceCount(uStackCount),
        m_uStackCount(uSliceCount) {}

Vertex* Sphare::GetVertexes() {
    return &m_msMesh.GetVertexes()[0];
}

UINT Sphare::GetVertexesCount() {
    return m_msMesh.GetVertexesSize();
}

UINT* Sphare::GetIndices() {
    return &m_msMesh.GetIndices()[0];
}

UINT Sphare::GetIndicesCount() {
    return m_msMesh.GetIndicesSize();
}

void Sphare::PreInitialize() {
    m_msMesh.Clear();    

    Vertex vtTopVertex { { 0.0f, +m_fRadius, 0.0f }, { 0.0f, +1.0f, 0.0f }, { 1.0f, 0.0, 0.0 }, { 0.0, 0.0f } };
    Vertex vtBottomVertex { { 0.0f, -m_fRadius, 0.0f }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 0.0, 0.0 }, { 0.0, 1.0f } };

    m_msMesh.AppendVertex(vtTopVertex);

    float fPhiStep = DirectX::XM_PI / m_uStackCount;
    float fThetaStep = DirectX::XM_2PI / m_uSliceCount;

    for (auto i = 1u; i < m_uStackCount; ++i) {
        float phi = i * fPhiStep;

        for (auto j = 0u; j <= m_uSliceCount; ++j) {
            float theta = j * fThetaStep;

            Vertex vtMeshVertex;

            vtMeshVertex.m_f3Pos.x = m_fRadius * sinf(phi) * cosf(theta);
            vtMeshVertex.m_f3Pos.y = m_fRadius * cosf(phi);
            vtMeshVertex.m_f3Pos.z = m_fRadius * sinf(phi) * sinf(theta);

            // vtMeshVertex.m_fColor = Colors::RandomColor();
            vtMeshVertex.m_f3Tangent.x = -m_fRadius * sinf(phi) * sinf(theta);
            vtMeshVertex.m_f3Tangent.y = 0.0f;
            vtMeshVertex.m_f3Tangent.z = +m_fRadius * sinf(phi) * cosf(theta);

            auto T = DirectX::XMLoadFloat3(&vtMeshVertex.m_f3Tangent);
            DirectX::XMStoreFloat3(&vtMeshVertex.m_f3Tangent, DirectX::XMVector3Normalize(T));

            auto P = DirectX::XMLoadFloat3(&vtMeshVertex.m_f3Pos);
            DirectX::XMStoreFloat3(&vtMeshVertex.m_f3Normal, DirectX::XMVector3Normalize(P));

            vtMeshVertex.m_f2Tex0.x = theta / DirectX::XM_2PI;
            vtMeshVertex.m_f2Tex0.y = phi / DirectX::XM_PI;

            m_msMesh.AppendVertex(vtMeshVertex);
        }
    }

    m_msMesh.AppendVertex(vtBottomVertex);

    for (auto i = 1u; i <= m_uSliceCount; ++i) {
        m_msMesh.AppendIndex(0);
        m_msMesh.AppendIndex(i + 1);
        m_msMesh.AppendIndex(i);
    }

    UINT uBaseIndex = 1;
    UINT uRingVertexCount = m_uSliceCount + 1;

    for (auto i = 0u; i < m_uStackCount - 2; ++i) {
        for (auto j = 0u; j < m_uSliceCount; ++j) {
            m_msMesh.AppendIndex(uBaseIndex + i * uRingVertexCount + j);
            m_msMesh.AppendIndex(uBaseIndex + i * uRingVertexCount + j + 1);
            m_msMesh.AppendIndex(uBaseIndex + (i + 1) * uRingVertexCount + j);

            m_msMesh.AppendIndex(uBaseIndex + (i + 1) * uRingVertexCount + j);
            m_msMesh.AppendIndex(uBaseIndex + i * uRingVertexCount + j + 1);
            m_msMesh.AppendIndex(uBaseIndex + (i + 1) * uRingVertexCount + j + 1);
        }
    }

    UINT uBottomPoleIndex = m_msMesh.GetVertexesSize() - 1;
    uBaseIndex = uBottomPoleIndex - uRingVertexCount;

    for (auto i = 0u; i < m_uSliceCount; ++i) {
        m_msMesh.AppendIndex(uBottomPoleIndex);
        m_msMesh.AppendIndex(uBaseIndex + i);
        m_msMesh.AppendIndex(uBaseIndex + i + 1);
    }
}
