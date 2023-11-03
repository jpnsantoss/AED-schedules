//
// Created by jpsantos on 25-10-2023.
//

#ifndef AED2324_PRJ1_G56_STUDENT_H
#define AED2324_PRJ1_G56_STUDENT_H

#include <string>
#include <list>
#include "UcClass.h"

using namespace std;

class Student {
private:
    string studentCode;
    string studentName;
    list<UcClass> ucClasses;

public:
    Student();
    Student(string studentCode, string studentName);

    // Setter and Getter methods
    void setStudentCode(const string& code);
    string getStudentCode() const;

    void setStudentName(const string& name);
    string getStudentName() const;

    void addUcClass(const UcClass& ucClass);

    const list<UcClass>& getUcClasses() const;

    // only to make insert work, dw about it.
    bool operator<(const Student &other) const;

    void reset();

    void removeUcClass(UcClass ucClass);

    list<Lesson> getLessons() const;

};


#endif //AED2324_PRJ1_G56_STUDENT_H
