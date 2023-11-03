#include "Consult.h"
#include <algorithm>

/**
*@brief Displays the schedule of a student.
*Complexity: O(n)
*@param code - Student code.
*@see Schedule
*@return A list of Schedule objects representing the student's schedule.
**/

std::list<Schedule> Consult::findStudentSchedule(const std::string& code) {
    std::list<Schedule> schedule;
    std::list<UcClass> ucs;

    for(const Student& s : data.getStudents()) {
        if(code == s.getStudentCode()) {
            ucs = s.getUcClasses();
            break;
        }
    }

    for(const auto& u: ucs) {
        for(const Lesson& l: u.getLessons()) {
            Schedule s;
            s.ucCode = u.getUcClassCodes().first;
            s.classCode = u.getUcClassCodes().second;
            s.weekday = l.getWeekday();
            s.start = l.getStart();
            s.end = l.getEnd();
            s.type = l.getType();

            schedule.emplace_back(s);
        }
    }

    return orderSchedule(schedule);
}

/**
*@brief Displays the schedule of a class.
*Complexity: O(n)
*@param code - Class code.
*@see Schedule
*@return A list of Schedule objects representing the class schedule.
**/

std::list<Schedule> Consult::findClassSchedule(std::string& code) {
    std::vector<Lesson> result;
    std::list<Schedule> schedule;

    for (char& c: code)
        c = (char)toupper(c);

    for(const UcClass& uc: data.getUcClasses()) {
        if(code == uc.getUcClassCodes().second) {
            for(const auto& l: uc.getLessons()) {
                Schedule s;
                s.ucCode = uc.getUcClassCodes().first;
                s.classCode = uc.getUcClassCodes().second;
                s.weekday = l.getWeekday();
                s.start = l.getStart();
                s.end = l.getEnd();
                s.type = l.getType();

                schedule.emplace_back(s);
            }
        }
    }

    return orderSchedule(schedule);
}

/**
*@brief Displays the list of students in a class.
*Complexity: O(n*m)
*@param code - Class code.
*@see Student
*@return A set of Student objects representing the students in the class.
**/

std::set<Student> Consult::findClassStudents(std::string& code) {
    std::set<Student> result;

    for (char& c: code)
        c = (char)toupper(c);

    for(const Student& s : data.getStudents()) {
        for(const UcClass& uc : s.getUcClasses()) {
            std::string classCode = uc.getUcClassCodes().second;
            if(code == classCode)
                result.insert(s);
        }
    }

    return result;
}

/**
*@brief Displays the list of students enrolled in a UC.
*Complexity: O(n*m)
*@param code - UC code.
*@see Student
*@return A set of Student objects Student representing the students enrolled in the UC.
**/

std::set<Student> Consult::findUcStudents(std::string& code) {
    std::set<Student> result;

    for (char& c: code)
        c = (char)toupper(c);

    for(const auto& s : data.getStudents()) {
        for(const auto& uc : s.getUcClasses()) {
            std::string ucCode = uc.getUcClassCodes().first;
            if(code == ucCode)
                result.insert(s);
        }
    }
    return result;
}

/**
*@brief Displays the list of students from a specific year.
*Complexity: O(n*m)
*@param year - Desired year.
*@see Student
*@return A set of Students objects representing the students from the specified year.
**/

std::set<Student> Consult::findYearStudents(int year) {
    std::set<Student> result;

    for(const Student& s : data.getStudents()) {
        for(const UcClass& uc : s.getUcClasses()) {
            std::string str = uc.getUcClassCodes().second.substr(0, 1);
            if(std::to_string(year) == str)
                result.insert(s);
        }
    }

    return result;
}

/**
*@brief Calculates the number of students enrolled in at least n UCs.
*Complexity: O(n)
*@param n - The minimum number of UCs a student should be enrolled in.
*@see Student
*@return The number of students enrolled in at least n UCs.
**/

int Consult::studentsRegisteredUcs(int n) {
    int result;

    for(const auto& s : data.getStudents()) {
        if (s.getUcClasses().size() >= n) {
            result++;
        }
    }

    return result;
}

/**
*@brief Shows the occupation of a class.
*Complexity: O(n*m)
*@param code - Class code.
*@see Student
*@return The number of students enrolled in the class.
**/

