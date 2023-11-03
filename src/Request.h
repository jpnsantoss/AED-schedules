//
// Created by jpsantos on 25-10-2023.
//

#ifndef AED2324_PRJ1_G56_REQUEST_H
#define AED2324_PRJ1_G56_REQUEST_H

#include <iostream>
#include <map>
#include <set>
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
    Student student;
    UcClass& initialUcClass;
    UcClass& finalUcClass;
public:
    Request(requestType type, Student student, UcClass& initialUcClass, UcClass& finalUcClass);
    Request(requestType type, Student student, UcClass& ucClass);
    requestType getType() const;
    Student getStudent() const;
    UcClass getInitialUcClass() const;
    UcClass getFinalUcClass() const;
    bool ucAlreadyExits();
    bool checkConflict();
    bool checkBalance(const list<UcClass> &ucClasses);
    string getTypeToString();
    static requestType stringToRequestType(const std::string& typeStr);
    bool process(set<Student>* students, const list<UcClass>& ucClasses);
};


#endif //AED2324_PRJ1_G56_REQUEST_H
