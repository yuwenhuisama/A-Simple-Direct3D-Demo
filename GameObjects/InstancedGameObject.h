#ifndef _H_INSTANCEDGAMEOBJECT_
#define _H_INSTANCEDGAMEOBJECT_

#include "GameObject.h"
#include "DxUtils/D3DHelper.hpp"

class InstancedGameObject : public GameObject {
private:
    std::shared_ptr<GameObject> m_pInstancedGameObject = nullptr;
    std::list<InstancedInfo> m_lsInstancedInfoList;

    InstancedInfo* m_pCurrentInstanced = nullptr;

public:
    InstancedGameObject(std::shared_ptr<GameObject> pInstancedGameObject);

    virtual ~InstancedGameObject() = default;

    virtual void Update();
    virtual void Render();

    virtual DirectX::XMMATRIX GetWorldMatrix() const override;

    void AppendInstancedInfo(InstancedInfo& iiInfo);
    std::list<InstancedInfo>& GetAssignedInstancedInfo() { return m_lsInstancedInfoList; }

    std::shared_ptr<GameObject> GetInnerGameObject() const { return m_pInstancedGameObject; }
};

#endif // !_H_INSTANCEDGAMEOBJECT_
