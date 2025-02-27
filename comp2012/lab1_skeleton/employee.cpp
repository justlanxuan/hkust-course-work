#include "employee.h"
#include <iostream> // for std::cout, std::endl, etc.

using namespace std;

// Getter methods
string Employee::getName() const
{
    // TODO: Return the name
    return this->name; 
}

double Employee::getSalary() const
{
    // TODO: Return the salary
    return this->salary;
}

char Employee::getGender() const
{
    // TODO: Return the gender
    return this->gender; 
}

string Employee::getTitle() const
{
    // TODO: Return the title
    return this->title;
}

// Setter methods
void Employee::setName(const string &newName)
{
    // TODO: Set the name
    this->name = newName;
}

void Employee::setSalary(double newSalary)
{
    // TODO: Set the salary
    this->salary = newSalary;
}

void Employee::setGender(char newGender)
{
    // TODO: Set the gender
    this->gender = newGender;
}

void Employee::setTitle(const string &newTitle)
{
    // TODO: Set the title
    this->title = newTitle;
}

// Print method
void Employee::print() const
{
    // TODO: Print in the format:
    cout<<"[Name: "<< this->name << ", Title: "<< this->title << ", Gender: "<<this->gender<<", Salary: "<<this->salary<< "]"<<endl;
    // [Name: <name>, Title: <title>, Gender: <gender>, Salary: <salary>]
}