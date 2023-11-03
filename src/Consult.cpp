
#include "Consult.h"
#include <algorithm>

/**
*@brief Default Constructor for the Consult class.
**/

Consult::Consult() {}

/**
*@brief Constructor that takes a Dataset object.
*@param dataset - dataset to be used for the query.
**/

Consult::Consult(const Dataset &dataset) {
    this->data = dataset;
}

/**
*@brief Displays the schedule of a student.
*Complexity: O(n)
*@param code - Student code.
*@see Schedule
*@return A list of Schedule objects representing the student's schedule.
**/

list<Schedule> Consult::findStudentSchedule(const string& code) {
    list<Schedule> schedule;
    list<UcClass> ucs;

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

list<Schedule> Consult::findClassSchedule(string& code) {
    vector<Lesson> result;
    list<Schedule> schedule;

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

set<Student> Consult::findClassStudents(string& code) {
    set<Student> result;

    for (char& c: code)
        c = (char)toupper(c);

    for(const Student& s : data.getStudents()) {
        for(const UcClass& uc : s.getUcClasses()) {
            string classCode = uc.getUcClassCodes().second;
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

set<Student> Consult::findUcStudents(string& code) {
    set<Student> result;

    for (char& c: code)
        c = (char)toupper(c);

    for(const Student& s : data.getStudents()) {
        for(const UcClass& uc : s.getUcClasses()) {
            string ucCode = uc.getUcClassCodes().first;
            if(code == ucCode)
                result.insert(s);
        }
    }
    return result;
}

/**
*@brief Displays the list of students from a specific year.
*Complexity: O(n*m)
*@param year - desired year.
*@see Student
*@return A set of Students objects representing the students from the specified year.
**/

set<Student> Consult::findYearStudents(int year) {
    set<Student> result;

    for(const Student& s : data.getStudents()) {
        for(const UcClass& uc : s.getUcClasses()) {
            string str = uc.getUcClassCodes().second.substr(0, 1);
            if(to_string(year) == str)
                result.insert(s);
        }
    }

    return result;
}

/**
*@brief Calculates the number of students enrolled in at least n UCs.
*Complexity: O(n)
*@param n - minimum number of UCs a student should be enrolled in.
*@see Student
*@return The number of students enrolled in at least n UCs.
**/

int Consult::studentsRegisteredUcs(int n) {
    int result;

    for(const Student& s : data.getStudents()) {
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

unsigned long Consult::findClassOccupation(string& code) {
    set<Student> result;

    for (char& c: code)
        c = (char)toupper(c);

    for(const Student& s : data.getStudents()) {
        for(const UcClass& uc : s.getUcClasses()) {
            string classCode = uc.getUcClassCodes().second;
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
    set<Student> result;

    for(const Student& s : data.getStudents()) {
        for(const UcClass& uc : s.getUcClasses()) {
            string str = uc.getUcClassCodes().second.substr(0, 1);
            if(to_string(year) == str)
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

unsigned long Consult::findUCOccupation(string& code) {
    set<Student> result;

    for (char& c: code)
        c = (char)toupper(c);

    for(const Student& s : data.getStudents()) {
        for(const UcClass& uc : s.getUcClasses()) {
            string ucCode = uc.getUcClassCodes().first;
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

vector<pair<string, int>> Consult::findGreatestUCs() {
    std::map<std::string, unsigned long> ucOccupations;

    for (const Student& s : data.getStudents()) {
        for (const UcClass& uc : s.getUcClasses()) {
            string ucCode = uc.getUcClassCodes().first;
            ucOccupations[ucCode]++;
        }
    }

    vector<pair<string, int>> result(ucOccupations.begin(), ucOccupations.end());

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

vector<UcClass> Consult::listOfClasses(string &code) {
    set<UcClass> ucClass;

    for (char& c: code)
        c = (char)toupper(c);

    for(const UcClass& uc: data.getUcClasses()) {
        if(code == uc.getUcClassCodes().first)
            ucClass.insert(uc);
    }

    vector<UcClass> classes(ucClass.begin(), ucClass.end());

    return classes;
}

/**
*@brief Finds a student through their code.
*Complexity: O(n)
*@param code - Student code.
*@see Student
*@return A pointer to the Student object corresponding to the specified Student, or nullptr if not found.
**/

Student * Consult::findStudent(std::string &code) {
    for (char& c: code)
        c = (char)toupper(c);

    for(const Student& s: data.getStudents()) {
        if(code == s.getStudentCode())
            return const_cast<Student *>(&s);
    }
    return nullptr;
}

/**
*@brief Finds a UC through its code.
*Complexity: O(n)
*@param code - UC code.
*@see UcClass
*@return A pointer to the UcClass object corresponding to the specified UC, or nullptr if not found.
**/

UcClass * Consult::findUc(std::string &code) {
    for (char& c: code)
        c = (char)toupper(c);

    for(const UcClass& uc: data.getUcClasses()) {
        if(code == uc.getUcClassCodes().first)
            return const_cast<UcClass *>(&uc);
    }
    return nullptr;
}

/**
*@brief Sorts the schedule for each lesson by hour and weekday.
*Complexity: O(n*log(n))
*@param schedule - Schedule to be sorted.
*@see Schedule
*@return The sorted schedule.
**/

list<Schedule> Consult::orderSchedule(list<Schedule> schedule) {
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