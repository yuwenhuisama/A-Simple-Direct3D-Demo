#ifndef _H_CAR_
#define _H_CAR_
#include "JsonModel.h"

class CarController;
class InstancedGameObject;
class Car : public JsonModel {
private:
    std::shared_ptr<CarController> m_pController = nullptr;
    std::shared_ptr<InstancedGameObject> m_pWheel = nullptr;

protected:
    virtual std::string GetJsonFilePath() override;
    virtual void Update() override;

public:
    Car();
    virtual ~Car();

    void SetController(std::shared_ptr<CarController> pController) { m_pController = pController; }
    std::shared_ptr<CarController> GetController() { return m_pController; }

    virtual bool Initialize() override;

    void SetWheelAngle(float fAngle);
    void SetWheelRollAngle(float fAngle);

    float GetWheelRadius() const;
};

#endif // !_H_CAR_