unsigned long Consult::findClassOccupation(std::string& code) {
    std::set<Student> result;

    for (char& c: code)
        c = (char)toupper(c);

    for(const Student& s : data.getStudents()) {
        for(const UcClass& uc : s.getUcClasses()) {
            std::string classCode = uc.getUcClassCodes().second;
            if(code == classCode)
                result.insert(s);
        }
    }

    return result.size();
}

/**
*@brief Shows the occupation of a specific year.
*Complexity: O(n*m)
*@param year - Desired year.
*@see Student
*@return The number of students enrolled in the specified year.
**/

unsigned long Consult::findYearOccupation(int year) {
    std::set<Student> result;

    for(const Student& s : data.getStudents()) {
        for(const UcClass& uc : s.getUcClasses()) {
            std::string str = uc.getUcClassCodes().second.substr(0, 1);
            if(std::to_string(year) == str)
                result.insert(s);
        }
    }

    return result.size();
}

/**
*@brief Shows the occupation of a specific UC.
*Complexity: O(n*m)
*@param code - UC code.
*@see Student
*@return The number of students enrolled in the specified UC.
**/

unsigned long Consult::findUCOccupation(std::string& code) {
    std::set<Student> result;

    for (char& c: code)
        c = (char)toupper(c);

    for(const Student& s : data.getStudents()) {
        for(const UcClass& uc : s.getUcClasses()) {
            std::string ucCode = uc.getUcClassCodes().first;
            if(code == ucCode)
                result.insert(s);
        }
    }

    return result.size();
}

/**
*@brief Shows the UCs with the highest occupation.
*Complexity: O((n*m)+ p*log(p))
*@see Student
*@see UcClass
*@return A vector of pairs (UC, occupation) sorted by decreasing occupation.
**/

std::vector<std::pair<std::string, int>> Consult::findGreatestUCs() {
    std::map<std::string, unsigned long> ucOccupations;

    for (const Student& s : data.getStudents()) {
        for (const UcClass& uc : s.getUcClasses()) {
            std::string ucCode = uc.getUcClassCodes().first;
            ucOccupations[ucCode]++;
        }
    }

    std::vector<std::pair<std::string, int>> result(ucOccupations.begin(), ucOccupations.end());

    sort(result.begin(), result.end(), [](const auto& map1, const auto& map2) {
        return map2.second < map1.second;
    });

    return result;
}

/**
*@brief Gets a vector with all the classes of a specific UC.
*Complexity: O(n)
@param code - UC code.
*@see UcClass
*@return A vector of UcClass objects corresponding to all existing classes of the specified UC.
**/

std::vector<UcClass> Consult::listOfClasses(std::string &code) {
    std::set<UcClass> ucClass;

    for (char& c: code)
        c = (char)toupper(c);

    for(const UcClass& uc: data.getUcClasses()) {
        if(code == uc.getUcClassCodes().first)
            ucClass.insert(uc);
    }

    std::vector<UcClass> classes(ucClass.begin(), ucClass.end());

    return classes;
}

/**
*@brief Finds a student through their code.
*Complexity: O(n)
*@param code - Student code.
*@see Student
*@return The Student object with that student code, or nothing if not found.
**/

Student Consult::findStudent(std::string &code) {
    for (char& c: code)
        c = (char)toupper(c);

    for(const Student& s: data.getStudents()) {
        if(code == s.getStudentCode())
            return s;
    }
    return {};
}

/**
*@brief Sorts the schedule for each lesson by hour and weekday.
*Complexity: O(n*log(n))
*@param schedule - Schedule to be sorted.
*@see Schedule
*@return The sorted schedule.
**/

std::list<Schedule> Consult::orderSchedule(std::list<Schedule> schedule) {
    std::map<std::string, int> weekdaysMap = {
            {"Monday", 1},
            {"Tuesday", 2},
            {"Wednesday", 3},
            {"Thursday", 4},
            {"Friday", 5}
    };

    schedule.sort([&weekdaysMap](const Schedule& obj1, const Schedule& obj2) {
        int weekday1 = weekdaysMap[obj1.weekday];
        int weekday2 = weekdaysMap[obj2.weekday];

        if (weekday1 != weekday2) {
            return weekday1 < weekday2;
        }
        return obj1.start < obj2.start;
    });

    return schedule;
}