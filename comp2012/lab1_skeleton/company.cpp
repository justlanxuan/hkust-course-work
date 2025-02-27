#include "company.h"
#include <iostream>
using namespace std;
//int currSize; // how many employees are currently in the company
// Employee *employees[COMPANY_MAX_SIZE];
void Company::init() 
{
    this->currSize = 0;
    for(int i = 0; i < COMPANY_MAX_SIZE;i++)
    {
        employees[i] = nullptr;
    }
}

void Company::addEmployee(Employee* emp)
{
    // Check if the employee already exists by name
    if (hasEmployee(emp->getName())) {
        cout << "Employee " << emp->getName() << " already exists in the company" << endl;
        return;
    }

    // Check if company is full
    if (currSize == COMPANY_MAX_SIZE) {
        cout << "Company is full" << endl;
        return;
    }

    // Otherwise, add the employee
    employees[currSize] = emp;
    currSize++;
    cout << "Employee " << emp->getName() << " is hired" << endl;
}

int Company::findEmployee(const string& empName) const
{
    for(int i = 0;i < this->currSize;i++)
    {
        if(employees[i]->getName() == empName)
        {
            return i;
        }
        // nullptr problem?
    }
    return -1;
}

bool Company::hasEmployee(const string& empName) const
{
    return findEmployee(empName) != -1;
}

void Company::fireEmployee(const string& empName)
{
    if(hasEmployee(empName)){
        int idx = findEmployee(empName);
        for(int i = idx;i<this->currSize;i++)
        {
            employees[i]=employees[i+1];
        }
        currSize--;
        cout<<"Employee "<< empName <<" is fired"<<endl;
    }
    else{
        cout<<"Employee "<< empName <<" is not found in the company"<<endl;
    }
}

void Company::promoteEmployee(const string& empName, const string& newTitle)
{
    if(hasEmployee(empName)){
        employees[findEmployee(empName)]->setTitle(newTitle);
        cout<<"Employee "<< empName <<" is promoted to "<< newTitle <<endl;
    }
    else{
        cout<<"Employee "<< empName <<" is not found in the company"<<endl;
    }
}

void Company::adjustSalary(const string& empName, double amount)
{
    // Find the employee to adjust the salary.
    int index = findEmployee(empName);
    if (index == -1) {
        cout << "Employee " << empName << " is not found in the company" << endl;
        return;
    }

    // Adjust the salary.
    double updatedSalary = employees[index]->getSalary() + amount;
    employees[index]->setSalary(updatedSalary);
    cout << "Employee " << empName << "'s salary is changed by " << amount << endl;
}

void Company::print() const
{
    cout<<"Company with "<< this->currSize<<" employees:"<<endl;
    for(int i = 0;i<this->currSize;i++)
    {
        cout<<"    ";
        employees[i]->Employee::print();
    }
}
