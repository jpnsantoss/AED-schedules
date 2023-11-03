
#ifndef AED2324_PRJ1_G56_DATASET_H
#define AED2324_PRJ1_G56_DATASET_H

#include <iostream>
#include <set>
#include <queue>
#include <fstream>
#include <sstream>
#include "UcClass.h"
#include "Student.h"
#include "Request.h"
class Dataset {
private:
    std::set<Student> students;
    std::list<UcClass> ucClasses;
    std::queue<Request> requests;
    std::queue<Request> history;

    void readUcClasses();
    void readLessons();
    void readStudents();
    void readHistory();
public:
    Dataset();
    const std::set<Student>& getStudents() const;
    const std::list<UcClass>& getUcClasses() const;
    void addRequest(const Request& request);
    void handleRequests();
    void updateHistory();
    void undoRequest();
    void reset();
};


#endif //AED2324_PRJ1_G56_DATASET_H
