//
// Created by jpsantos on 25-10-2023.
//

#include "Lesson.h"

#include <utility>
/**
 * Creates a lesson with a specific weekDay, start time, duration and type (T, TP, PL)
 * @brief Parameterized constructor
 * @param weekDay
 * @param start
 * @param duration
 * @param type
 */
Lesson::Lesson(string weekDay, double start, double duration, string type)
        : start(start), end(start + duration), type(std::move(type)), weekday(std::move(weekDay)) {}

/**
 * @brief Getter for the start time of the lesson
 * @return lecture's start time.
 */
double Lesson::getStart() const {
    return start;
}

/**
 * @brief Getter for the end time of the lesson
 * @return lecture's end time.
 */
double Lesson::getEnd() const {
    return end;
}

/**
 * @brief Getter for the type of lesson
 * @return type of lesson
 */
std::string Lesson::getType() const {
    return type;
}

/**
 * @brief Getter for the weekday of the lesson
 * @return lecture's weekday
 */
std::string Lesson::getWeekday() const {
    return weekday;
}

/**
 * @brief Checks if two lectures are compatible
 * @param Lesson - the lesson to be compared with
 * @return true if lessons are compatible, false if otherwise
 */
bool Lesson::compatible(const Lesson& lesson) const {
    if (this-> weekday != lesson.getWeekday()) return true;

    if(this->start >= lesson.getEnd() || this->end <= lesson.getStart()) return true;

    return false;
}

