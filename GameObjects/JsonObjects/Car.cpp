#include "Car.h"

#include "GameObjects/InstancedGameObject.h"
#include "GameObjects/BasicShapes/Cylinder.h"

Car::Car() : JsonModel() {}

Car::~Car() {}

std::string Car::GetJsonFilePath() {
    return "SimpleModels/car.json";
}

void Car::SetWheelAngle(float fAngle) {
    auto& iter = m_pWheel->GetAssignedInstancedInfo().begin();
    auto& infoWheel0 = *iter++;
    auto& infoWheel1 = *iter;

    infoWheel0.m_v3Rotation.x = fAngle;
    infoWheel1.m_v3Rotation.x = fAngle;
}

void Car::SetWheelRollAngle(float fAngle) {
    for (auto&& info : m_pWheel->GetAssignedInstancedInfo()) {
        info.m_v3Rotation.y = fAngle;
    }
}

void Car::Update() {
}

float Car::GetWheelRadius() const {
    if (m_pWheel) {
        auto pWheel = std::dynamic_pointer_cast<Cylinder>(m_pWheel->GetInnerGameObject());
        return pWheel->GetTopRadius();
    }
    return 0.0f;
}

bool Car::Initialize() {
    if (!JsonModel::Initialize()) {
        return false;
    }

    m_pWheel = std::dynamic_pointer_cast<InstancedGameObject>(this->FindGameObjectByTag("wheel"));

    for (auto&& info : m_pWheel->GetAssignedInstancedInfo()) {
        info.m_arrRotationOrder = { RotationOrderAxis::Y, RotationOrderAxis::X, RotationOrderAxis::Z };
    }

    return true;
}
