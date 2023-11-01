//
// Created by jpsantos on 25-10-2023.
//

#include "Menu.h"

void Menu::main() {
    cout << "******************************************" << endl;
    cout << "*                                        *" << endl;
    cout << "*        L.EIC Schedules                 *" << endl;
    cout << "*                                        *" << endl;
    cout << "*     1) SYSTEM INFORMATION              *" << endl;
    cout << "*     2) REGISTRATION                    *" << endl;
    cout << "*     3) SYSTEM RECORDS                  *" << endl;
    cout << "*     0) EXIT                            *" << endl;
    cout << "*                                        *" << endl;
    cout << "******************************************" << endl;
    cout << "Option: ";
    int option;
    do{
        cin >> option;
        switch(option) {
            case 1: information(); break;
            case 2: registration(); break;
            case 3: records(); break;
            case 0: exit(0);
            default: cout << "Invalid option, please try again: ";
        }
    } while(option != 0 && option != 1 && option != 2 && option != 3);
}

void Menu::information() {
    cout << "************************************************************" << endl;
    cout << "*  system information                                      *" << endl;
    cout << "*                                                          *" << endl;
    cout << "*     1) SCHEDULE OF A STUDENT OR CLASS                    *" << endl;
    cout << "*     2) STUDENTS WITHIN A CLASS, COURSE OR YEAR           *" << endl;
    cout << "*     3) NUMBER OF STUDENTS REGISTERED IN AT LEAST N UCs   *" << endl;
    cout << "*     4) CLASS, YEAR OR UC OCCUPATION                      *" << endl;
    cout << "*     5) UCs WITH THE GREATEST NUMBER OF STUDENTS  +++     *" << endl;
    cout << "*                                                          *" << endl;
    cout << "*                                                 0) BACK  *" << endl;
    cout << "******************************************+*****************" << endl;
    cout << "Option: ";
    int option;
    do{
        cin >> option;
        switch(option) {
            case 1: viewSchedule(); break;
            case 2: viewStudentsCCY(); break;
            case 3: viewNumStudents(); break;
            case 4: viewCYUoccupation(); break;
            case 5: viewUCgreatest(); break;
            case 0: main(); break;
            default: cout << "Invalid option, please try again: ";
        }
    } while(option != 0 && option != 1 && option != 2 && option != 3 && option != 4 && option != 5);
}

void Menu::registration() {
    cout << "******************************************" << endl;
    cout << "*  registration                          *" << endl;
    cout << "*                                        *" << endl;
    cout << "*     1) REGISTRATION IN UC              *" << endl;
    cout << "*     2) REGISTRATION IN CLASS           *" << endl;
    cout << "*     3) REMOVE UC                       *" << endl;
    cout << "*     4) REMOVE CLASS                    *" << endl;
    cout << "*     5) SWITCH UC                       *" << endl;
    cout << "*     6) SWITCH CLASS                    *" << endl;
    cout << "*                                        *" << endl;
    cout << "*                               0) BACK  *" << endl;
    cout << "******************************************" << endl;
    cout << "Option: ";
    int option;
    do{
        cin >> option;
        switch(option) {
            case 1: menuRegUC(); break;
            case 2: menuRegClass(); break;
            case 3: menuRemoveUC(); break;
            case 4: menuRemoveClass(); break;
            case 5: menuSwitchUC(); break;
            case 6: menuSwitchClass(); break;
            case 0: main(); break;
            default: cout << "Invalid option, please try again: ";
        }
    } while(option != 0 && option != 1 && option != 2 && option != 3 &&
            option != 4 && option != 5 && option != 6);
}

void Menu::records() {
    cout << "******************************************" << endl;
    cout << "*  system records                        *" << endl;
    cout << "*                                        *" << endl;
    cout << "*     1)                                 *" << endl;
    cout << "*     2)                                 *" << endl;
    cout << "*     3)                                 *" << endl;
    cout << "*                                        *" << endl;
    cout << "*                               0) BACK  *" << endl;
    cout << "******************************************" << endl;
    cout << "Option: ";
    int option;
    do{
        cin >> option;
        switch(option) {
            case 1: break;
            case 2: break;
            case 3: break;
            case 0: main(); break;
            default: cout << "Invalid option, please try again: ";
        }
    } while(option != 0 && option != 1 && option != 2 && option != 3);
}

void Menu::viewSchedule() {
    cout << "Choose one:" << endl;
    cout << "1) Student" << endl;
    cout << "2) Class" << endl;
    cout << "option: ";
    int option;
    do{
        cin >> option;
        if (option == 1){
            viewStudentSchedule();
        } else {
            if (option == 2) {
                viewClassSchedule();
            } else {
                cout << "Invalid option, please try again: ";
            }
        }
    } while(option != 1 && option != 2);
}

