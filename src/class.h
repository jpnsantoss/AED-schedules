//
// Created by jpsantos on 09-10-2023.
//
#include "stdafx.h"
#include "lesson.h"
#include "student.h"

#ifndef AED2324_PRJ1_G56_CLASS_H
#define AED2324_PRJ1_G56_CLASS_H


class Class {
private:
    string classCode;
    vector<Lesson> lessons;
    vector <Student> students;

public:
    explicit Class(string  code) : classCode(std::move(code)) {}

    [[nodiscard]] const string& getClassCode() const {
        return classCode;
    }

    void addLesson(const Lesson& lesson) {
        lessons.emplace_back(lesson);
    }

    void addStudent(const Student& student) {
        students.emplace_back(student);
    }
};


#endif //AED2324_PRJ1_G56_CLASS_H
