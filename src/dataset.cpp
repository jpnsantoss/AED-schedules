//
// Created by jpsantos on 18-10-2023.
//

#include <unordered_set>
#include <unordered_map>
#include "dataset.h"
#include "csvReader.h"
Dataset::Dataset() {
    CsvReader read;
    vector<file_classes_per_uc> fileClassesPerUc = read.readClassesPerUc();
    vector<file_classes> fileClasses = read.readClasses();
    vector<file_students_classes> fileStudentsClasses = read.readStudentsClasses();
    createLessons(fileClasses);
    createUcs(fileClassesPerUc);
    createStudents(fileStudentsClasses);
    createClasses(fileClassesPerUc);
}

void Dataset::createLessons(const vector<file_classes>& fileClasses) {
    lessons.clear();

    for (const file_classes& data : fileClasses) {
        double startHour = stod(data.startHour);
        double duration = stod(data.duration);
        double endHour = startHour + duration;

        lessons.emplace_back(data.ucCode, data.classCode, startHour, endHour, data.type, data.weekday);
    }
}


void Dataset::createUcs(const vector<file_classes_per_uc>& fileClassesPerUc) {
    ucs.clear();
    unordered_set<string> ucCodes;

    for (const file_classes_per_uc& data : fileClassesPerUc) {
        ucCodes.insert(data.ucCode);
    }

    for (const string& code : ucCodes) {
        ucs.emplace_back(code);
    }

    for (Uc& uc : ucs) {
        for (const Lesson& lesson : lessons) {
            if (uc.getUcCode() == lesson.getUcCode()) {
                uc.addLesson(lesson);
            }
        }
    }
}




void Dataset::createStudents(const vector<file_students_classes>& fileStudentsClasses) {
    students.clear();
    unordered_map<string, string> studentsData;

    for (const file_students_classes& data : fileStudentsClasses) {
        studentsData.insert({data.studentCode, data.studentName});
    }

    for (const pair<const string, string>& studentData : studentsData) {
        students.emplace_back(studentData.first, studentData.second );  // Initialize with an empty student name
    }

    for (Student& student : students) {
        for (const file_students_classes& data : fileStudentsClasses) {
            if (data.studentCode == student.getStudentCode()) {
                student.addClassPerUc({data.ucCode, data.classCode});
            }
        }
    }
}

void Dataset::createClasses(const vector<file_classes_per_uc>& fileClassesPerUc) {
    classes.clear();
    unordered_set<string> classCodes;

    for (const file_classes_per_uc& data : fileClassesPerUc) {
        classCodes.insert(data.classCode);
    }

    for (const string& classCode : classCodes) {
        classes.emplace_back(classCode);  // Initialize with an empty student name
    }

    for (Class& existingClass : classes) {
        for(const Lesson& lesson: lessons) {
            if(lesson.getClassCode() == existingClass.getClassCode()) {
                existingClass.addLesson(lesson);
            }
        }

        for(const Student& student: students) {
            for (const pair<string, string>& ucClass: student.getClassesPerUcs()) {
                if(ucClass.second == existingClass.getClassCode()) {
                    existingClass.addStudent(student.getStudentCode());
                }
            }
        }
    }
}





