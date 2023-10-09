//
// Created by jpsantos on 09-10-2023.
//
#include <string>
#include <list>
#include "slotH.h"
#include <iostream>

#ifndef AED2324_PRJ1_G56_STUDENT_H
#define AED2324_PRJ1_G56_STUDENT_H


class Student {

private:
    std::string code;
    std::string name;
    std::list<SlotH> schedule;
public:
    Student(std::string code, std::string name, std::list<SlotH> schedule) {
        this->code = code;
        this->name = name;
        this->schedule = schedule;
    }
};


#endif //AED2324_PRJ1_G56_STUDENT_H
