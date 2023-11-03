
#ifndef AED2324_PRJ1_G56_STUDENT_H
#define AED2324_PRJ1_G56_STUDENT_H

#include <string>
#include <list>
#include "UcClass.h"

class Student {
private:
    std::string studentCode;
    std::string studentName;
    list<UcClass> ucClasses;

public:
    Student();
    Student(std::string studentCode, std::string studentName);
    void setStudentCode(const std::string& code);
    std::string getStudentCode() const;
    void setStudentName(const std::string& name);
    std::string getStudentName() const;
    void addUcClass(const UcClass& ucClass);
    const list<UcClass>& getUcClasses() const;
    bool operator<(const Student &other) const;
    void reset();
    void removeUcClass(const UcClass& ucClass);
    list<Lesson> getLessons() const;
};


#endif //AED2324_PRJ1_G56_STUDENT_H
