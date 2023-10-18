//
// Created by jpsantos on 18-10-2023.
//
#include "stdafx.h"
#include "student.h"
#include "lesson.h"
#include "class.h"
#include "uc.h"
#include "csvReader.h"

#ifndef AED2324_PRJ1_G56_DATASET_H
#define AED2324_PRJ1_G56_DATASET_H


class Dataset {
private:
    vector<Class> classes;
    vector<Student> students;
    vector<Lesson> lessons;
    vector<Uc> ucs;

public:
    Dataset();

    // Getters for the private member variables
    [[nodiscard]] const vector<Class>& getClasses() const {
        return classes;
    }

    [[nodiscard]] const vector<Student>& getStudents() const {
        return students;
    }

    [[nodiscard]] const vector<Lesson>& getLessons() const {
        return lessons;
    }

    [[nodiscard]] const vector<Uc>& getUcs() const {
        return ucs;
    }

protected:
    void createUcs(const vector<file_classes_per_uc>& fileClassesPerUc);
    void createLessons(const vector<file_classes>& fileClasses);
    void createClasses(const vector<file_classes_per_uc>& fileClassesPerUc);
    void createStudents();

};



#endif //AED2324_PRJ1_G56_DATASET_H
