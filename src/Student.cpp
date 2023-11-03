//
// Created by jpsantos on 25-10-2023.
//

#include "Student.h"

#include <utility>

// Default constructor
Student::Student() {}

// Parameterized constructor
Student::Student(string  studentCode, string  studentName)
        : studentCode(std::move(studentCode)), studentName(std::move(studentName)) {
}

// Setter and Getter methods for studentCode
void Student::setStudentCode(const std::string& code) {
    studentCode = code;
}

std::string Student::getStudentCode() const {
    return studentCode;
}

// Setter and Getter methods for studentName
void Student::setStudentName(const std::string& name) {
    studentName = name;
}

std::string Student::getStudentName() const {
    return studentName;
}

// Setter and Getter methods for ucClasses
void Student::addUcClass(const UcClass& ucClass) {

    ucClasses.push_back(ucClass);
}

const std::list<UcClass>& Student::getUcClasses() const {
    return ucClasses;
}


//useless, only for the set type to work.
bool Student::operator<(const Student &other) const {
    return studentCode < other.studentCode;
}

void Student::reset() {
    // Reset all fields to their initial state
    studentCode = "";
    studentName = "";
    ucClasses.clear(); // Assuming you want to clear the list of UcClasses
}

void Student::removeUcClass(UcClass ucClass) {
    ucClasses.remove(ucClass);
}

list<Lesson> Student::getLessons() const {
    list<Lesson> allLessons;
    for (const UcClass& ucClass : ucClasses) {
        allLessons.insert(allLessons.end(), ucClass.getLessons().begin(), ucClass.getLessons().end());
    }
    return allLessons;
}


