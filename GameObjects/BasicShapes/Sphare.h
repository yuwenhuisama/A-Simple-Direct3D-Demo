#ifndef _H_SPHARE_
#define _H_SPHARE_

#include "Shape.h"
#include "DxUtils/Mesh.h"

class Sphare : public Shape {
private:
    float m_fRadius = 0.0f;

    UINT m_uStackCount = 0;
    UINT m_uSliceCount = 0;
    Mesh m_msMesh;

public:
    Sphare() = delete;
    Sphare(float fRadius, UINT uStackCount, UINT uSliceCount);
    virtual ~Sphare() = default;
    
    virtual Vertex* GetVertexes();
    virtual UINT GetVertexesCount();
    virtual UINT* GetIndices();
    virtual UINT GetIndicesCount();

    virtual void PreInitialize();

    virtual float GetRadius() const { return m_fRadius; }
};

#endif // !_H_SPHARE_
