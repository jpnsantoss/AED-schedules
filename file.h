//
// Created by Maureen Ah-shu on 15/10/2023.
//

#ifndef AED2324_PRJ1_G56_FILE_H
#define AED2324_PRJ1_G56_FILE_H

#include "iostream"
#include "course.h"
#include "classUc.h"
#include "student.h"
#include <fstream>
#include <string>
#include "vector"

using namespace std;

class file {
public:
    void readData();
protected:
    vector<Course> readClasses();
    vector<Student> readStudents();
    vector<ClassUC> readClassesUC();
};


#endif //AED2324_PRJ1_G56_FILE_H
