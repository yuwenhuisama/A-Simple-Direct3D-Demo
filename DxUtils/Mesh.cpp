#include "Mesh.h"

void Mesh::AppendVertex(const Vertex& vtVertex) {
    m_vcVertexes.push_back(vtVertex);
}

void Mesh::AppendIndex(UINT uIndex) {
    m_vcIndices.push_back(uIndex);
}

void Mesh::Clear() {
    m_vcVertexes.clear();
    m_vcIndices.clear();
}
