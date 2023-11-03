
#ifndef AED2324_PRJ1_G56_REQUEST_H
#define AED2324_PRJ1_G56_REQUEST_H

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include "UcClass.h"
#include "Student.h"

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
    bool checkBalance(const std::list<UcClass> &ucClasses);
    std::string getTypeToString();
    static requestType stringToRequestType(const std::string& typeStr);
    bool process(std::set<Student>* students, const std::list<UcClass>& ucClasses);
    Request& operator=(const Request& other) {
        if (this != &other) {
            type = other.type;
            student = other.student;

            // Crie cópias dos objetos UcClass
            initialUcClass = other.initialUcClass;
            finalUcClass = other.finalUcClass;
        }
        return *this;
    }
};


#endif //AED2324_PRJ1_G56_REQUEST_H
