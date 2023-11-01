//
// Created by jpsantos on 25-10-2023.
//

#ifndef AED2324_PRJ1_G56_DATASET_H
#define AED2324_PRJ1_G56_DATASET_H

#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include "UcClass.h"
#include "Student.h"
#include "Request.h"
class Dataset {
private:
    set<Student> students;
    vector<UcClass> ucClasses;
    queue<Request> requests;
    queue<Request> history;

    void readUcClasses();
    void readLessons();
    void readStudents();
public:
    Dataset();

    // Getter methods
    const std::set<Student>& getStudents() const;
    const std::vector<UcClass>& getUcClasses() const;
    const std::queue<Request>& getRequests() const;
    const std::queue<Request>& getHistory() const;

    void handleRequests();
    /* TODO:
     void handleRequests();
    void pushRequestToQueue(Request request);
    queue<Request> getMainRequest() const;
    queue<Request> getArchiveRequest() const;

     also missing archive feature, do that and go to sleep :)
     */
};


#endif //AED2324_PRJ1_G56_DATASET_H
