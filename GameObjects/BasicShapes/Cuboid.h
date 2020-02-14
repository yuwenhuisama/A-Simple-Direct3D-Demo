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
    virtual ~Cuboid() = default;

    virtual Vertex* GetVertexes() override;
    virtual UINT GetVertexesCount() override;
    virtual UINT* GetIndices() override;
    virtual UINT GetIndicesCount() override;

    virtual void PreInitialize() override;

    virtual float GetHeight() const { return m_fHeight; }
    virtual float GetWidth() const { return m_fWidth; }
    virtual float GetDepth() const { return m_fDepth; }
};

#endif // !_H_Cuboid_
