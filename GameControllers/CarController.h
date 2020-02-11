#ifndef _H_CARCONTROLLRE_
#define _H_CARCONTROLLRE_

#include <memory>
#include "GameObjects/JsonObjects/Car.h"

class CarController {
private:
    std::weak_ptr<Car> m_pCar;
    
    DirectX::XMVECTOR m_v3Position { 0.0f, 0.0f, 0.0f };
    DirectX::XMVECTOR m_v3Direction { 0.0f, 0.0f, 1.0f };
    float m_fSpeed = 0.0f;
    float m_fAngle = 0.0f;

    float m_fWheelAngle = 0.0f;

public:
    CarController() = delete;
    CarController(std::shared_ptr<Car> pCar);
    ~CarController() = default;

    void Update();

    DirectX::XMVECTOR GetDirection() const { return m_v3Direction; }

    float GetWheelRadius() const;
};

#endif // !_H_CARCONTROLLRE_