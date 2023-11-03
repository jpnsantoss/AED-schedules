//
// Created by jpsantos on 25-10-2023.
//

#include "Dataset.h"

Dataset::Dataset() {
    readUcClasses();
    readLessons();
    readStudents();
    readHistory();
}

const std::set<Student>& Dataset::getStudents() const {
    return students;
}

const std::vector<UcClass>& Dataset::getUcClasses() const {
    return ucClasses;
}

const std::queue<Request>& Dataset::getRequests() const {
    return requests;
}

const std::queue<Request>& Dataset::getHistory() const {
    return history;
}

void Dataset::readUcClasses() {
    ifstream file("files/classes_per_uc.csv");
    if (!file.is_open()) {
        cout << "Error: File 'classes_per_uc.csv' not opened." << endl;
        return;
    }

    string row, ucCode, classCode;
    getline(file, row);

    while (getline(file, row)) {
        istringstream line(row);
        getline(line, ucCode, ',');
        getline(line, classCode, '\r');

        ucClasses.emplace_back(ucCode, classCode);
    }
    file.close();
}

void Dataset::readLessons() {
    ifstream file("files/classes.csv");
    if (!file.is_open()) {
        cout << "Error: File 'classes.csv' not opened." << endl;
        return;  // Exit the method if the file couldn't be opened.
    }

    string row, classCode, ucCode, weekday, startHour, duration, type;

    getline(file, row);  // Read and discard the header row.

    while (getline(file, row)) {
        istringstream line(row);
        getline(line, classCode, ',');
        getline(line, ucCode, ',');
        getline(line, weekday, ',');
        getline(line, startHour, ',');
        getline(line, duration, ',');
        getline(line, type, '\r');

        // Ensure the Lesson constructor parameters are in the correct order.
        Lesson newLesson(weekday, stof(startHour), stof(duration), type);

        for (UcClass& ucClass : ucClasses) {
            if (ucClass.getUcClassCodes() == make_pair(ucCode, classCode)) {
                ucClass.addLesson(newLesson);
            }
        }
    }
    file.close();
}

void Dataset::readStudents() {
    ifstream file("files/students_classes.csv");
    if (!file.is_open()) {
        cout << "Error: File 'students_classes.csv' not opened." << endl;
        return;  // Exit the method if the file couldn't be opened.
    }
    string row, studentCode, studentName, ucCode, classCode, prevStudentCode;
    int maxCapacity = 0;
    Student currentStudent;
    getline(file, row);

    while(getline(file, row)) {
        istringstream line(row);
        getline(line, studentCode, ',');
        getline(line, studentName, ',');
        getline(line, ucCode, ',');
        getline(line, classCode, '\r');

        if(studentCode != prevStudentCode) {
            if(!prevStudentCode.empty()) {
                students.insert(currentStudent);
            }
            currentStudent.reset();
            currentStudent.setStudentCode(studentCode);
            currentStudent.setStudentName(studentName);
        }

        for (UcClass& ucClass : ucClasses) {
            if (ucClass.getUcClassCodes() == make_pair(ucCode, classCode)) {
                ucClass.setStudentsNumber(ucClass.getStudentsNumber() + 1);
                if(ucClass.getStudentsNumber()>maxCapacity) maxCapacity=ucClass.getStudentsNumber();
                currentStudent.addUcClass(ucClass);
            }
        }
        prevStudentCode = studentCode;
    }
    students.insert(currentStudent);
    UcClass::capacity = maxCapacity;
    file.close();
}

void Dataset::handleRequests() {
    while(!requests.empty()) {
        Request request = requests.front();
        if(request.process(&students, ucClasses)) {
               history.push(request);
        }

        requests.pop();
    }
    updateHistory();
    cout << "Request successful." << endl;
}

void Dataset::updateHistory() {
    ofstream file("files/history.csv", ios::app);

    while (!history.empty()) {
        Request request = history.front();
        history.pop();
        file << request.getTypeToString() << ",";
        file << request.getStudent().getStudentCode() << ",";
        if (request.getType() == requestType::Add) {
            file << request.getFinalUcClass().getUcClassCodes().first << ","
                 << request.getFinalUcClass().getUcClassCodes().second;
        } else if (request.getType() == requestType::Remove) {
            file << request.getInitialUcClass().getUcClassCodes().first << ","
                 << request.getInitialUcClass().getUcClassCodes().second;
        } else {
            file << request.getInitialUcClass().getUcClassCodes().first << ","
                 << request.getInitialUcClass().getUcClassCodes().second << ","
                 << request.getFinalUcClass().getUcClassCodes().first << ","
                 << request.getFinalUcClass().getUcClassCodes().second;
        }

        file << endl;
    }
    file.close();
}


void Dataset::addRequest(const Request &request) {
    requests.push(request);
}

void Dataset::readHistory() {
    ifstream file("files/history.csv");
    if (!file.is_open()) {
        cout << "Error: File 'history.csv' not opened." << endl;
        return;
    }

    string row, strType, studentCode;

    while (getline(file, row)) {
        istringstream line(row);
        getline(line, strType, ',');
        getline(line, studentCode, ',');
        Student student = *(students.find(Student(studentCode, "Irrelevant")));
        requestType type = Request::stringToRequestType(strType);
        if(type == requestType::Switch) {
            string initialUcStr, initialClassStr, finalUcStr, finalClassStr;
            getline(line, initialUcStr, ',');
            getline(line, initialClassStr, ',');
            getline(line, finalUcStr, ',');
            getline(line, finalClassStr, '\r');
            UcClass initialUcClass;
            UcClass finalUcClass;
            for(const UcClass& ucClass: ucClasses) {
                if(ucClass.getUcClassCodes().first == initialUcStr && ucClass.getUcClassCodes().second == initialClassStr) {
                    initialUcClass = ucClass;
                } else if(ucClass.getUcClassCodes().first == finalUcStr && ucClass.getUcClassCodes().second == finalClassStr) {
                    finalUcClass = ucClass;
                }
            }
            Request request(type, student, initialUcClass, finalUcClass);
            request.process(&students, ucClasses);

        } else {
            string ucStr, classStr;
            getline(line, ucStr, ',');
            getline(line, classStr, '\r');
            UcClass requestUcClass;
            for(const UcClass& ucClass: ucClasses) {
                if(ucClass.getUcClassCodes().first == ucStr && ucClass.getUcClassCodes().second == classStr) {
                    requestUcClass = ucClass;
                }
            }
            Request request(type, student, requestUcClass);
            request.process(&students, ucClasses);
        }
    }
    file.close();
}

void Dataset::undoRequest() {
    string line;
    vector<string> lines;
    ifstream infile("files/history.csv");

    while (getline(infile,line)) {
        lines.push_back(line);
    }
    infile.close();

    ofstream outfile("files/history.csv");
    if (outfile.is_open())
    {
        for (int i=0; i < lines.size()-1; i++)
        {
            outfile << lines[i] << "\n";
        }
        outfile.close();
    }
    reset();
}

void Dataset::reset() {
    students.clear();
    ucClasses.clear();
    while(!requests.empty()) requests.pop();
    while(!history.empty()) history.pop();
    readUcClasses();
    readLessons();
    readStudents();
    readHistory();
}