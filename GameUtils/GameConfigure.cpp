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

    // random ground
    assert(this->m_dcDocument.HasMember("random_ground"));
    auto objGround = this->m_dcDocument.FindMember("random_ground")->value.GetObject();

    m_cRandomGroundConfigure.m_vcTextures = this->GetStringArray(objGround, "textures");
    m_cRandomGroundConfigure.m_uRandomModelTypes = this->GetInt(objGround, "random_model_types");
    m_cRandomGroundConfigure.m_uGenerateLevelFrom = this->GetInt(objGround, "generate_level_from");
    m_cRandomGroundConfigure.m_uGenerateLevelTo= this->GetInt(objGround, "generate_level_to");
    m_cRandomGroundConfigure.m_fGenerateRate = this->GetFloat(objGround, "generate_rate");
    m_cRandomGroundConfigure.m_fModelMinScaleRate = this->GetFloat(objGround, "model_min_scale_rate");
    m_cRandomGroundConfigure.m_fModelMaxScaleRate = this->GetFloat(objGround, "model_max_scale_rate");
    m_cRandomGroundConfigure.m_fMinRegionSize = this->GetFloat(objGround, "min_region_size");
    
    auto vcFloats = this->GetFloatArray(objGround, "region");
    m_cRandomGroundConfigure.m_f4Region = { vcFloats[0], vcFloats[1], vcFloats[2], vcFloats[3] };

    // sky box
    assert(this->m_dcDocument.HasMember("skybox"));
    auto objSkyBox = this->m_dcDocument.FindMember("skybox")->value.GetObject();
    m_cSkyBoxConfigure.m_strTexture = this->GetString(objSkyBox, "texture");
    vcFloats = this->GetFloatArray(objSkyBox, "size");
    m_cSkyBoxConfigure.m_f3Size = { vcFloats[0], vcFloats[1], vcFloats[2] };

    // light
    assert(this->m_dcDocument.HasMember("light"));
    auto objLight = this->m_dcDocument.FindMember("light")->value.GetObject();
    vcFloats = this->GetFloatArray(objLight, "position");
    m_cLightConfigure.m_f3Position = { vcFloats[0], vcFloats[1], vcFloats[2] };
    vcFloats = this->GetFloatArray(objLight, "light_eye_position");
    m_cLightConfigure.m_f3LightEyePosition = { vcFloats[0], vcFloats[1], vcFloats[2] };
    vcFloats = this->GetFloatArray(objLight, "projection_region");
    m_cLightConfigure.m_f4ProjectionRegion = { vcFloats[0], vcFloats[1], vcFloats[2], vcFloats[3] };
    auto vcInts = this->GetIntArray(objLight, "shadow_map_textue_size");
    m_cLightConfigure.m_i2ShadowMapTextureSize = { vcInts[0], vcInts[1] };

    return true;
}
