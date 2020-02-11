#ifndef  _H_CYLINDER_
#define _H_CYLINDER_
#include "Shape.h"
#include "DxUtils/Mesh.h"

class Cylinder : public Shape {
private:
    Mesh m_msMesh;
    float m_fBottomRadius = 0.0f;
    float m_fTopRadius = 0.0f;
    float m_fHeight = 0.0f;
    UINT m_uSliceCount = 0u;
    UINT m_uStackCount = 0u;

private:
    void _BuildTopCap();
    void _BuidBottomCap();

public:
    Cylinder() = delete;
    Cylinder(float fBottomRadius,
        float fTopRadius,
        float fHeight,
        UINT uSliceCount,
        UINT uStackCount);
    virtual ~Cylinder() = default;

    virtual Vertex* GetVertexes() override;
    virtual UINT GetVertexesCount() override;
    virtual UINT* GetIndices() override;
    virtual UINT GetIndicesCount() override;

    virtual void PreInitialize() override;

    virtual float GetBottomRadius() const { return m_fBottomRadius; }
    virtual float GetTopRadius() const { return m_fTopRadius; }

    virtual float GetHeight() const { return m_fHeight; }
};

#endif // ! _H_CYLINDER_
