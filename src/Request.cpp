//
// Created by jpsantos on 25-10-2023.
//

#include "Request.h"
//Switch class
Request::Request(requestType type, Student *student, UcClass *initialUcClass, UcClass *finalUcClass) {
    this->type = type;
    this->student = student;
    this->initialUcClass = initialUcClass;
    this->finalUcClass = finalUcClass;

}
//Add/remove class
Request::Request(requestType type, Student *student, UcClass *ucClass) {
    this->type = type;
    this->student = student;
    if(type == requestType::Add) {
        finalUcClass = ucClass;
    } else {
        initialUcClass = ucClass;
    }
}
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


    to do:
        check balance
        create student.hasUcClass(initialClass);

*/
bool Request::process(vector<UcClass>& ucClasses) {
    switch(this->type) {
        case requestType::Remove:
            this->student->removeUcClass(this->initialUcClass);
            initialUcClass->setStudentsNumber(initialUcClass->getStudentsNumber() - 1);
            return true;

        case requestType::Add:
            if(ucAlreadyExits()) {
                cout << "Student is already enrolled in this uc, try to switch instead." << endl;
                return false;
            }

            if(student->getUcClasses().size() >= 6) {
                cout << "Student is already enrolled in 6 ucs." << endl;
                return false;
            }

            if(finalUcClass->getStudentsNumber() >= UcClass::capacity) {
                cout << "This class is already full." << endl;
                return false;
            }

            if(checkConflict()) {
                cout << "There is a conflict between the Student's classes and the new class." << endl;
                return false;
            }

            if(!checkBalance(ucClasses)) {
                cout << "The number of students in each class must be balanced." << endl;
                return false;
            }

            this->student->addUcClass(*finalUcClass);

            this->finalUcClass->setStudentsNumber(finalUcClass->getStudentsNumber() + 1);

            return true;

        case requestType::Switch:
            if(initialUcClass->getUcClassCodes().first != finalUcClass->getUcClassCodes().first) {
                cout << "You have to switch classes from the same uc." << endl;
                return false;
            }

            if(finalUcClass->getStudentsNumber() >= UcClass::capacity) {
                cout << "This class is already full." << endl;
                return false;
            }
            this->student->removeUcClass(initialUcClass);
            initialUcClass->setStudentsNumber(initialUcClass->getStudentsNumber() - 1);
            if(checkConflict()) {
                cout << "There is a conflict between the Student's classes and the new class." << endl;
                this->student->addUcClass(*initialUcClass);
                initialUcClass->setStudentsNumber(initialUcClass->getStudentsNumber() + 1);
                return false;
            }
            if(!checkBalance(ucClasses)) {
                cout << "The number of students in each class must be balanced." << endl;
                initialUcClass->setStudentsNumber(initialUcClass->getStudentsNumber() + 1);
                this->student->addUcClass(*initialUcClass);
                return false;
            }
            this->student->addUcClass(*finalUcClass);
            this->finalUcClass->setStudentsNumber(finalUcClass->getStudentsNumber() + 1);
            return true;
        default:
            return false;
    }
}

bool Request::checkBalance(const vector<UcClass>& ucClasses) {
        int min = ucClasses[0].getStudentsNumber();
        for (const UcClass& ucClass: ucClasses) {

            if(ucClass.getUcClassCodes().first == finalUcClass->getUcClassCodes().first) {
                if(ucClass.getStudentsNumber() < min) min = ucClass.getStudentsNumber();
            }
        }
        if(finalUcClass->getStudentsNumber() - min > 3) return false;
    return true;
}

bool Request::checkConflict() {
    for(const Lesson& studentLesson: this->student->getLessons()) {
        for(const Lesson& ucClassLesson: this->finalUcClass->getLessons()) {
            if(!studentLesson.compatible(ucClassLesson)) return true;
            break;
        }
    }
    return false;
}

bool Request::ucAlreadyExits() {
    for(const UcClass& ucClass: student->getUcClasses()) {
        if(ucClass.getUcClassCodes().first == finalUcClass->getUcClassCodes().first) {
            return true;
        }
    }
    return false;
}

