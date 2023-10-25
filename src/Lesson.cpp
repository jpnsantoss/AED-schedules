//
// Created by jpsantos on 25-10-2023.
//

#include "Lesson.h"

#include <utility>

Lesson::Lesson(string weekDay, double start, double duration, string type)
        : start(start), end(start + duration), type(std::move(type)), weekday(std::move(weekDay)) {
    // Constructor implementation
}

// Getter method implementations
double Lesson::getStart() const {
    return start;
}

double Lesson::getEnd() const {
    return end;
}

std::string Lesson::getType() const {
    return type;
}

std::string Lesson::getWeekday() const {
    return weekday;
}
