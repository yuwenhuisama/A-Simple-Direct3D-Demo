#include "Scene.h"
#include "DxUtils/Direct3DManager.h"

#include "GameObjects/GameObject.h"
#include "GameObjects/SkyBox.h"

void Scene::Render() {
    if (m_pSkyBox) {
        m_pSkyBox->Render();
    }

    for (auto& obj : m_lsGameObjects) {
        obj->Render();
    }
}

void Scene::AddChild(std::shared_ptr<GameObject> pObject) {
    m_lsGameObjects.push_back(pObject);
}

void Scene::RemoveChild(std::shared_ptr<GameObject> pObject) {
    m_lsGameObjects.remove(pObject);
}

std::shared_ptr<GameObject> Scene::FindGameObjectByTag(std::string_view strvTag) {
    for (auto &&pObject : m_lsGameObjects) {
        if (auto pResult = pObject->FindGameObjectByTag(strvTag)) {
            return pResult;
        }
    }
    return nullptr;
}

