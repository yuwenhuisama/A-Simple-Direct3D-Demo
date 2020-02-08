#ifndef _H_SCENEMANAGER_
#define _H_SCENEMANAGER_

#include <memory>

class Scene;
class SceneManager {
private:
    std::shared_ptr<Scene> m_pCurrentScene = nullptr;
    std::shared_ptr<Scene> m_pNewScene = nullptr;

private:
    SceneManager() = default;
    ~SceneManager() = default;

public:
    static SceneManager& Instance();

    void Render();

    void SwitchScene(std::shared_ptr<Scene> pScene);
    void StartScene();
};


#endif // !_H_SCENEMANAGER_
