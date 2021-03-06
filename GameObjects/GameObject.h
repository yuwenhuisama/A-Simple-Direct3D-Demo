#ifndef _H_GAMEOBJECT_
#define _H_GAMEOBJECT_

#include <memory>
#include <list>
#include <string>
#include <array>

#include <d3d11.h>
#include "DxUtils/Vertex.h"

enum class RotationOrderAxis {
    X = 0,
    Y,
    Z,
};

class GameObject : public std::enable_shared_from_this<GameObject>{
private:
    std::string m_strTag = "";

    DirectX::XMFLOAT3 m_v3Position { 0, 0, 0 };
    DirectX::XMFLOAT3 m_v3Scale { 1.0f, 1.0f, 1.0f };
    DirectX::XMFLOAT3 m_v3Rotation { 0.0f, 0.0f, 0.0f };

    std::array<RotationOrderAxis, 3> m_arrRotationOrder = { RotationOrderAxis::X, RotationOrderAxis::Y, RotationOrderAxis::Z };

public:
    GameObject() = default;
    virtual ~GameObject() = default;

    virtual std::shared_ptr<GameObject> FindGameObjectByTag(std::string_view strTag);

    virtual void Update() = 0;
    virtual void Render() = 0;

    virtual DirectX::XMMATRIX GetWorldMatrix() const;

    DirectX::XMFLOAT3& Position() { return m_v3Position; }
    DirectX::XMFLOAT3& Scale() { return m_v3Scale; }
    DirectX::XMFLOAT3& Rotation() { return m_v3Rotation; }

    void SetTag(std::string_view strvTag) { m_strTag = strvTag; }
    std::string_view GetTag() { return m_strTag; }

    void SetRotationOrder(const std::array<RotationOrderAxis, 3>& arrOrder) { m_arrRotationOrder =  arrOrder; }
    const std::array<RotationOrderAxis, 3>& GetRotationOrder() const { return m_arrRotationOrder; }

};

#endif // !_H_GAME_OBJECT_
