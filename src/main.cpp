//
// Created by jpsantos on 25-10-2023.
//

#include "Dataset.h"
#include "Menu.h"


using namespace std;

int main() {
    Dataset dataset;
    Menu(dataset).main();
    /*
    Dataset dataset;
    cout << "Students:" << "\n\n";

    const std::set<Student>& students = dataset.getStudents();

    if (students.empty()) {
        cout << "No students in the dataset." << endl;
    } else {
        for (const auto& student : students) {
            cout << "Student Name: " << student.getStudentName() << "\n";
            cout << "Student Code: " << student.getStudentCode() << "\n";
            cout << "UcClasses:" << "\n";

            for (const auto& ucClass : student.getUcClasses()) {
                cout << "  " << ucClass.getUcClassCodes().first << " - " << ucClass.getUcClassCodes().second << "\n";
            }

            cout << "\n";
        }
    }
     */

    /*
    Dataset dataset;
    cout << "UcClasses:" << "\n\n";

    const std::vector<UcClass>& ucClasses = dataset.getUcClasses();

    if (ucClasses.empty()) {
        cout << "No UcClasses in the dataset." << endl;
    } else {
        for (const auto& ucClass : ucClasses) {
            cout << "UcClass Code: " << ucClass.getUcClassCodes().first << " - " << ucClass.getUcClassCodes().second << "\n";
            cout << "Lessons:" << "\n";
            for (const auto& lesson : ucClass.getLessons()) {
                cout << "  Weekday: " << lesson.getWeekday() << "\n";
                cout << "  Start Time: " << lesson.getStart() << "\n";
                cout << "  Duration: " << lesson.getEnd() << " minutes\n";
                cout << "  Type: " << lesson.getType() << "\n\n";
            }
        }
    }
     */
}
