#ifndef _H_CUBOID_
#define _H_CUBOID_

#include "Shape.h"
#include "DxUtils/Mesh.h"

class Cuboid: public Shape {
private:
    float m_fWidth = 0.0f;
    float m_fHeight = 0.0f;
    float m_fDepth = 0.0f;

    Mesh m_msMesh;

public:
    Cuboid() = delete;
    Cuboid(float fWidth, float fHeight, float fDepth);
    ~Cuboid() = default;

    virtual Vertex* GetVertexes() override;
    virtual UINT GetVertexesCount() override;
    virtual UINT* GetIndices() override;
    virtual UINT GetIndicesCount() override;

    virtual void PreInitialize() override;
};

#endif // !_H_Cuboid_
