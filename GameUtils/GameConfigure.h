#ifndef _H_GAMECONFIGURE_
#define _H_GAMECONFIGURE_

#include "Configure.h"
#include <DirectXMath.h>

struct CarConfigure {
    float m_fMaxSpeedForward = 0.0f;
    float m_fMinSpeedBack = 0.0f;
    float m_fAccSpeedForward = 0.0f;
    float m_fAccSpeedBack = 0.0f;
    float m_fAccStop = 0.0f;
    float m_fTurnAngle = 0.0f;
    float m_fTurnWheelAngle = 0.0f;
};

struct CameraConfigure {
    DirectX::XMFLOAT3 m_f3DefaultThirdEyePos = { 0.0f, 0.0f, 0.0f};
    DirectX::XMFLOAT3 m_f3DefaultThirdEyeUp = { 0.0f, 0.0f, 0.0f};
    float m_fDefaultThirdTheta = 0.0f;
    float m_fDefaultThirdPhi = 0.0f;
    float m_fDefaultThirdRotationFactorX = 0.0f;
    float m_fDefaultThirdRotationFactorY = 0.0f;
    float m_fDefaultThirdDistance = 0.0f;
    float m_fThirdMaxDistance = 0.0f;
    float m_fThirdMinDistance = 0.0f;

    DirectX::XMFLOAT3 m_f3DefaultFirstEyePos = { 0.0f, 0.0f, 0.0f };
    DirectX::XMFLOAT3 m_f3DefaultFirstEyeUp = { 0.0f, 0.0f, 0.0f };
    DirectX::XMFLOAT3 m_f3DefaultFirstEyeDirection = { 0.0f, 0.0f, 0.0f};
    float m_fFirstRotationFactorX = 0.0f;
    float m_fFirstRotationFactorY = 0.0f;
    DirectX::XMFLOAT3 m_f3FirstEyePosAdjust = { 0.0f, 0.0f, 0.0f};

};

class GameConfigure : public Configure {
private:
    CarConfigure m_cCarConfigure;
    CameraConfigure m_cCameraConfigure;

private:
    GameConfigure();
    virtual ~GameConfigure() = default;

public:
    static GameConfigure& Instance();
    virtual bool Initialize(std::string_view strvConfigureFileName) override;

    const CarConfigure& GetCarConfigure() const { return m_cCarConfigure; }
    const CameraConfigure& GetCameraConfigure() const { return m_cCameraConfigure; }
};

#endif
