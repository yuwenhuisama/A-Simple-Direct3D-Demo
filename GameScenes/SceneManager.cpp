#include "SceneManager.h"
#include "DxUtils/Direct3DManager.h"
#include "DxUtils/InputManager.h"
#include "GameUtils/Timer.h"
#include "Scene.h"

SceneManager& SceneManager::Instance() {
    static SceneManager smManager;
    return smManager;
}

void SceneManager::SwitchScene(std::shared_ptr<Scene> pScene) {
    if (m_pCurrentScene != pScene) {
        m_pNewScene = pScene;
    }
}

void SceneManager::StartScene() {
    auto& dD3DManager = Direct3DManager::Instance();
    auto& iInputManager = InputManager::Instance();
    auto& tTimer = Timer::Instance();

    tTimer.Reset();

    if (m_pNewScene) {
        m_pCurrentScene = m_pNewScene;
        m_pNewScene = nullptr;
    }

    do {
        if (m_pCurrentScene) {
            m_pCurrentScene->OnReady();
        }

        while (
            m_pCurrentScene
            && !m_pNewScene
            && dD3DManager.GetApplicationState() == ApplicationState::Running
        ) {
            tTimer.Update();
            m_pCurrentScene->OnUpdate();

            // m_pCurrentScene->Render();
            iInputManager.Update();
            dD3DManager.Update();
        }
        
        if (m_pCurrentScene) {
            m_pCurrentScene->OnRelease();
            m_pCurrentScene = nullptr;
        }

        if (m_pNewScene) {
            m_pCurrentScene = m_pNewScene;
            m_pNewScene = nullptr;
        }
    } while(m_pCurrentScene
            && dD3DManager.GetApplicationState() == ApplicationState::Running);
}

void SceneManager::Render() {
    if (m_pCurrentScene) {
        m_pCurrentScene->Render();
    }
}
