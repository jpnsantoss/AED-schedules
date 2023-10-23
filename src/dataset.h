//
// Created by jpsantos on 18-10-2023.
//

#ifndef AED2324_PRJ1_G56_DATASET_H
#define AED2324_PRJ1_G56_DATASET_H

#include "stdafx.h"
#include "csvReader.h"
#include "class.h"
#include "student.h"
#include "uc.h"

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
    void createStudents(const vector<file_students_classes> &fileStudentsClasses);
    void createClasses(const vector<file_classes_per_uc>& fileClassesPerUc);

};



#endif //AED2324_PRJ1_G56_DATASET_H
