#include "Factory.h"


Factory::Factory(int cap) : capacity(cap), count(0) {
    vehicles = new Vehicle*[capacity];
}

Factory::~Factory() {
    for (int i = 0; i < count; i++) {
        delete vehicles[i];
    }
    delete[] vehicles;
}

void Factory::addVehicle(Vehicle* vehicle) {
    if (this->count < this->capacity) {
        vehicles[count++] = vehicle; // 添加车辆
    } else {
        cout << "Factory is full, cannot add more vehicles!" << endl;
    }
}

void Factory::listAllVehicles() const {
    for (int i = 0; i < this->count; i++) {
        vehicles[i]->displayInfo(); // 调用每辆车的显示信息方法
    }
}

void Factory::listCombustionVehicles() const {
    for (int i = 0; i < this->count; i++) {
        if (typeid(*vehicles[i]) == typeid(CombustionVehicle)) {
            vehicles[i]->displayInfo();
        }
    }
}

void Factory::listElectricVehicles() const {
    for (int i = 0; i < this->count; i++) {
        if (typeid(*vehicles[i]) == typeid(ElectricVehicle)) {
            vehicles[i]->displayInfo();
        }
    }
}

double Factory::calculateTotalCombustionCost() const {
    double totalCost = 0;
    for (int i = 0; i < this->count; i++) {
        if (typeid(*vehicles[i]) == typeid(CombustionVehicle)) { 
            totalCost += vehicles[i]->calculateCost();
        }
    }
    return totalCost;
}

double Factory::calculateTotalElectricCost() const {
    double totalCost = 0;
    for (int i = 0; i < this->count; i++) {
        if (typeid(*vehicles[i]) == typeid(ElectricVehicle)) {
            totalCost += vehicles[i]->calculateCost();
            // vehicles[i]->displayInfo();
        }
    }
    return totalCost;
}

double Factory::calculateTotalCost() const {
    double totalCost = 0;
    for (int i = 0; i < this->count; i++) {
        totalCost += vehicles[i]->calculateCost();
        // vehicles[i]->displayInfo(); 
    }
    return totalCost;
}