//
// Created by jpsantos on 09-10-2023.
//

#ifndef AED2324_PRJ1_G56_CLASS_H
#define AED2324_PRJ1_G56_CLASS_H

#include "stdafx.h"
#include "lesson.h"
#include "student.h"
class Class {
private:
    string classCode;
    vector<string> students;
    vector<string> ucs;
    vector<Lesson> lessons;

public:
    /*
    explicit Class(string  code) : classCode(std::move(code)) {}

    [[nodiscard]] const string& getClassCode() const {
        return classCode;
    }

    void addLesson(const Lesson& lesson) {
        lessons.emplace_back(lesson);
    }
     */
};


#endif //AED2324_PRJ1_G56_CLASS_H
