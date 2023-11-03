//
// Created by jpsantos on 25-10-2023.
//

#ifndef AED2324_PRJ1_G56_LESSON_H
#define AED2324_PRJ1_G56_LESSON_H

#include <string>

using namespace std;
#include <iostream>
class Lesson {
private:
    double start;
    double end;
    std::string type;
    std::string weekday;

public:
    Lesson(string weekDay, double start, double duration, string type);
    double getStart() const;
    double getEnd() const;
    std::string getType() const;
    std::string getWeekday() const;
    bool compatible(const Lesson& lesson) const;
};


#endif //AED2324_PRJ1_G56_LESSON_H
