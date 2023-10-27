//
// Created by jpsantos on 25-10-2023.
//

#ifndef AED2324_PRJ1_G56_REQUEST_H
#define AED2324_PRJ1_G56_REQUEST_H

#include <iostream>
#include <map>
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

/*
     check request type
     remove:
        checkBalance
     add:
        check if student already has that uc
        check if the student has less than 7 ucs
        check classes for that uc with slots available
        for each class:
            checkBalance
            checkConflict
    switch:
        check if olduc == newUc
        checkCapacity
        checkBalance
        checkConflict
*/

    bool process();

    bool checkBalance();

    bool ucAlreadyExits();

    bool checkConflict();
};


#endif //AED2324_PRJ1_G56_REQUEST_H
