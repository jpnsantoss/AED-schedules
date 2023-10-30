//
// Created by jpsantos on 25-10-2023.
//

#include "Dataset.h"

Dataset::Dataset() {
    readUcClasses();
    readLessons();
    readStudents();
}

const std::set<Student>& Dataset::getStudents() const {
    return students;
}

const std::vector<UcClass>& Dataset::getUcClasses() const {
    return ucClasses;
}

const std::queue<Request>& Dataset::getRequests() const {
    return requests;
}

const std::queue<Request>& Dataset::getHistory() const {
    return history;
}

void Dataset::readUcClasses() {
    ifstream file("files/classes_per_uc.csv");
    if (!file.is_open()) {
        cout << "Error: File 'classes_per_uc.csv' not opened." << endl;
        return;
    }

    string row, ucCode, classCode;
    getline(file, row);

    while (getline(file, row)) {
        istringstream line(row);
        getline(line, ucCode, ',');
        getline(line, classCode, '\r');

        ucClasses.emplace_back(ucCode, classCode);
    }
}

void Dataset::readLessons() {
    ifstream file("files/classes.csv");
    if (!file.is_open()) {
        cout << "Error: File 'classes.csv' not opened." << endl;
        return;  // Exit the method if the file couldn't be opened.
    }

    string row, classCode, ucCode, weekday, startHour, duration, type;

    getline(file, row);  // Read and discard the header row.

    while (getline(file, row)) {
        istringstream line(row);
        getline(line, classCode, ',');
        getline(line, ucCode, ',');
        getline(line, weekday, ',');
        getline(line, startHour, ',');
        getline(line, duration, ',');
        getline(line, type, '\r');

        // Ensure the Lesson constructor parameters are in the correct order.
        Lesson newLesson(weekday, stof(startHour), stof(duration), type);

        for (UcClass& ucClass : ucClasses) {
            if (ucClass.getUcClassCodes() == make_pair(ucCode, classCode)) {
                ucClass.addLesson(newLesson);
            }
        }
    }
}

void Dataset::readStudents() {
    ifstream file("files/students_classes.csv");
    if (!file.is_open()) {
        cout << "Error: File 'students_classes.csv' not opened." << endl;
        return;  // Exit the method if the file couldn't be opened.
    }
    string row, studentCode, studentName, ucCode, classCode, prevStudentCode;
    int maxCapacity = 0;
    Student currentStudent;
    getline(file, row);

    while(getline(file, row)) {
        istringstream line(row);
        getline(line, studentCode, ',');
        getline(line, studentName, ',');
        getline(line, ucCode, ',');
        getline(line, classCode, '\r');

        if(studentCode != prevStudentCode) {
            if(!prevStudentCode.empty()) {
                students.insert(currentStudent);
            }
            currentStudent.reset();
            currentStudent.setStudentCode(studentCode);
            currentStudent.setStudentName(studentName);
        }

        for (UcClass& ucClass : ucClasses) {
            if (ucClass.getUcClassCodes() == make_pair(ucCode, classCode)) {
                ucClass.setStudentsNumber(ucClass.getStudentsNumber());
                if(ucClass.getStudentsNumber()>maxCapacity) maxCapacity=ucClass.getStudentsNumber();
                currentStudent.addUcClass(ucClass);
            }
        }
        prevStudentCode = studentCode;
    }
    students.insert(currentStudent);
    UcClass::capacity = maxCapacity;
}

void Dataset::handleRequests() {
    for(int i = 0; i < requests.size(); i++) {
        requests.front().process(ucClasses);
        requests.pop();
    }
}
