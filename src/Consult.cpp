//
// Created by Maureen Ah-shu🍩 on 29/10/2023.
//

#include "Consult.h"

Consult::Consult() {}

Consult::Consult(const Dataset &dataset) {
    this->data = dataset;
}

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

set<Student> Consult::findCourseStudent() {
    set<Student> result;



    return result;
}

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

bool Consult::findStudent(std::string &code) {
    for (char& c: code)
        c = (char)toupper(c);

    for(const Student& s: data.getStudents()) {
        if(code == s.getStudentCode())
            return true;
    }
    return false;
}

bool Consult::findUc(std::string &code) {
    for (char& c: code)
        c = (char)toupper(c);

    for(const UcClass& uc: data.getUcClasses()) {
        if(code == uc.getUcClassCodes().first)
            return true;
    }
    return false;
}

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