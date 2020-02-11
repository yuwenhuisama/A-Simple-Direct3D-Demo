#include <iostream>

#include "DxUtils/Direct3DManager.h"
#include "DxUtils/InputManager.h"

#include "GameScenes/SceneManager.h"
#include "GameScenes/MainScene.h"
#include "GameUtils/Timer.h"

#include "GameUtils/GameConfigure.h"

int _stdcall WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
) {
    if (Direct3DManager::Instance().Initialize(hInstance, 1024, 768, true)
        && InputManager::Instance().Initialize(hInstance)
        && GameConfigure::Instance().Initialize("game_configure.json")) {
        Direct3DManager::Instance().StartWindow(nCmdShow);

        Timer::Instance().Initialize();

        auto pScene = std::make_shared<MainScene>();
        SceneManager::Instance().SwitchScene(pScene);
        SceneManager::Instance().StartScene();
    }

    return 0;
}
