//
// Created by Maureen Ah-shu on 15/10/2023.
//

#ifndef AED2324_PRJ1_G56_FILE_H
#define AED2324_PRJ1_G56_FILE_H

#include "lesson.h"
#include "class.h"
#include "student.h"
#include "stdafx.h"

using namespace std;

class File {
public:
    void readData();
protected:
    vector<Lesson> readLessons();
    vector<Student> readStudents();
    vector<Class> readClasses();
};


#endif //AED2324_PRJ1_G56_FILE_H
