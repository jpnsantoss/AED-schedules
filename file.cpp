//
// Created by Maureen Ah-shu on 15/10/2023.
//

#include "file.h"

void File::readData() {
    readLessons();
    readClasses();
    readStudents();
}

vector<Course> File::readLessons() {
    vector<Course> data;
    string header;

    ifstream file("data/classes.csv");
    if(!file.is_open())
        cout << "Error: File 'classes.csv' not opened." << endl;

    getline(file, header);

    while(!file.eof()){

        data.emplace_back();
    }
    file.close();
    return data;
}

vector<Class> File::readClasses() {
    vector<Class> data;
    string header;

    ifstream file("data/classes_per_uc.csv");
    if(!file.is_open())
        cout << "Error: File 'classes_per_uc.csv' not opened." << endl;

    getline(file, header);

    while(!file.eof()){

        data.emplace_back();
    }
    file.close();
    return data;
}

vector<Student> File::readStudents() {
    vector<Student> data;
    string header;

    ifstream file("data/students_classes.csv");
    if(!file.is_open())
        cout << "Error: File 'students_classes.csv' not opened." << endl;

    getline(file, header);

    while(!file.eof()){

    }
    file.close();
    return data;
}