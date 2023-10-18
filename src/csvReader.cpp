//
// Created by Maureen Ah-shu on 15/10/2023.
//

#include "csvReader.h"

vector<classes_per_uc> CsvReader::readClassesPerUc() {
    string header;
    vector<classes_per_uc> data;
    ifstream file("classes_per_uc.csv");
    if(!file.is_open())
        cout << "Error: File 'classes_per_uc.csv' not opened." << endl;

    getline(file, header);

    while (getline(file, header)) {
        stringstream line(header);
        string buffer;
        classes_per_uc row;
        getline(line, buffer, ',');
        row.UcCode = buffer;

        getline(line, buffer, '\r');
        row.ClassCode = buffer;

        data.push_back(row);
    }
    return data;
}

vector<classes> CsvReader::readClasses() {
    string header;
    vector<classes> data;
    ifstream file("classes.csv");
    if(!file.is_open())
        cout << "Error: File 'classes_per_uc.csv' not opened." << endl;

    getline(file, header);

    while (getline(file, header)) {
        stringstream line(header);
        string buffer;
        classes row;
        double start;
        double duration;

        getline(line, buffer, ',');
        row.ClassCode = buffer;

        getline(line, buffer, ',');
        row.UcCode = buffer;

        getline(line, buffer, ',');
        row.Weekday = buffer;

        getline(line, buffer, ',');
        row.StartHour = buffer;
        start = stod(buffer);

        getline(line, buffer, ',');
        row.Duration = buffer;
        duration = stod(buffer);

        row.EndHour = start + duration;


        getline(line, buffer, '\r');
        row.Type = buffer;

        data.push_back(row);
    }
    return data;
}

vector<students_classes> CsvReader::readStudentsClasses() {
    string header;
    vector<students_classes> data;
    ifstream file("classes_per_uc.csv");
    if(!file.is_open())
        cout << "Error: File 'classes_per_uc.csv' not opened." << endl;

    getline(file, header);

    while (getline(file, header)) {
        stringstream line(header);
        string buffer;
        students_classes row;

        getline(line,buffer,',');
        row.StudentCode = buffer;

        getline(line,buffer,',');

        getline(line,buffer,',');
        row.UcCode = buffer;

        getline(line,buffer,'\r');
        row.ClassCode = buffer;

        data.push_back(row);
    }
    return data;
}

