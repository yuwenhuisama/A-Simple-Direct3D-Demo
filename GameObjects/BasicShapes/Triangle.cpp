#include "Triangle.h"
#include "DxUtils/Colors.h"

Triangle::Triangle() : Shape() {}

void Triangle::PreInitialize() {}

Vertex* Triangle::GetVertexes() {
    static Vertex arrVertecis[] = {
        { DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f), (Colors::White)  },
        { DirectX::XMFLOAT3(0.0f, +1.0f, 0.0f), (Colors::Black)  },
        { DirectX::XMFLOAT3(+1.0f, 0.0f, 0.0f), (Colors::Red)    },
    };

    return arrVertecis;
}

UINT Triangle::GetVertexesCount() {
    return 3;
}

UINT* Triangle::GetIndices() {
    static UINT arrIndex[] = {
        // 前表面
        0, 1, 2,
    };
    return arrIndex;
}

UINT Triangle::GetIndicesCount() {
    return 3;
}
