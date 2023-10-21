//
// Created by jpsantos on 18-10-2023.
//

#include "dataset.h"
#include "csvReader.h"
Dataset::Dataset() {
    CsvReader read;
    vector<file_classes_per_uc> fileClassesPerUc = read.readClassesPerUc();
    vector<file_classes> fileClasses = read.readClasses();
    //vector<file_students_classes> fileStudentsClasses = read.readStudentsClasses();
    createUcs(fileClassesPerUc);
    createLessons(fileClasses);
    createClasses(fileClassesPerUc);
}

void Dataset::createUcs(const vector<file_classes_per_uc>& fileClassesPerUc) {
    /*
    ucs.clear();
    vector<string> ucCodes;
    for(const file_classes_per_uc& data: fileClassesPerUc) {
        bool alreadyAdded = false;
        for(const string& code: ucCodes) {
            if (data.ucCode == code) alreadyAdded = true;
        }
        if(!alreadyAdded) ucCodes.push_back(data.ucCode);
    }
    for(const string& code: ucCodes) {
        Uc newUc(code);
        ucs.push_back(newUc);
    }
     */
}

void Dataset::createLessons(const vector<file_classes>& fileClasses) {
    /*
    lessons.clear();

    for (const file_classes& data : fileClasses) {
        double start = stod(data.startHour);
        double duration = stod(data.duration);
        double endHour = start + duration;

        Lesson newLesson(data.ucCode, data.classCode, start, endHour, data.type, data.weekday);
        lessons.push_back(newLesson);
    }
     */
}

void Dataset::createClasses(const vector<file_classes_per_uc>& fileClassesPerUc) {
    /*
    classes.clear();
    vector<string> classCodes;
    for(const file_classes_per_uc& data: fileClassesPerUc) {
        bool alreadyAdded = false;
        for(const string& code: classCodes) {
            if (data.classCode == code) alreadyAdded = true;
        }
        if(!alreadyAdded) classCodes.push_back(data.classCode);
    }
    for(const string& code: classCodes) {
        Class newClass(code);
        for(const Lesson& lesson: getLessons()) {
            if(lesson.getClassCode() == code) {
                newClass.addLesson(lesson);
            }
        }
        classes.push_back(newClass);
    }
     */
}



