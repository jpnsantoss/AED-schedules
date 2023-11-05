
#include "Dataset.h"
/**
 * initializes the dataset and populates it with ucClasses, lessons, students. also executes the requests from the history.
 * @brief Default constructor
 * @see readUcClasses()
 * @see readLessons()
 * @see readStudents()
 * @see readHistory()
 */
Dataset::Dataset() {
    readUcClasses();
    readLessons();
    readStudents();
    readHistory();
}

/**
 * @brief Getter for students
 * @return set of students
 */
const std::set<Student>& Dataset::getStudents() const {
    return students;
}

/**
 * @brief Getter for ucClasses
 * @return list of ucClasses
 */
const std::list<UcClass>& Dataset::getUcClasses() const {
    return ucClasses;
}

/**
 * Reads the file classes_per_uc.csv and populates the ucClasses list with the data from that file.
 * @brief classes_per_uc reader
 */
void Dataset::readUcClasses() {
    std::ifstream file("files/classes_per_uc.csv");
    if (!file.is_open()) {
        std::cout << "Error: File 'classes_per_uc.csv' not opened." << std::endl;
        return;
    }

    std::string row, ucCode, classCode;
    getline(file, row);

    while (getline(file, row)) {
        std::istringstream line(row);
        getline(line, ucCode, ',');
        getline(line, classCode, '\r');

        ucClasses.emplace_back(ucCode, classCode);
    }
    file.close();
}

/**
 * Reads the file classes.csv and populates each ucClass with its own lessons.
 * @brief classes_per_uc reader
 */
void Dataset::readLessons() {
    std::ifstream file("files/classes.csv");
    if (!file.is_open()) {
        std::cout << "Error: File 'classes.csv' not opened." << std::endl;
        return;
    }

    std::string row, classCode, ucCode, weekday, startHour, duration, type;

    getline(file, row);

    while (getline(file, row)) {
        std::istringstream line(row);
        getline(line, classCode, ',');
        getline(line, ucCode, ',');
        getline(line, weekday, ',');
        getline(line, startHour, ',');
        getline(line, duration, ',');
        getline(line, type, '\r');

        Lesson newLesson(weekday, stof(startHour), stof(duration), type);

        for (UcClass& ucClass : ucClasses) {
            if (ucClass.getUcClassCodes() == make_pair(ucCode, classCode)) {
                ucClass.addLesson(newLesson);
            }
        }
    }
    file.close();
}

/**
 * Reads the students_classes.csv file and populates the students set with the data. Also adds the respective ucClasses to each student and sets the capacity.
 * @brief students_classes reader
 */
void Dataset::readStudents() {
    std::ifstream file("files/students_classes.csv");
    if (!file.is_open()) {
        std::cout << "Error: File 'students_classes.csv' not opened." << std::endl;
        return;
    }
    std::string row, studentCode, studentName, ucCode, classCode, prevStudentCode;
    int maxCapacity = 0;
    Student currentStudent;
    getline(file, row);

    while(getline(file, row)) {
        std::istringstream line(row);
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

/**
 * process the list of requests and if passed, adds them to the history, then updates the history file.
 * @brief Requests queue processor
 * @see updateHistory()
 * @see request.process()
 */
void Dataset::handleRequests() {
    while(!requests.empty()) {
        Request request = requests.front();
        if(request.process(&students, ucClasses)) {
            history.push(request);
            updateHistory();
            std::cout << "Request successful." << std::endl;
        }
        requests.pop();
    }
}

/**
 * gets the approved requests in history queue and types them into the history.csv file
 * @brief history.csv file updater
 */
void Dataset::updateHistory() {
    std::ofstream file("files/history.csv", std::ios::app);

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

        file << std::endl;
    }
    file.close();
}

/**
 * @brief adds a request to the requests queue
 * @param request
 */
void Dataset::addRequest(const Request &request) {
    requests.push(request);
}

/**
 * this gets the data from the history.csv file, handles it accordingly and then process the requests. this function is only called when the dataset starts or resets.
 * @brief process the requests saved in the history file
 * @see request.process()
 */
void Dataset::readHistory() {
    std::ifstream file("files/history.csv");
    if (!file.is_open()) {
        std::cout << "Error: File 'history.csv' not opened." << std::endl;
        return;
    }

    std::string row, strType, studentCode;

    while (getline(file, row)) {
        std::istringstream line(row);
        getline(line, strType, ',');
        getline(line, studentCode, ',');
        Student student = *(students.find(Student(studentCode, "Irrelevant")));
        requestType type = Request::stringToRequestType(strType);
        if(type == requestType::Switch) {
            std::string initialUcStr, initialClassStr, finalUcStr, finalClassStr;
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
            std::string ucStr, classStr;
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

/**
 * Deletes the last line of the history.csv file and then resets the dataset.
 * @brief undo the last approved request
 */
void Dataset::undoRequest() {
    std::string line;
    std::vector<std::string> lines;
    std::ifstream infile("files/history.csv");

    while (getline(infile,line)) {
        lines.push_back(line);
    }
    infile.close();

    std::ofstream outfile("files/history.csv");
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

/**
 * Deletes all the data from the dataset and then reads everything again. useful to undo requests.
 * @brief resets all the data in the dataset.
 * @see readUcClasses()
 * @see readLessons()
 * @see readStudents()
 * @see readHistory()
 */
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