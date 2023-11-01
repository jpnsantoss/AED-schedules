//
// Created by jpsantos on 25-10-2023.
//

#include "UcClass.h"

#include <utility>
int UcClass::capacity = 0;
UcClass::UcClass(string ucCode, string classCode) {
    this->ucCode = std::move(ucCode);
    this->classCode = std::move(classCode);
    this->studentsNumber = 0;
}

void UcClass::addLessons(const list<Lesson> &newLessons) {
    lessons.insert(lessons.end(), newLessons.begin(), newLessons.end());
}

pair<string, string> UcClass::getUcClassCodes() const {
    return make_pair(ucCode, classCode);
}

void UcClass::addLesson(const Lesson &newLesson) {
    lessons.push_back(newLesson);
}

void UcClass::setStudentsNumber(int number) {
    studentsNumber = number;
}

int UcClass::getStudentsNumber() const {
    return studentsNumber;
}

int UcClass::getCapacity() {
    return capacity;
}

const list<Lesson> &UcClass::getLessons() const {
    return lessons;
}

bool UcClass::operator==(const UcClass &other) const {
    return (ucCode == other.ucCode) && (classCode == other.classCode);
}

bool UcClass::operator<(const UcClass &other) const {
    return classCode < other.classCode;
}
