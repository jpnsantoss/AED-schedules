//
// Created by jpsantos on 09-10-2023.
//

#ifndef AED2324_PRJ1_G56_LESSON_H
#define AED2324_PRJ1_G56_LESSON_H

#include "stdafx.h"

class Lesson {
private:
    string ucCode;
    string classCode;
    double startHour;
    double endHour;
    string type;
    string weekday;

public:

    Lesson(string ucCode, string classCode, double startHour, double endHour, string type, string weekday)
            : ucCode(std::move(ucCode)), classCode(std::move(classCode)), startHour(startHour), endHour(endHour), type(std::move(type)), weekday(std::move(weekday)) {
        // Constructor body is empty because all the work is done in the member initializer list.
    }

    // Getters for private member variables
    [[nodiscard]] const string& getUcCode() const {
        return ucCode;
    }

    [[nodiscard]] const string& getClassCode() const {
        return classCode;
    }

    [[nodiscard]] double getStartHour() const {
        return startHour;
    }

    [[nodiscard]] double getEndHour() const {
        return endHour;
    }

    [[nodiscard]] const string& getType() const {
        return type;
    }

    [[nodiscard]] const string& getWeekday() const {
        return weekday;
    }
};


#endif //AED2324_PRJ1_G56_LESSON_H
