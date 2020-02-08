#ifndef _H_SCENE_
#define _H_SCENE_

#include <list>
#include <memory>
#include "GameObjects/GameObject.h"

class Scene {
private:
    std::list<std::shared_ptr<GameObject>> m_lsGameObjects;

protected:
    virtual void AddChild(std::shared_ptr<GameObject> pObject);
    virtual void RemoveChild(std::shared_ptr<GameObject> pObject);

    virtual std::shared_ptr<GameObject> FindGameObjectByTag(std::string_view strvTag);

public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void Render();

    virtual void OnReady() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnRelease() = 0;

};

#endif // !_H_SCENE_
