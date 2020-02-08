#ifndef _H_MESH_
#define _H_MESH_

#include <vector>
#include <Windows.h>
#include "Vertex.h"

class Mesh {
private:
    std::vector<Vertex> m_vcVertexes;
    std::vector<UINT> m_vcIndices;

public:
    Mesh() = default;
    ~Mesh() = default;

    void AppendVertex(const Vertex& vtVertex);
    void AppendIndex(UINT uIndex);

    void Clear();

    std::vector<Vertex>& GetVertexes()  { return m_vcVertexes; }
    std::vector<UINT>& GetIndices()  { return m_vcIndices; }

    UINT GetVertexesSize() const { return static_cast<UINT>(m_vcVertexes.size()); }
    UINT GetIndicesSize() const { return static_cast<UINT>(m_vcIndices.size()); }
};

#endif // !_H_MESH_
