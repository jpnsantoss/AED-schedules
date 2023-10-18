//
// Created by Maureen Ah-shu on 15/10/2023.
//

#ifndef AED2324_PRJ1_G56_CSVREADER_H
#define AED2324_PRJ1_G56_CSVREADER_H

#include "lesson.h"
#include "class.h"
#include "student.h"
#include "stdafx.h"

struct classes_per_uc{
    string UcCode;
    string ClassCode;
};
struct classes{
    string ClassCode;
    string UcCode;
    string Weekday;
    string StartHour;
    string Duration;
    double EndHour;
    string Type;
};
struct students_classes{
    string StudentCode;
    string StudentName;
    string UcCode;
    string ClassCode;
};
struct lesson{
    string Weekday;
    double StartHour;
    double Duration;
    double EndHour;
    string Type;
};

class CsvReader {
public:
    vector<classes_per_uc> readClassesPerUc();
    vector<classes> readClasses();
    vector<students_classes> readStudentsClasses();
};


#endif //AED2324_PRJ1_G56_CSVREADER_H
