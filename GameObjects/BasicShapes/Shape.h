#ifndef _H_SHAPE_
#define _H_SHAPE_

#include "GameObjects/GameObject.h"
#include <Windows.h>

struct Vertex;

class Shape: public GameObject {
protected:
    ID3D11Buffer* m_pVertexBuffer = nullptr;
    ID3D11Buffer* m_pIndexedBuffer = nullptr;

public:
    Shape();
    virtual ~Shape();

    virtual Vertex* GetVertexes() = 0;
    virtual UINT GetVertexesCount() = 0;
    virtual UINT* GetIndices() = 0;
    virtual UINT GetIndicesCount() = 0;

    virtual void PreInitialize() = 0;
    
    virtual void Initialize();

    virtual void Update() override;
    virtual void Render() override;

    ID3D11Buffer* GetVertexBuffer() const { return m_pVertexBuffer; }
    ID3D11Buffer* GetIndexedBuffer() const { return m_pIndexedBuffer; }

};

#endif // !_H_SHAPE_
