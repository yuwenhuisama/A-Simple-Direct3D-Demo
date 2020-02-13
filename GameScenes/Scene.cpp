#include "Scene.h"
#include "DxUtils/Direct3DManager.h"
#include "DxUtils/RenderCommandQueue/RenderCommandQueueManager.h"

#include "GameObjects/GameObject.h"
#include "GameObjects/SkyBox.h"


void Scene::RenderSkyBox() {
    if (m_pSkyBox) {
        m_pSkyBox->Render();
    }
}

void Scene::RenderGameObjects() {
    for (auto& obj : m_lsGameObjects) {
        obj->Render();
    }
}

void Scene::Render() {
    RenderCommandQueueManager::Instance().Push(RenderCommand {
        RenderCommandType::ClearColorBuffer,
        nullptr,
    });

    RenderCommandQueueManager::Instance().Push(RenderCommand {
        RenderCommandType::ClearDepthStencilBuffer,
        nullptr,
    });

    this->RenderSkyBox();
    this->RenderGameObjects();
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

