//
// Created by jpsantos on 09-10-2023.
//

#ifndef AED2324_PRJ1_G56_STUDENT_H
#define AED2324_PRJ1_G56_STUDENT_H

#include "stdafx.h"
#include "lesson.h"
#include "class.h"

class Student {
private:
    string studentCode;
    string name;

    //pair<uc, class>
    vector<pair<string, string>> classesPerUcs;

public:

    // Constructor
    Student(string studentCode, string studentName)
            : studentCode(std::move(studentCode)), name(std::move(studentName)) {
        // Initialize other members as needed.
    }

    // Methods to add lessons to the schedule and classes to the list.
    void addClassPerUc(const pair<string, string>& classPerUc) {
        classesPerUcs.push_back(classPerUc);
    }

    // Getter for code
    [[nodiscard]] string getStudentCode() const {
        return studentCode;
    }

    // Getter for name
    [[nodiscard]] string getName() const {
        return name;
    }

    [[nodiscard]] const vector<pair<string, string>>& getClassesPerUcs() const {
        return classesPerUcs;
    }
};



#endif //AED2324_PRJ1_G56_STUDENT_H
