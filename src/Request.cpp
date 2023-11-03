//
// Created by jpsantos on 25-10-2023.
//

#include "Request.h"

#include <utility>
Request::Request(requestType type, Student student, UcClass& initialUcClass, UcClass& finalUcClass)
        : type(type), student(std::move(student)), initialUcClass(initialUcClass), finalUcClass(finalUcClass) {
    // Constructor implementation
}

Request::Request(requestType type, Student student, UcClass& ucClass)
        : type(type), student(std::move(student)), initialUcClass(ucClass), finalUcClass(ucClass) {
    // Constructor implementation
}


bool Request::checkBalance(const vector<UcClass>& ucClasses) {
        int min = ucClasses[0].getStudentsNumber();
        for (const UcClass& ucClass: ucClasses) {

            if(ucClass.getUcClassCodes().first == finalUcClass.getUcClassCodes().first) {
                if(ucClass.getStudentsNumber() < min) min = ucClass.getStudentsNumber();
            }
        }
        if(finalUcClass.getStudentsNumber() - min > 3) return false;
    return true;
}

bool Request::checkConflict() {
    for(const Lesson& studentLesson: this->student.getLessons()) {
        for(const Lesson& ucClassLesson: this->finalUcClass.getLessons()) {
            if(!studentLesson.compatible(ucClassLesson)) return true;
            break;
        }
    }
    return false;
}

bool Request::ucAlreadyExits() {
    for(const UcClass& ucClass: student.getUcClasses()) {
        if(ucClass.getUcClassCodes().first == finalUcClass.getUcClassCodes().first) {
            return true;
        }
    }
    return false;
}

requestType Request::getType() const {
    return type;
}

Student Request::getStudent() const  {
    return student;
}

UcClass Request::getInitialUcClass() const {
        return initialUcClass;
}

UcClass Request::getFinalUcClass() const {
    return finalUcClass;
}

string Request::getTypeToString() {
    switch (type) {
        case requestType::Add:
            return "Add";
        case requestType::Remove:
            return "Remove";
        case requestType::Switch:
            return "Switch";
        default:
            return "Unknown";
    }
}

requestType Request::stringToRequestType(const string &typeStr) {
    if (typeStr == "Add") {
        return requestType::Add;
    } else if (typeStr == "Remove") {
        return requestType::Remove;
    } else {
        return requestType::Switch;
    }
}

bool Request::process(set<Student>* students, const vector<UcClass> &ucClasses)  {

    auto newStudentItr = (*students).find(this->student);// copy of the student
    if(newStudentItr==students->end()) {
        // Student doesn't exist anymore
        cout<<"Failed! Student does not exist anymore!";
        return {};
    }
    Student newStudent = *newStudentItr;// auxiliary student
    switch(this->type) {
        case requestType::Remove:
            newStudent.removeUcClass(this->initialUcClass);
            initialUcClass.setStudentsNumber(initialUcClass.getStudentsNumber() - 1);
            break;

        case requestType::Add:
            if(ucAlreadyExits()) {
                cout << "Student is already enrolled in this uc, try to switch instead." << endl;
                return false;
            }

            if(newStudent.getUcClasses().size() >= 6) {
                cout << "Student is already enrolled in 6 ucs." << endl;
                return false;
            }

            if(finalUcClass.getStudentsNumber() >= UcClass::capacity) {
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

            newStudent.addUcClass(finalUcClass);

            this->finalUcClass.setStudentsNumber(finalUcClass.getStudentsNumber() + 1);

            break;

        case requestType::Switch:
            if(initialUcClass.getUcClassCodes().first != finalUcClass.getUcClassCodes().first) {
                cout << "You have to switch classes from the same uc." << endl;
                return false;
            }

            if(finalUcClass.getStudentsNumber() >= UcClass::capacity) {
                cout << "This class is already full." << endl;
                return false;
            }
            newStudent.removeUcClass(initialUcClass);
            initialUcClass.setStudentsNumber(initialUcClass.getStudentsNumber() - 1);
            if(checkConflict()) {
                cout << "There is a conflict between the Student's classes and the new class." << endl;
                newStudent.addUcClass(initialUcClass);
                initialUcClass.setStudentsNumber(initialUcClass.getStudentsNumber() + 1);
                return false;
            }
            if(!checkBalance(ucClasses)) {
                cout << "The number of students in each class must be balanced." << endl;
                initialUcClass.setStudentsNumber(initialUcClass.getStudentsNumber() + 1);
                newStudent.addUcClass(initialUcClass);
                return false;
            }
            newStudent.addUcClass(finalUcClass);
            this->finalUcClass.setStudentsNumber(finalUcClass.getStudentsNumber() + 1);
            break;
    }
    auto itr = students->find(student);
    students->erase(itr);
    students->insert(newStudent);
    this->student = newStudent;
    return true;
}

