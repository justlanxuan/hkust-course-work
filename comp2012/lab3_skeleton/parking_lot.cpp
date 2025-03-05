#include "parking_lot.h"
#include <iostream>

ParkingLot::ParkingLot(const string& name, int capacity):name(name),capacity(capacity) {
    // TODO 1: ParkingLot constructor
    cout<<"[Creation] Parking Lot "<<this->name;
    this->num_of_spots = 0; // initialize to 0?
    this->spots = new ParkingSpot*[this->capacity]{};// initialize to nullptr
}

ParkingLot::ParkingLot(const ParkingLot& lot) {
    // TODO 2: ParkingLot copy constructor
    this->name = lot.name;
    this->capacity = lot.capacity;
    this->num_of_spots = 0;
    this->spots = new ParkingSpot*[this->capacity]{};//initialize members to nullptr
    for(int i=0;i<this->capacity;i++){// for all spots
        if(lot.spots[i]!=nullptr){// if there the spot is occupied
            ParkingLot::createSpot(lot.spots[i]->getSpotNumber(),lot.spots[i]->getVehicle());
        }
    }
    cout<<"[Creation] Parking Lot "<<this->name;
}

ParkingLot::~ParkingLot() {
    // TODO 3: ParkingLot destructor
    cout<<"[Destructor] Parking Lot "<<this->name<<endl;
    for(int i=0;i<this->capacity;i++){
        if(this->spots[i]!=nullptr){
            delete spots[i];
        }
    }
    delete [] spots;
}

void ParkingLot::createSpot(const string& spotNumber, Vehicle* vehicle) {
    if (num_of_spots >= capacity) {
        cout << "Cannot create more spots. Parking lot is at capacity." << endl;
        return;
    }
    
    spots[num_of_spots++] = new ParkingSpot(spotNumber, vehicle);
}

bool ParkingLot::addVehicle(Vehicle* vehicle, const string& spotNumber) {
    // TODO 4: addVehicle member function in parkingLot class
    // the vehical is invalid:
    if(vehicle == nullptr){
        cout<<"Invalid vehicle."<<endl;
        return false;
    }
    // if vehicle is parked elsewhere
    for(int i=0;i<this->capacity;i++){
        if(this->spots[i]!=nullptr){
            if(this->spots[i]->getVehicle()==vehicle){
                cout<<"Vehicle "<<vehicle->getLicensePlate()<<" is already parked in spot "<<spots[i]->getSpotNumber()<<endl;
                return false;
            }
        }
    }
    // if the parking spot is occupied
    for(int i=0;i<this->capacity;i++){
        if(this->spots[i]!=nullptr){
            if(this->spots[i]->isOccupied()){
                cout<<"Spot "<<spots[i]->getSpotNumber()<<" is already occupied."<<endl;
                return false;
            }
        }
    }
    // if parking spot is found
    for(int i=0;i<this->capacity;i++){
        if(this->spots[i]!=nullptr){
            if(this->spots[i]->getSpotNumber()==spotNumber){//found
                this->spots[i]->parkVehicle(vehicle);
                return true;
            }
        }
    }
    cout<<"Spot "<<spotNumber<<" not found in "<<this->name<<endl;
    return false;
}

bool ParkingLot::removeVehicle(const string& spotNumber) {
    for (int i = 0; i < num_of_spots; i++) {
        if (spots[i] != nullptr && spots[i]->getSpotNumber() == spotNumber) {
            if (!spots[i]->isOccupied()) {
                cout << "Spot " << spotNumber << " is already empty." << endl;
                return false;
            }
            spots[i]->removeVehicle();
            return true;
        }
    }
    cout << "Spot " << spotNumber << " not found in " << name << endl;
    return false;
}

string ParkingLot::getName() const {
    return name;
}

void ParkingLot::setName(const string& lotName) {
    name = lotName;
}

void ParkingLot::display() const {
    cout << "========================================" << endl; 
    cout << "Parking Lot " << name << endl;
    for (int i = 0; i < num_of_spots; i++) {
        if (spots[i] != nullptr) {
            cout << i << ". " << spots[i]->getSpotNumber();
            if (spots[i]->isOccupied()) {
                cout << " - " << spots[i]->getVehicle()->getLicensePlate();
            } else {
                cout << " - Empty";
            }
            cout << endl;
        }
    }
    cout << "========================================" << endl;
}
