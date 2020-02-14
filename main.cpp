#include <iostream>

#include "DxUtils/D3DHelper.hpp"
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
    auto& gConfigure = GameConfigure::Instance();
    if (gConfigure.Initialize("game_configure.json")) {
        auto wstrTitle = D3DHelper::StringToWString(gConfigure.GetWindowConfigure().m_strTitle);
        auto i2Size = gConfigure.GetWindowConfigure().m_i2Size;

        if (Direct3DManager::Instance().Initialize(hInstance, wstrTitle, i2Size.x, i2Size.y, true)
            && InputManager::Instance().Initialize(hInstance)) {
        
            Direct3DManager::Instance().StartWindow(nCmdShow);

            Timer::Instance().Initialize();

            auto pScene = std::make_shared<MainScene>();
            SceneManager::Instance().SwitchScene(pScene);
            SceneManager::Instance().StartScene();

            Direct3DManager::Instance().Release();
            InputManager::Instance().Release();
        }
    }

    return 0;
}
