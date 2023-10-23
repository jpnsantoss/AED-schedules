//
// Created by jpsantos on 09-10-2023.
//
#ifndef AED2324_PRJ1_G56_UC_H
#define AED2324_PRJ1_G56_UC_H

#include "stdafx.h"
#include "lesson.h"
#include "class.h"

class Uc {
private:
    string ucCode;
    list<Lesson> lessons;

public:

    // Constructor
    explicit Uc(string  ucCode) : ucCode(std::move(ucCode)) {}

    // Getter for code
    [[nodiscard]] const string& getUcCode() const {
        return ucCode;
    }

    // Getter for classes
    [[nodiscard]] const list<Lesson>& getLessons() const {
        return lessons;
    }

    // Method to add a class to the list
    void addLesson(const Lesson& lesson) {
        lessons.push_back(lesson);
    }
};

#endif //AED2324_PRJ1_G56_UC_H
