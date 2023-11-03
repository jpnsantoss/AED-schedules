
#ifndef AED2324_PRJ1_G56_UCCLASS_H
#define AED2324_PRJ1_G56_UCCLASS_H

#include <string>
#include <list>
#include "Lesson.h"

class UcClass {
private:
    std::string ucCode;
    std::string classCode;
    list<Lesson> lessons;
    int studentsNumber;

public:
    static int capacity;
    UcClass();
    UcClass(std::string ucCode, std::string classCode);
    pair<std::string, std::string> getUcClassCodes() const;
    int getStudentsNumber() const;
    const list<Lesson>& getLessons() const;
    void setStudentsNumber(int number);
    void addLesson(const Lesson& newLesson);
    bool operator==(const UcClass& other) const;
    bool operator<(const UcClass &other) const;
};



#endif //AED2324_PRJ1_G56_UCCLASS_H
