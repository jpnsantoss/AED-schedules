
#include "Student.h"

#include <utility>

/**
 * Will initialize an empty student
 * @brief Default constructor
 */
Student::Student() {}

/**
 * Will initialize a student without ucClasses, ucClasses are to be added later
 * @brief Parameterized constructor
 * @param studentCode
 * @param studentName
 */
Student::Student(std::string  studentCode, std::string  studentName)
        : studentCode(std::move(studentCode)), studentName(std::move(studentName)) {
}


/**
 * @brief Setter for the student code
 * @param code - student code
 */
void Student::setStudentCode(const std::string& code) {
    studentCode = code;
}
/**
 * @brief Getter for student code
 * @return studentCode
 */
std::string Student::getStudentCode() const {
    return studentCode;
}

/**
 * @brief Setter for student name
 * @param name
 */
void Student::setStudentName(const std::string& name) {
    studentName = name;
}
/**
 * @brief Getter for student name
 * @return
 */
std::string Student::getStudentName() const {
    return studentName;
}

/**
 * @brief adds an ucClass to the student
 * @param ucClass
 */
void Student::addUcClass(const UcClass& ucClass) {

    ucClasses.push_back(ucClass);
}

/**
 * @brief Getter for student ucClasses
 * @return list of ucClasses
 */
const std::list<UcClass>& Student::getUcClasses() const {
    return ucClasses;
}


/**
 * @brief Overlods < operator
 * @param other
 * @return true if studentCode < other.studentCode, false otherwise
 */
bool Student::operator<(const Student &other) const {
    return studentCode < other.studentCode;
}

/**
 * @brief Resets user attributes
 */
void Student::reset() {
    studentCode = "";
    studentName = "";
    ucClasses.clear();
}

/**
 * @brief removes an ucClass from the student
 * @param ucClass
 */
void Student::removeUcClass(const UcClass& ucClass) {
    ucClasses.remove(ucClass);
}

/**
 * @brief Getter for the lessons the student has
 * @return list of Lessons
 */
std::list<Lesson> Student::getLessons() const {
    std::list<Lesson> allLessons;
    for (const UcClass& ucClass : ucClasses) {
        allLessons.insert(allLessons.end(), ucClass.getLessons().begin(), ucClass.getLessons().end());
    }
    return allLessons;
}


