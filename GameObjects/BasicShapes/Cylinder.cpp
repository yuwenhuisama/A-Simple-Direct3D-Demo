#include "Cylinder.h"
#include "DxUtils/Colors.h"

Cylinder::Cylinder(float fBottomRadius,
        float fTopRadius,
        float fHeight,
        UINT uSliceCount,
        UINT uStackCount):
            m_fBottomRadius(fBottomRadius),
            m_fTopRadius(fTopRadius),
            m_fHeight(fHeight),
            m_uSliceCount(uSliceCount),
            m_uStackCount(uStackCount),
            Shape() {}

Vertex* Cylinder::GetVertexes() {
    return &m_msMesh.GetVertexes()[0];
}

UINT Cylinder::GetVertexesCount() {
    return m_msMesh.GetVertexesSize();
}

UINT* Cylinder::GetIndices() {
    return &m_msMesh.GetIndices()[0];
}

UINT Cylinder::GetIndicesCount() {
    return m_msMesh.GetIndicesSize();
}

void Cylinder::PreInitialize() {
    m_msMesh.Clear();

    float fStackHeight = m_fHeight / m_uStackCount;
    float fRadiusStep = (m_fTopRadius - m_fBottomRadius) / m_uStackCount;

    // vertex
    UINT uRingCount = m_uStackCount + 1;
    for (auto i = 0u; i < uRingCount; ++i) {
        float y = -0.5f * m_fHeight + i * fStackHeight;
        float r = m_fBottomRadius + i * fRadiusStep;

        float theta = DirectX::XM_2PI / m_uSliceCount;
        for (auto j = 0u; j <= m_uSliceCount; ++j) {
            Vertex vMeshVertex;

            float c = cosf(j * theta);
            float s = sinf(j * theta);

            vMeshVertex.m_f3Pos = DirectX::XMFLOAT3(r * c, y, r * s);
            // vMeshVertex.m_fColor = Colors::RandomColor();

            vMeshVertex.m_f2Tex0.x = static_cast<float>(j) / m_uSliceCount;
            vMeshVertex.m_f2Tex0.y = 1.0f - static_cast<float>(i) / m_uStackCount;

            vMeshVertex.m_f3Tangent = DirectX::XMFLOAT3(-s, 0.0f, c);

            float dr = m_fBottomRadius - m_fTopRadius;
            DirectX::XMFLOAT3 bitangent(dr * c, -m_fHeight, dr * s);

            auto T = DirectX::XMLoadFloat3(&vMeshVertex.m_f3Tangent);
            auto B = DirectX::XMLoadFloat3(&bitangent);
            auto N = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(T, B));

            DirectX::XMStoreFloat3(&vMeshVertex.m_f3Normal, N);

            m_msMesh.AppendVertex(vMeshVertex);
        }
    }

    // index
    UINT uRingVertexCount = m_uSliceCount + 1;
    for (auto i = 0u; i < m_uStackCount; ++i) {
        for (auto j = 0u; j < m_uSliceCount; ++j) {
            m_msMesh.AppendIndex(i * uRingVertexCount + j);
            m_msMesh.AppendIndex((i + 1) * uRingVertexCount + j);
            m_msMesh.AppendIndex((i + 1) * uRingVertexCount + j + 1);

            m_msMesh.AppendIndex(i * uRingVertexCount + j);
            m_msMesh.AppendIndex((i + 1) * uRingVertexCount + j + 1);
            m_msMesh.AppendIndex(i * uRingVertexCount + j + 1);
        }
    }

    _BuildTopCap();
    _BuidBottomCap();
}

void Cylinder::_BuildTopCap() {
    UINT uBaseIndex = m_msMesh.GetVertexesSize();

    float y = 0.5f * m_fHeight;
    float theta = DirectX::XM_2PI / m_uSliceCount;

    for (auto i = 0u; i <= m_uSliceCount; ++i) {
        float x = m_fTopRadius * cosf(i * theta);
        float z = m_fTopRadius * sinf(i * theta);

        float u = x / m_fHeight + 0.5f;
        float v = z / m_fHeight + 0.5f;

        m_msMesh.AppendVertex(
            { {x, y, z}, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { u, v } }
        );
    }

    m_msMesh.AppendVertex(
        { {0.0f, y, 0.0f}, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f}, { 0.5f, 0.5f } }
    );

    UINT uCenterIndex = m_msMesh.GetVertexesSize() - 1;

    for (auto i = 0u; i < m_uSliceCount; ++i) {
        m_msMesh.AppendIndex(uCenterIndex);
        m_msMesh.AppendIndex(uBaseIndex + i + 1);
        m_msMesh.AppendIndex(uBaseIndex + i);
    }
}

void Cylinder::_BuidBottomCap() {
    UINT uBaseIndex = m_msMesh.GetVertexesSize();

    float y = -0.5f * m_fHeight;
    float theta = DirectX::XM_2PI / m_uSliceCount;

    for (auto i = 0u; i <= m_uSliceCount; ++i) {
        float x = m_fBottomRadius * cosf(i * theta);
        float z = m_fBottomRadius * sinf(i * theta);

        float u = x / m_fHeight + 0.5f;
        float v = z / m_fHeight + 0.5f;

        m_msMesh.AppendVertex(
            { {x, y, z}, { 0.0f, -1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { u, v } }
        );
    }

    m_msMesh.AppendVertex(
        { {0.0f, y, 0.0f}, { 0.0f, -1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f}, { 0.5f, 0.5f } }
    );

    UINT uCenterIndex = m_msMesh.GetVertexesSize() - 1;

    for (auto i = 0u; i < m_uSliceCount; ++i) {
        m_msMesh.AppendIndex(uCenterIndex);
        m_msMesh.AppendIndex(uBaseIndex + i);
        m_msMesh.AppendIndex(uBaseIndex + i + 1);
    }
}
