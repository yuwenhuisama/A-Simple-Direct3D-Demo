#include "Cuboid.h"
#include "DxUtils/Colors.h"

Cuboid::Cuboid(float fWidth, float fHeight, float fDepth):
    Shape(), m_fWidth(fWidth), m_fHeight(fHeight), m_fDepth(fDepth) {}

void Cuboid::PreInitialize() {
    const auto w = m_fWidth / 2.0f;
    const auto h = m_fHeight / 2.0f;
    const auto d = m_fDepth / 2.0f;

    Vertex arrVertecis[] = {
        { DirectX::XMFLOAT3(-w, -h, -d), (Colors::White)  },
        { DirectX::XMFLOAT3(-w, +h, -d), (Colors::Black)  },
        { DirectX::XMFLOAT3(+w, +h, -d), (Colors::Red)    },
        { DirectX::XMFLOAT3(+w, -h, -d), (Colors::Green)  },

        { DirectX::XMFLOAT3(-w, -h, +d), (Colors::Blue)   },
        { DirectX::XMFLOAT3(+w, -h, +d), (Colors::Yellow) },
        { DirectX::XMFLOAT3(+w, +h, +d), (Colors::Cyan)   },
        { DirectX::XMFLOAT3(-w, +h, +d), (Colors::Magenta)},

        { DirectX::XMFLOAT3(-w, +h, -d), (Colors::White)  },
        { DirectX::XMFLOAT3(-w, +h, +d), (Colors::Black)  },
        { DirectX::XMFLOAT3(+w, +h, +d), (Colors::Red)    },
        { DirectX::XMFLOAT3(+w, +h, -d), (Colors::Green)  },

        { DirectX::XMFLOAT3(-w, -h, -d), (Colors::Blue)   },
        { DirectX::XMFLOAT3(+w, -h, -d), (Colors::Yellow) },
        { DirectX::XMFLOAT3(+w, -h, +d), (Colors::Cyan)   },
        { DirectX::XMFLOAT3(-w, -h, +d), (Colors::Magenta)},

        { DirectX::XMFLOAT3(-w, -h, +d), (Colors::White)  },
        { DirectX::XMFLOAT3(-w, +h, +d), (Colors::Black)  },
        { DirectX::XMFLOAT3(-w, +h, -d), (Colors::Red)    },
        { DirectX::XMFLOAT3(-w, -h, -d), (Colors::Green)  },

        { DirectX::XMFLOAT3(+w, -h, -d), (Colors::Blue)   },
        { DirectX::XMFLOAT3(+w, +h, -d), (Colors::Yellow) },
        { DirectX::XMFLOAT3(+w, +h, +d), (Colors::Cyan)   },
        { DirectX::XMFLOAT3(+w, -h, +d), (Colors::Magenta)},
    };

    m_msMesh.GetVertexes().assign(&arrVertecis[0], &arrVertecis[std::size(arrVertecis)]);

    UINT arrIndices[] = {
        0, 1, 2,
        0, 2, 3,

        4, 5, 6,
        4, 6, 7,

        8, 9, 10,
        8, 10, 11,

        12, 13, 14,
        12, 14, 15,

        16, 17, 18,
        16, 18, 19,

        20, 21, 22,
        20, 22, 23,
    };

    m_msMesh.GetIndices().assign(&arrIndices[0], &arrIndices[std::size(arrIndices)]);
}

Vertex* Cuboid::GetVertexes() {
    return &m_msMesh.GetVertexes()[0];
}

UINT Cuboid::GetVertexesCount() {
    return static_cast<UINT>(m_msMesh.GetVertexesSize());
}

UINT* Cuboid::GetIndices() {
    return &m_msMesh.GetIndices()[0];
}

UINT Cuboid::GetIndicesCount() {
    return static_cast<UINT>(m_msMesh.GetIndicesSize());
}
