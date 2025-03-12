#include "Zoo.h"
#include "Animal.h"
#include "Exhibit.h"
#include "IndoorExhibit.h"
#include "OutdoorExhibit.h"
#include <iostream>
using namespace std;

// TODO 4.1: complete the constructor of Zoo
// Initialize the zoo with the specified maximum number of animals
Zoo::Zoo(int max_animals): max_animals(max_animals), num_animals(0){
   this->animals = new Animal*[this->max_animals]{nullptr};
}

// TODO 4.2: complete the destructor of Zoo
// Clean up any dynamically allocated memory if necessary
Zoo::~Zoo() {
   for (int i=0;i<this->max_animals;i++){
        if(animals[i]!=nullptr){
            delete animals[i];
        }
        else{
            break;
        }
   }
   delete [] animals;
}
// TODO 4.3: complete Zoo::add_to_indoor() and Zoo::add_to_outdoor()
// Add an animal to the zoo if there is space available

bool Zoo::add_animal_to_indoor(Animal* animal, IndoorExhibit* exhibit) {
    // if no space available
    if(this->num_animals >= this->max_animals){
        cout << "Zoo is full. Cannot add more animals." << endl;
        return false;
    }
    else{// add animal
        animal->set_exhibit(exhibit);
        this->animals[num_animals] = new Animal(animal->get_name(),animal->get_age());
        this->num_animals += 1;
        cout << "Added animal " << animal->get_name() 
         << " to indoor exhibit " << animal->get_exhibit()->get_name()
         << " (" << exhibit->get_climate_type() << " environment)" << endl;
        return true;
    }    
}

bool Zoo::add_animal_to_outdoor(Animal* animal, OutdoorExhibit* exhibit) {
    // if no space available
    if(this->num_animals >= this->max_animals){
        cout << "Zoo is full. Cannot add more animals." << endl;
        return false;
    }
    else{// add animal
        animal->set_exhibit(exhibit);
        this->animals[num_animals] = new Animal(animal->get_name(),animal->get_age());
        this->num_animals += 1;
        cout << "Added animal " << animal->get_name() 
         << " to outdoor exhibit " << animal->get_exhibit()->get_name()
         << " (area: " << exhibit->get_area() << " square meters)" << endl;  
        return true;
    }  
}

// TODO 4.4: complete Zoo::remove_animal()
// Remove an animal from the zoo by name
bool Zoo::remove_animal(const string& name) {
    for(int i=0;i<this->max_animals;i++){
        if(this->animals[i] == nullptr){
            break;
        }
        else{
            if(name == this->animals[i]->get_name()){
                // animal found
                delete this->animals[i];
                for(int j=i;j<this->max_animals;j++){
                    this->animals[i] = this->animals[i+1];
                }
                this->num_animals -= 1;
                cout << "Removed animal: " << name << endl;
                return true;
            }
        }
    }
    // animal not found
    cout << "Animal " << name << " not found in the zoo." << endl;
    return false;
   
    
    

}

void Zoo::print_all_animals() const {
    if (num_animals == 0) {
        cout << "The zoo currently has no animals." << endl;
        return;
    }
    
    cout << "Current animals in the zoo:" << endl;
    for (int i = 0; i < num_animals; i++) {
        cout << animals[i]->get_name() << ", ";  
    }
    cout << endl;
}

