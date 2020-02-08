#include "Car.h"

Car::Car() : JsonModel() {}

Car::~Car() {}

std::string Car::GetJsonFilePath() {
    return "SimpleModels/car.json";
}

void Car::Update() {

}
