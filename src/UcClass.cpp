//
// Created by jpsantos on 25-10-2023.
//

#include "UcClass.h"

#include <utility>
int UcClass::capacity = 0;

/**
 * Will initialize an empty class
 * @brief Default constructor
 */
UcClass::UcClass() : studentsNumber(0) {}

/**
 * Will initialize a class without lessons, lessons are to be added later
 * @brief Parameterized constructor
 * @param ucCode
 * @param classCode
 */
UcClass::UcClass(string ucCode, string classCode) {
    this->ucCode = std::move(ucCode);
    this->classCode = std::move(classCode);
    this->studentsNumber = 0;
}

/**
 * @brief Getter for uc and class codes
 * @return pair of first:ucCode second:classCode
 */
pair<string, string> UcClass::getUcClassCodes() const {
    return make_pair(ucCode, classCode);
}

/**
 * @brief Getter for current number of students
 * @return number of students
 */
int UcClass::getStudentsNumber() const {
    return studentsNumber;
}

/**
 * @brief Getter for the lessons
 * @return list of lessons
 */
const list<Lesson> &UcClass::getLessons() const {
    return lessons;
}

/**
 * @brief Adds a lesson to the class
 * @param newLessons - Lesson to be added
 */
void UcClass::addLesson(const Lesson &newLesson) {
    lessons.push_back(newLesson);
}

/**
 * @brief Setter for current number of students
 * @param number - new number of students
 */
void UcClass::setStudentsNumber(int number) {
    studentsNumber = number;
}

/**
 * @brief Overloads == operator
 * @param other - second class to be compared
 * @return true if the ucCodes and classCodes are the same.
 */
bool UcClass::operator==(const UcClass &other) const {
    return (ucCode == other.ucCode) && (classCode == other.classCode);
}

/**
 * Useless, only used to fix some errors.
 * @param other
 * @return true if classCode is less than the second class code.
 */
bool UcClass::operator<(const UcClass &other) const {
    return classCode < other.classCode;
}

