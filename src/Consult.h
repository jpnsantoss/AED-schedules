//
// Created by Maureen Ah-shu🍩 on 29/10/2023.
//

#ifndef AED2324_PRJ1_G56_CONSULT_H
#define AED2324_PRJ1_G56_CONSULT_H

#include "Dataset.h"
#include "Lesson.h"
#include "Student.h"
#include "UcClass.h"

struct Schedule {
    std::string ucCode;
    std::string classCode;
    std::string weekday;
    double start;
    double end;
    std::string type;
};


class Consult {
public:
    Consult();
    Consult(const Dataset &dataset);
    list<Schedule> findStudentSchedule(const string& code);
    list<Schedule> findClassSchedule(string& code);
    set<Student> findClassStudents(string& code);
    set<Student> findCourseStudent();
    set<Student> findYearStudents(int year);
    unsigned long findClassOccupation(string& code);
    unsigned long findYearOccupation(int year);
    unsigned long findUCOccupation(string& code);
    vector<pair<string, int>> findGreatestUCs();
private:
    Dataset data;
    static list<Schedule> orderSchedule(list<Schedule> schedule);
};


#endif //AED2324_PRJ1_G56_CONSULT_H
