/**
*@file Consult.h
*Funções que organizam os dados, de modo a consultá-los.
**/

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
    const vector<Student>& getStudentList(const Dataset& dataset);
    list<Schedule> findStudentSchedule(const string& code);
    list<Schedule> findClassSchedule(string& code);
    set<Student> findClassStudents(string& code);
    set<Student> findUcStudents(string& code);
    set<Student> findYearStudents(int year);
    int studentsRegisteredUcs(int n);
    unsigned long findClassOccupation(string& code);
    unsigned long findYearOccupation(int year);
    unsigned long findUCOccupation(string& code);
    vector<UcClass> listOfClasses(string& code);
    vector<pair<string, int>> findGreatestUCs();
    Student * findStudent(string& code);
    UcClass * findUc(string& code);
private:
    Dataset data;
    static list<Schedule> orderSchedule(list<Schedule> schedule);
};


#endif //AED2324_PRJ1_G56_CONSULT_H
