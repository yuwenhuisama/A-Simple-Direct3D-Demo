#include "GameConfigure.h"

#include <array>

GameConfigure& GameConfigure::Instance() {
    static GameConfigure instance;
    return instance;
}

GameConfigure::GameConfigure() : Configure() {}

bool GameConfigure::Initialize(std::string_view strvConfigureFileName) {
    if (!Configure::Initialize(strvConfigureFileName)) {
        return false;
    }

    // car
    assert(this->m_dcDocument.GetObject().HasMember("car") == true);
    auto objCar = this->m_dcDocument.FindMember("car")->value.GetObject();

    m_cCarConfigure.m_fMaxSpeedForward = this->GetFloat(objCar, "max_speed_forward");
    m_cCarConfigure.m_fMinSpeedBack = this->GetFloat(objCar, "min_speed_back");
    m_cCarConfigure.m_fAccSpeedForward = this->GetFloat(objCar, "acc_speed_forward");
    m_cCarConfigure.m_fAccSpeedBack = this->GetFloat(objCar, "acc_speed_back");
    m_cCarConfigure.m_fAccStop = this->GetFloat(objCar, "acc_stop");
    m_cCarConfigure.m_fTurnAngle = this->GetFloat(objCar, "turn_angle");
    m_cCarConfigure.m_fTurnWheelAngle = this->GetFloat(objCar, "turn_wheel_angle");

    // camera
    assert(this->m_dcDocument.HasMember("camera"));
    auto objCamera = this->m_dcDocument.FindMember("camera")->value.GetObject();

    std::vector<float> arrVector;
    arrVector = this->GetFloatArray(objCamera, "default_third_eye_pos");
    m_cCameraConfigure.m_f3DefaultThirdEyePos = { arrVector[0], arrVector[1], arrVector[2] };
    arrVector = this->GetFloatArray(objCamera, "default_third_eye_up");
    m_cCameraConfigure.m_f3DefaultThirdEyeUp = { arrVector[0], arrVector[1], arrVector[2] };
    m_cCameraConfigure.m_fDefaultThirdTheta = this->GetFloat(objCamera, "default_third_theta");
    m_cCameraConfigure.m_fDefaultThirdPhi = this->GetFloat(objCamera, "default_third_phi");
    m_cCameraConfigure.m_fDefaultThirdRotationFactorX = this->GetFloat(objCamera, "default_third_rotation_factor_x");
    m_cCameraConfigure.m_fDefaultThirdRotationFactorY = this->GetFloat(objCamera, "default_third_rotation_factor_y");
    m_cCameraConfigure.m_fDefaultThirdDistance = this->GetFloat(objCamera, "default_third_distance");
    m_cCameraConfigure.m_fThirdMaxDistance = this->GetFloat(objCamera, "third_max_distance");
    m_cCameraConfigure.m_fThirdMinDistance = this->GetFloat(objCamera, "third_min_distance");
    
    arrVector = this->GetFloatArray(objCamera, "default_first_eye_pos");
    m_cCameraConfigure.m_f3DefaultFirstEyePos = { arrVector[0], arrVector[1], arrVector[2] };
    arrVector = this->GetFloatArray(objCamera, "default_first_eye_up");
    m_cCameraConfigure.m_f3DefaultFirstEyeUp = { arrVector[0], arrVector[1], arrVector[2] };
    arrVector = this->GetFloatArray(objCamera, "default_first_eye_direction");
    m_cCameraConfigure.m_f3DefaultFirstEyeDirection = { arrVector[0], arrVector[1], arrVector[2] };
    m_cCameraConfigure.m_fFirstRotationFactorX = this->GetFloat(objCamera, "first_rotation_factor_x");
    m_cCameraConfigure.m_fFirstRotationFactorY = this->GetFloat(objCamera, "first_rotation_factor_y");
    arrVector = this->GetFloatArray(objCamera, "first_eye_pos_adjust");
    m_cCameraConfigure.m_f3FirstEyePosAdjust = { arrVector[0], arrVector[1], arrVector[2] };

    return true;
}
