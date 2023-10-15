//
// Created by Maureen Ah-shu on 15/10/2023.
//

#include "file.h"
#include <fstream>
#include <string>

void file::readData() {
    readClasses();
    readClassesUC();
    readStudents();
}

vector<Course> file::readClasses() {
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

vector<ClassUC> file::readClassesUC() {
    vector<ClassUC> data;
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

vector<Student> file::readStudents() {
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