void Menu::viewStudentSchedule() {
    cout << "Enter student code: ";
    string code;
    cin >> code;
    list<Schedule> schedule = consult.findStudentSchedule(code);
    
    cout << "\n**************************************************************************************" << endl;
    cout << "   student schedule" << endl;
    cout << endl;

    for(const auto& s: schedule) {
        cout << "Weekday: " << s.weekday << " \tUC: " << s.ucCode << " \tClass:" << s.classCode
        << " \tType: " << s.type << " \tHour: " << s.start << " \tEnd: " << s.end << endl;
    }

    cout << endl;
    cout << "0) BACK" << endl;
    cout << "**************************************************************************************" << endl;
    goToMenu();
}

void Menu::viewClassSchedule() {
    cout << "Enter class code: ";
    string code;
    cin >> code;
    list<Schedule> schedule = consult.findClassSchedule(code);

    cout << "**************************************************************************************" << endl;
    cout << "   class schedule" << endl;
    cout << endl;

    for(const auto& s: schedule) {
            cout << "Weekday: " << s.weekday << " \tUC: " << s.ucCode << " \tClass:" << s.classCode
                 << " \tType: " << s.type << " \tHour: " << s.start << " \tEnd: " << s.end << endl;
    }

    cout << endl;
    cout << "0) BACK" << endl;
    cout << "**************************************************************************************" << endl;
    goToMenu();
}

void Menu::viewStudentsCCY() {
    set<Student> students;
    int year;
    string code;
    cout << "Choose one:" << endl;
    cout << "1) Class" << endl;
    cout << "2) Course" << endl;
    cout << "3) Year" << endl;
    cout << "option: ";
    int option;
    do{
        cin >> option;
        switch(option) {
            case 1: {
                cout << "Enter class code: ";
                cin >> code;
                students = consult.findClassStudents(code);
            } break;
            case 2: {
                cout << "Enter course code: ";
                cin >> code;
                students = consult.findUcStudents(code);
            } break;
            case 3: {
                cout << "Enter the year: ";
                cin >> year;
                students = consult.findYearStudents(year);
            } break;
            default: cout << "Invalid option, please try again: ";
        }
    } while(option != 1 && option != 2 && option != 3);

    cout << "\n************************************************************" << endl;
    cout << "   list of students" << endl;
    cout << endl;

    for(const auto& s: students)
            cout << "\t" << s.getStudentCode() << " \t" << s.getStudentName() << endl;

    cout << endl;
    cout << "                                                   0) BACK  " << endl;
    cout << "************************************************************" << endl;
    goToMenu();
}

void Menu::viewNumStudents() {
    cout << "Enter the minimum number of UCs: ";
    int n;
    cin >> n;
    int numStudents = consult.studentsRegisteredUcs(n);
    cout << "Number of students enrolled in at least " << n << " UCs: " << numStudents << endl;
    cout << "0) BACK" << endl;
    goToMenu();
}

void Menu::viewCYUoccupation() {
    unsigned long occupation = -1;
    string code;
    int year;
    cout << "Choose one:" << endl;
    cout << "1) Class" << endl;
    cout << "2) Year" << endl;
    cout << "3) UC" << endl;
    cout << "option: ";
    int option;
    do{
        cin >> option;
        switch(option) {
            case 1: {
                cout << "Enter class code: ";
                cin >> code;
                occupation = consult.findClassOccupation(code);
                cout << "\nCLASS " << code << ", " << "OCCUPATION = " << occupation << endl;
            } break;
            case 2: {
                cout << "Enter the year: ";
                cin >> year;
                occupation = consult.findYearOccupation(year);
                cout << "\nYEAR " << year << ", " << "OCCUPATION = " << occupation << endl;
            } break;
            case 3: {
                cout << "Enter UC code: ";
                cin >> code;
                occupation = consult.findUCOccupation(code);
                cout << "\nUC " << code << ", " << "OCCUPATION = " << occupation << endl;
            } break;
            default: cout << "Invalid option, please try again: ";
        }
    } while(option != 1 && option != 2 && option != 3);

    cout << "0) Back" << endl;
    goToMenu();
}

void Menu::viewUCgreatest() {
    vector<pair<string, int>> ucs = consult.findGreatestUCs();
    cout << "n************************************************************" << endl;
    cout << "   ucs with the greatest number of students" << endl;
    cout << endl;

    for(int i = 0; i < 5; i++) 
        cout << "\t" << ucs[i].first << ": " << ucs[i].second << endl;

    cout << endl;
    cout << "                                                   0) BACK  " << endl;
    cout << "************************************************************" << endl;
    goToMenu();
}

void Menu::menuRegUC() {

}

void Menu::menuRegClass() {

}

void Menu::menuRemoveUC() {

}

void Menu::menuRemoveClass() {

}

void Menu::menuSwitchUC() {

}

void Menu::menuSwitchClass() {

}

void Menu::goToMenu() {
    cout << "option: ";
    int option;
    do{
        cin >> option;
        if (option == 0){
            main();
        } else {
            cout << "Invalid option, please try again: ";
        }
    } while(option != 0);
}
