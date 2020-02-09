#include "InputManager.h"
#include "DxUtils/D3DHelper.hpp"

InputManager& InputManager::Instance() {
    static InputManager instance;
    return instance;
}

bool InputManager::Initialize(HINSTANCE hInstance) {
    IDirectInput8* pDirectInputObject = nullptr;

    auto result = DirectInput8Create(hInstance,
        DIRECTINPUT_VERSION,
        IID_IDirectInput8,
        reinterpret_cast<void**>(&pDirectInputObject),
        nullptr);

    if (FAILED(result)) {
        goto failed_exit;
    }

    // create keyboard device
    result = pDirectInputObject->CreateDevice(GUID_SysKeyboard, &m_pKeyBoardInputDevice, nullptr);
    if (FAILED(result)) {
        goto failed_exit;
    }

    // create mouse device
    result = pDirectInputObject->CreateDevice(GUID_SysMouse, &m_pMouseInputDevice, nullptr);   
    if (FAILED(result)) {
        goto failed_exit;
    }

    result = m_pKeyBoardInputDevice->SetDataFormat(&c_dfDIKeyboard);
    if (FAILED(result)) {
        goto failed_exit;
    }

    result = m_pMouseInputDevice->SetDataFormat(&c_dfDIMouse);
    if (FAILED(result)) {
        goto failed_exit;
    }
    
    result = m_pKeyBoardInputDevice->SetCooperativeLevel(
        Direct3DManager::Instance().GetHWND(), 
        DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    if (FAILED(result)) {
        goto failed_exit;
    }

    result = m_pKeyBoardInputDevice->Acquire();
    if (FAILED(result)) {
        goto failed_exit;
    }

    result = m_pMouseInputDevice->Acquire();
    if (FAILED(result)) {
        goto failed_exit;
    }

    D3DHelper::SafeRelease(pDirectInputObject);
    return true;

failed_exit:
    D3DHelper::SafeRelease(pDirectInputObject);
    D3DHelper::SafeRelease(m_pKeyBoardInputDevice);
    D3DHelper::SafeRelease(m_pMouseInputDevice);
    return false;
}

void InputManager::Update() {
    HRESULT result;

    memcpy(m_arrKeyBackBoardBuffer, m_arrKeyBoardBuffer, sizeof(m_arrKeyBackBoardBuffer));

    result = m_pKeyBoardInputDevice->Acquire();
    if (result != DIERR_INPUTLOST) {
        result = m_pKeyBoardInputDevice->GetDeviceState(sizeof(m_arrKeyBoardBuffer), reinterpret_cast<void*>(&m_arrKeyBoardBuffer));
    }

    result =  m_pMouseInputDevice->Acquire();
    if (result != DIERR_INPUTLOST) {
        result = m_pMouseInputDevice->GetDeviceState(sizeof(m_stMouseBuffer), reinterpret_cast<void*>(&m_stMouseBuffer));
    }
}

#define DIKEYDOWN(buffer, n) (buffer[n] & 0x80)
bool InputManager::IsKeyDown(BYTE dwKeyCode) const {
    return DIKEYDOWN(m_arrKeyBoardBuffer, dwKeyCode);
}

bool InputManager::IsKeyTrigger(BYTE dwKeyCode) const {
    return !DIKEYDOWN(m_arrKeyBackBoardBuffer, dwKeyCode)
        && DIKEYDOWN(m_arrKeyBoardBuffer, dwKeyCode);
}

bool InputManager::IsMouseLeftButtonDown() const {
    return DIKEYDOWN(m_stMouseBuffer.rgbButtons, 0);
}

bool InputManager::IsMouseRightButtonDown() const {

    return DIKEYDOWN(m_stMouseBuffer.rgbButtons, 1);
}

InputManager::~InputManager() {
    if (m_pKeyBoardInputDevice) {
        m_pKeyBoardInputDevice->Unacquire();
        D3DHelper::SafeRelease(m_pKeyBoardInputDevice);
    }

    if (m_pMouseInputDevice){
        m_pMouseInputDevice->Unacquire();
        D3DHelper::SafeRelease(m_pMouseInputDevice);
    }
}
