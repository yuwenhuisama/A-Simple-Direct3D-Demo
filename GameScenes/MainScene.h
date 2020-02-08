#ifndef _H_MAINSCENE_
#define _H_MAINSCENE_

#include <memory>
#include "Scene.h"

class CarController;
class MainScene: public Scene {
private:
    std::shared_ptr<CarController> m_pCarController;

public:
    MainScene() = default;
    ~MainScene() = default;

    virtual void OnReady();
    virtual void OnUpdate();
    virtual void OnRelease();
};

#endif // !_H_MAINSCENE_
