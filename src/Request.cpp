
#include "Request.h"

#include <utility>
/**
 * Constructor used to implement a switch request.
 * @brief switch type constructor
 * @param type
 * @param student
 * @param initialUcClass
 * @param finalUcClass
 */
Request::Request(requestType type, Student student, UcClass& initialUcClass, UcClass& finalUcClass)
        : type(type), student(std::move(student)), initialUcClass(initialUcClass), finalUcClass(finalUcClass) {
}

/**
 * Constructor used to implement a add or remove requests.
 * @brief add/remove type constructor
 * @param type
 * @param student
 * @param ucClass
 */
Request::Request(requestType type, Student student, UcClass& ucClass)
        : type(type), student(std::move(student)), initialUcClass(ucClass), finalUcClass(ucClass) {
}

/**
 * Checks if the class i want to add/switch unbalances or not the students number between classes of that uc.
 * @brief verifies the balance between the classes of a given Uc.
 * @param ucClasses
 * @return true if students of class to add has a difference not greater than 3 students to the minimum class, false otherwise.
 */
bool Request::checkBalance(const std::list<UcClass>& ucClasses) {
    int min = ucClasses.begin()->getStudentsNumber();
    for (const UcClass& ucClass: ucClasses) {

        if(ucClass.getUcClassCodes().first == finalUcClass.getUcClassCodes().first) {
            if(ucClass.getStudentsNumber() < min) min = ucClass.getStudentsNumber();
        }
    }
    if(finalUcClass.getStudentsNumber() - min > 3) return false;
    return true;
}

/**
 * @brief checks if the lessons of the new class doesn't conflict with the current lessons
 * @return true of the lessons are not compatible, false otherwise.
 */
bool Request::checkConflict() {
    for(const Lesson& studentLesson: this->student.getLessons()) {
        for(const Lesson& ucClassLesson: this->finalUcClass.getLessons()) {
            if(!studentLesson.compatible(ucClassLesson)) return true;
            break;
        }
    }
    return false;
}

/**
 * @brief checks if user already is in a certain uc
 * @return true if user is already in that uc, false otherwise
 */
bool Request::ucAlreadyExits() {
    for(const UcClass& ucClass: student.getUcClasses()) {
        if(ucClass.getUcClassCodes().first == finalUcClass.getUcClassCodes().first) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Getter for the request type
 * @return type in format requestType::
 */
requestType Request::getType() const {
    return type;
}

/**
 * @brief Getter for the student
 * @return Student
 */
Student Request::getStudent() const  {
    return student;
}

/**
 * @brief Getter for the initial ucClass
 * @return initialUcClass
 */
UcClass Request::getInitialUcClass() const {
    return initialUcClass;
}

/**
 * @brief Getter for the final ucClass
 * @return finalUcClass
 */
UcClass Request::getFinalUcClass() const {
    return finalUcClass;
}

/**
 * @brief getter for the request type in string format
 * @return type in string format
 */
std::string Request::getTypeToString() {
    switch (type) {
        case requestType::Add:
            return "Add";
        case requestType::Remove:
            return "Remove";
        case requestType::Switch:
            return "Switch";
        default:
            return "Unknown";
    }
}

/**
 *
 * @param typeStr
 * @return
 */
requestType Request::stringToRequestType(const std::string &typeStr) {
    if (typeStr == "Add") {
        return requestType::Add;
    } else if (typeStr == "Remove") {
        return requestType::Remove;
    } else {
        return requestType::Switch;
    }
}

/**
 * To process the request, first you create a copy of the student, called new student
 * Then, checks the request type and proceeds accordingly with the proper conditions.
 * If the requests can pass all the conditions, we apply the changes to the student and then change the current student in the dataset for the new student.
 * @brief Handles the request and approves it or not
 * @see ucAlreadyExists()
 * @see checkConflict()
 * @see checkBalance()
 * @param students
 * @param ucClasses
 * @return true if the request is approved, false otherwise
 */
bool Request::process(std::set<Student>* students, const std::list<UcClass> &ucClasses)  {

    auto newStudentItr = (*students).find(this->student);
    if(newStudentItr==students->end()) {
        std::cout<<"Failed! Student does not exist anymore!";
        return {};
    }
    Student newStudent = *newStudentItr;
    switch(this->type) {
        case requestType::Remove:
            newStudent.removeUcClass(this->initialUcClass);
            initialUcClass.setStudentsNumber(initialUcClass.getStudentsNumber() - 1);
            break;

        case requestType::Add:
            if(ucAlreadyExits()) {
                std::cout << "Student is already enrolled in this uc, try to switch instead." << std::endl;
                return false;
            }

            if(newStudent.getUcClasses().size() >= 6) {
                std::cout << "Student is already enrolled in 6 ucs." << std::endl;
                return false;
            }

            if(finalUcClass.getStudentsNumber() >= UcClass::capacity) {
                std::cout << "This class is already full." << std::endl;
                return false;
            }

            if(checkConflict()) {
                std::cout << "There is a conflict between the Student's classes and the new class." << std::endl;
                return false;
            }

            if(!checkBalance(ucClasses)) {
                std::cout << "The number of students in each class must be balanced." << std::endl;
                return false;
            }

            newStudent.addUcClass(finalUcClass);

            this->finalUcClass.setStudentsNumber(finalUcClass.getStudentsNumber() + 1);

            break;

        case requestType::Switch:
            if(initialUcClass.getUcClassCodes().first != finalUcClass.getUcClassCodes().first) {
                std::cout << "You have to switch classes from the same uc." << std::endl;
                return false;
            }

            if(finalUcClass.getStudentsNumber() >= UcClass::capacity) {
                std::cout << "This class is already full." << std::endl;
                return false;
            }
            newStudent.removeUcClass(initialUcClass);
            initialUcClass.setStudentsNumber(initialUcClass.getStudentsNumber() - 1);
            if(checkConflict()) {
                std::cout << "There is a conflict between the Student's classes and the new class." << std::endl;
                newStudent.addUcClass(initialUcClass);
                initialUcClass.setStudentsNumber(initialUcClass.getStudentsNumber() + 1);
                return false;
            }
            if(!checkBalance(ucClasses)) {
                std::cout << "The number of students in each class must be balanced." << std::endl;
                initialUcClass.setStudentsNumber(initialUcClass.getStudentsNumber() + 1);
                newStudent.addUcClass(initialUcClass);
                return false;
            }
            newStudent.addUcClass(finalUcClass);
            this->finalUcClass.setStudentsNumber(finalUcClass.getStudentsNumber() + 1);
            break;
    }
    auto itr = students->find(student);
    students->erase(itr);
    students->insert(newStudent);
    this->student = newStudent;
    return true;
}

