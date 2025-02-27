#include "class.h"
#include <iostream>
#include <cstring>

using namespace std;

// Student constructor
Student::Student(const char* name): classCount{0}, classCapacity{2}
{
    this->name = new char[strlen(name)+1];
    strcpy(this->name,name);
    this->classes = new Class*[classCapacity];
    cout<<"Student: "<<this->name<<" initialized!"<<endl;
}

// Student destructor
Student::~Student() {

    for(int i = 0;i<classCapacity;i++)
    {
        if(classes[i]!=nullptr){
        classes[i]->dropStudent(this);
        }
    }
    delete [] this->classes;
    cout<<"Student: "<<this->name<<" destroyed!"<<endl;
    delete [] this->name;
}

// Class constructor
Class::Class(const char* name, int capacity):studentCount{0},capacity{capacity} {
    this->name = new char[strlen(name)+1];
    strcpy(this->name,name);
    this->students = new Student*[this->capacity];
    cout<<"Class: "<<this->name<<" created with capacity "<<this->capacity<<"."<<endl;
}

// Class destructor
Class::~Class() {
    cout<<"Class: "<<this->name<<" destroyed."<<endl;
    delete [] this->name;
    delete [] this->students;
}

// Enroll a student in the class
bool Class::enrollStudent(Student* student) {
    // check whether the class is full
    if(this->studentCount>=this->capacity){
        cout<<"Class "<<this->name<<" is full. Cannot enroll student!"<<endl;
        return false;
    }
    else{
        // add the student to the students array
        students[studentCount] = student;
        studentCount+=1;
        student->enrollInClass(this);
        
        cout<<"Student "<<student->getName()<<" enrolled in class "<<this->name<<"."<<endl;
        return true;
    }
}

// Drop a student from the class
bool Class::dropStudent(Student* student) {
    // student name not found
    bool student_found = false;
    int student_idx = 0;
    for(int i=0;i<this->studentCount;i++){
        // can I just compare the address instead of compare names
        if(strcmp(student->getName(),this->students[i]->getName())==0){
            student_found = true;
            student_idx = i;
            break;
        }
    }
    if(!student_found){
        cout<<"Student "<<student->getName()<<" is not in class "<<this->getName()<<"."<<endl;
        return false;
    }
    else if(student_found){
        cout<<"Student "<<students[student_idx]->getName()<<" dropped from class "<<this->getName()<<"."<<endl;
        this->students[student_idx]->dropClass(this);
        for(int j=student_idx;j<this->studentCount;j++){
            this->students[j]=this->students[j+1];
        }
        studentCount-=1;
        this->students[studentCount]=nullptr;
        

        return true;
    }
}