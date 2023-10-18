//
// Created by jpsantos on 18-10-2023.
//
#include "stdafx.h"
#include "student.h"
#include "lesson.h"
#include "class.h"
#include "uc.h"
#ifndef AED2324_PRJ1_G56_DATASET_H
#define AED2324_PRJ1_G56_DATASET_H


class Dataset {
private:
    vector<Class> classes;
    vector<Student> students;
    vector<Lesson> lessons;
    vector<Uc> ucs;
};


#endif //AED2324_PRJ1_G56_DATASET_H
