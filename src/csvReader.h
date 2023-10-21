//
// Created by Maureen Ah-shu on 15/10/2023.
//

#ifndef AED2324_PRJ1_G56_CSVREADER_H
#define AED2324_PRJ1_G56_CSVREADER_H

#include "stdafx.h"

struct file_classes_per_uc{
    string ucCode;
    string classCode;
};
struct file_classes{
    string classCode;
    string ucCode;
    string weekday;
    string startHour;
    string duration;
    string type;
};
struct file_students_classes{
    string studentCode;
    string studentName;
    string ucCode;
    string classCode;
};

class CsvReader {
public:
    vector<file_classes_per_uc> readClassesPerUc();
    vector<file_classes> readClasses();
    vector<file_students_classes> readStudentsClasses();
};


#endif //AED2324_PRJ1_G56_CSVREADER_H
