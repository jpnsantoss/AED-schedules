//
// Created by Maureen Ah-shu on 15/10/2023.
//

#include "csvReader.h"

vector<file_classes_per_uc> CsvReader::readClassesPerUc() {
    string header;
    vector<file_classes_per_uc> data;
    ifstream file("classes_per_uc.csv");
    if(!file.is_open())
        cout << "Error: File 'classes_per_uc.csv' not opened." << endl;

    getline(file, header);

    while (getline(file, header)) {
        stringstream line(header);
        string buffer;
        file_classes_per_uc row;
        getline(line, buffer, ',');
        row.ucCode = buffer;

        getline(line, buffer, '\r');
        row.classCode = buffer;

        data.push_back(row);
    }
    return data;
}

vector<file_classes> CsvReader::readClasses() {
    string header;
    vector<file_classes> data;
    ifstream file("classes.csv");
    if(!file.is_open())
        cout << "Error: File 'classes_per_uc.csv' not opened." << endl;

    getline(file, header);

    while (getline(file, header)) {
        stringstream line(header);
        string buffer;
        file_classes row;

        getline(line, buffer, ',');
        row.classCode = buffer;

        getline(line, buffer, ',');
        row.ucCode = buffer;

        getline(line, buffer, ',');
        row.weekday = buffer;

        getline(line, buffer, ',');
        row.startHour = buffer;

        getline(line, buffer, ',');
        row.duration = buffer;


        getline(line, buffer, '\r');
        row.type = buffer;

        data.push_back(row);
    }
    return data;
}

vector<file_students_classes> CsvReader::readStudentsClasses() {
    string header;
    vector<file_students_classes> data;
    ifstream file("classes_per_uc.csv");
    if(!file.is_open())
        cout << "Error: File 'classes_per_uc.csv' not opened." << endl;

    getline(file, header);

    while (getline(file, header)) {
        stringstream line(header);
        string buffer;
        file_students_classes row;

        getline(line,buffer,',');
        row.studentCode = buffer;

        getline(line,buffer,',');

        getline(line,buffer,',');
        row.ucCode = buffer;

        getline(line,buffer,'\r');
        row.classCode = buffer;

        data.push_back(row);
    }
    return data;
}

