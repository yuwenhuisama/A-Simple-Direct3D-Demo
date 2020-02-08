#ifndef  _H_TRIANGLE_
#define  _H_TRIANGLE_

#include "Shape.h"

class Triangle : public Shape {
public:
    Triangle();
    virtual ~Triangle() = default;

    virtual Vertex* GetVertexes() override;
    virtual UINT GetVertexesCount() override;
    virtual UINT* GetIndices() override;
    virtual UINT GetIndicesCount() override;

    virtual void PreInitialize() override;
};

#endif // ! _H_TRIANGLE_