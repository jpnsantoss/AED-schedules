//
// Created by jpsantos on 25-10-2023.
//

#ifndef AED2324_PRJ1_G56_REQUEST_H
#define AED2324_PRJ1_G56_REQUEST_H

#include <iostream>
#include <map>
#include <vector>
#include "UcClass.h"
#include "Student.h"

using namespace std;

enum requestType{
    Add,
    Remove,
    Switch
};

// add/remove/switch uc/class
class Request {
private:
    requestType type;
    Student* student;
    UcClass* initialUcClass;
    UcClass* finalUcClass;
public:
    // add uc/class
    // remove uc/class
    // switch class in some uc

    //swap a student from a class to another
    Request(requestType type, Student* student, UcClass* initialUcClass, UcClass* finalUcClass);

    //add/remove a class to a student
    Request(requestType type, Student* student, UcClass* ucClass);

    // Getter for requestType
    requestType getType() const;

    // Getter for Student pointer
    Student* getStudent() const;

    // Getter for initialUcClass pointer
    UcClass* getInitialUcClass() const;

    // Getter for finalUcClass pointer
    UcClass* getFinalUcClass() const;

    bool ucAlreadyExits();

    bool checkConflict();

    bool checkBalance(const vector<UcClass> &ucClasses);

    string getTypeToString();

    static requestType stringToRequestType(const std::string& typeStr);

    bool process(const vector<UcClass>& ucClasses);
};


#endif //AED2324_PRJ1_G56_REQUEST_H
