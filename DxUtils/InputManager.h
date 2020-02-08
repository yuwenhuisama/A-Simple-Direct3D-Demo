#ifndef _H_INPUTMANAGER_
#define _H_INPUTMANAGER_

#include <Windows.h>
#include <dinput.h>
#include <dinputd.h>

#include "DxUtils/Direct3DManager.h"

class InputManager {
private:
    IDirectInputDevice8* m_pKeyBoardInputDevice = nullptr;
    IDirectInputDevice8* m_pMouseInputDevice = nullptr;

    char m_arrKeyBoardBuffer[256];
    DIMOUSESTATE m_stMouseBuffer;

private:
    InputManager() = default;
    ~InputManager();

public:
    static InputManager& Instance();

    bool Initialize(HINSTANCE hInstance);
    void Update();

    bool IsKeyDown(BYTE dwKeyCode) const;
    bool IsMouseLeftButtonDown() const;
    bool IsMouseRightButtonDown() const;

};

#endif // !_H_INPUTMANAGER_
