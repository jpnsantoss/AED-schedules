//
// Created by jpsantos on 09-10-2023.
//

#ifndef AED2324_PRJ1_G56_CLASS_H
#define AED2324_PRJ1_G56_CLASS_H

#include <utility>

#include "stdafx.h"
#include "lesson.h"
#include "student.h"
class Class {
private:
    string classCode;
    vector<string> studentCodes;
    vector<Lesson> lessons;

public:
    // Constructor
    explicit Class(string  code) : classCode(std::move(code)) {}

    // Getter for class code
    [[nodiscard]] const string& getClassCode() const {
        return classCode;
    }

    // Add a student to the class
    void addStudent(const string& student) {
        studentCodes.push_back(student);
    }

    // Add a lesson to the class
    void addLesson(const Lesson& lesson) {
        lessons.push_back(lesson);
    }

    // Get the list of students in the class
    [[nodiscard]] const vector<string>& getStudents() const {
        return studentCodes;
    }

    // Get the list of lessons associated with the class
    [[nodiscard]] const vector<Lesson>& getLessons() const {
        return lessons;
    }
    void addLessons(const vector<Lesson>& newLessons) {
        lessons.insert(lessons.end(), newLessons.begin(), newLessons.end());
    }
};


#endif //AED2324_PRJ1_G56_CLASS_H
