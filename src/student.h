//
// Created by jpsantos on 09-10-2023.
//
#include <utility>

#include "stdafx.h"
#include "lesson.h"
#include "class.h"

#ifndef AED2324_PRJ1_G56_STUDENT_H
#define AED2324_PRJ1_G56_STUDENT_H


class Student {
private:
    string code;
    string name;
    list<Lesson> lessons;
    list<Class> classes;

public:
    // Constructor
    Student(string  studentCode, string  studentName)
            : code(std::move(studentCode)), name(std::move(studentName)) {
        // Initialize other members as needed.
    }

    // Methods to add lessons to the schedule and classes to the list.
    void addLessonToSchedule(const Lesson& lesson) {
        schedule.push_back(lesson);
    }

    void addClass(const Class& classObj) {
        classes.push_back(classObj);
    }

    // Additional methods as needed for managing the student's data.
};


#endif //AED2324_PRJ1_G56_STUDENT_H
