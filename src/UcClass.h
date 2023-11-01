//
// Created by jpsantos on 25-10-2023.
//

#ifndef AED2324_PRJ1_G56_UCCLASS_H
#define AED2324_PRJ1_G56_UCCLASS_H

#include <string>
#include <list>
#include "Lesson.h"

using namespace std;

class UcClass {
private:
    string ucCode;
    string classCode;
    list<Lesson> lessons;
    int studentsNumber;

public:
    static int capacity;

    UcClass(string ucCode, string classCode);
    pair<string, string> getUcClassCodes() const;
    void addLessons(const list<Lesson>& newLessons);
    void addLesson(const Lesson& newLesson);

    // Setter for studentsNumber
    void setStudentsNumber(int number);

    // Getter for studentsNumber
    int getStudentsNumber() const;

    // Getter for capacity
    static int getCapacity();

    // Getter for lessons
    const list<Lesson>& getLessons() const;

    bool operator==(const UcClass& other) const;

    bool operator<(const UcClass &other) const;
};



#endif //AED2324_PRJ1_G56_UCCLASS_H
