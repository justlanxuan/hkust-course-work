#ifndef VEHICLE_H
#define VEHICLE_H


#include <string>
#include <iostream>




using namespace std;

class Vehicle {
protected:
    string model;
    double price;
    int yearOfProduction;
public:
    Vehicle(const string& model, double price, int yearOfProduction);
    virtual void displayInfo() const = 0; 
    virtual double calculateCost() const { return price; }
    virtual ~Vehicle() {}
};

class CombustionVehicle : public Vehicle {
private:
    double fuelConsumption;  // Fuel consumption per 100 kilometers (liters)
    int emissionLevel;       // Emission level
public:
    CombustionVehicle(const string& model, double price, int yearOfProduction, 
                      double fuelConsumption, int emissionLevel);
    double getFuelConsumption() const { return fuelConsumption; }
    int getEmissionLevel() const { return emissionLevel; }
    virtual void displayInfo() const override;
    virtual double calculateCost() const override; // Consider fuel costs
};

class ElectricVehicle : public Vehicle {
//Todo 2.2: Implement the ElectricVehicle class
//(const string& model, double price, int yearOfProduction,int batteryCapacity, int range)
private:
    int batteryCapacity;
    int range;
public:
    // constructor
    ElectricVehicle(const string& model, double price, int yearOfProduction,int batteryCapacity, int range);
    // getBatteryCapacity()
    int getBatteryCapacity() const {return this->batteryCapacity;}
    // getRange
    int getRange() const {return this->range;}
    // displayInfo
    virtual void displayInfo() const override;
    virtual double calculateCost() const override;
};
#endif /* VEHICLE_H */ 