//
// Created by jpsantos on 09-10-2023.
//
#include "stdafx.h"
#include "course.h"

#ifndef AED2324_PRJ1_G56_STUDENT_H
#define AED2324_PRJ1_G56_STUDENT_H


class Student {

private:
    string code;
    string name;
    list<Course> schedule;
public:
    Student(string code, string name, list<Course> schedule) {
        this->code = code;
        this->name = name;
        this->schedule = schedule;
    }
};


#endif //AED2324_PRJ1_G56_STUDENT_H
