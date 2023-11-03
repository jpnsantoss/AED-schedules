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
    Consult(Dataset& dataset) : data(dataset) {};
    const std::vector<Student>& getStudentList(const Dataset& dataset);
    std::list<Schedule> findStudentSchedule(const std::string& code);
    std::list<Schedule> findClassSchedule(std::string& code);
    std::set<Student> findClassStudents(std::string& code);
    std::set<Student> findUcStudents(std::string& code);
    std::set<Student> findYearStudents(int year);
    int studentsRegisteredUcs(int n);
    unsigned long findClassOccupation(std::string& code);
    unsigned long findYearOccupation(int year);
    unsigned long findUCOccupation(std::string& code);
    std::vector<UcClass> listOfClasses(std::string& code);
    std::vector<std::pair<std::string, int>> findGreatestUCs();
    Student findStudent(std::string& code);
private:
    Dataset& data;
    static std::list<Schedule> orderSchedule(std::list<Schedule> schedule);
};


#endif //AED2324_PRJ1_G56_CONSULT_H