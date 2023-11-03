//
// Created by jpsantos on 25-10-2023.
//

#include "Menu.h"

/**
 *  Outputs the Main menu.
 *  Complexity: O(1).
 */
void Menu::main() {
    cout << "******************************************\n"
         << "*                                        *\n"
         << "*        L.EIC Schedules                 *\n"
         << "*                                        *\n"
         << "*     1) SYSTEM INFORMATION              *\n"
         << "*     2) REGISTRATION                    *\n"
         << "*     0) EXIT                            *\n"
         << "*                                        *\n"
         << "******************************************\n"
         << "Option: " << endl;
    int option;
    do{
        cin >> option;
        switch(option) {
            case 1: information(); break;
            case 2: registration(); break;
            case 0: exit(0);
            default: cout << "Invalid option, please try again: ";
        }
    } while(option != 0 && option != 1 && option != 2 && option != 3);
}

/**
 *  Outputs the Information menu.
 *  Complexity: O(1).
 */
void Menu::information() {
    cout << "************************************************************\n"
         << "*  system information                                      *\n"
         << "*                                                          *\n"
         << "*     1) SCHEDULE OF A STUDENT OR CLASS                    *\n"
         << "*     2) STUDENTS WITHIN A CLASS, COURSE OR YEAR           *\n"
         << "*     3) NUMBER OF STUDENTS REGISTERED IN AT LEAST N UCs   *\n"
         << "*     4) CLASS, YEAR OR UC OCCUPATION                      *\n"
         << "*     5) UCs WITH THE GREATEST NUMBER OF STUDENTS          *\n"
         << "*                                                          *\n"
         << "*                                                 0) BACK  *\n"
         << "******************************************+*****************\n"
         << "Option: " << endl;
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

/**
 *   Outputs the Registration menu.
 *   Complexity: O(1).
 */
void Menu::registration() {
    cout << "******************************************\n"
         << "*  registration                          *\n"
         << "*                                        *\n"
         << "*     1) REGISTRATION IN UC              *\n"
         << "*     2) REMOVE UC                       *\n"
         << "*     3) SWITCH CLASS                    *\n"
         << "*     4) UNDO                            *\n"
         << "*                                        *\n"
         << "*                               0) BACK  *\n"
         << "******************************************\n"
         << "Option: " << endl;
    int option;
    do{
        cin >> option;
        switch(option) {
            case 1: menuRegUC(); break;
            case 2: menuRemoveUC(); break;
            case 3: menuSwitchClass(); break;
            case 4: data.undoRequest(); main(); break;
            case 0: main(); break;
            default: cout << "Invalid option, please try again: ";
        }
    } while(option != 0 && option != 1 && option != 2 && option != 3 && option != 4);
}

/**
 *  Asks the user what option they want;
 *  1) If they want to see the student schedule.
 *  2) If they want to see the class schedule.
 *  Complexity: O(1).
 */
void Menu::viewSchedule() {
    cout << "Choose one:\n"
         << "1) Student\n"
         << "2) Class\n"
         << "option: ";
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

/**
 *  Outputs the user schedule.
 *  Complexity: O(n).
 */
void Menu::viewStudentSchedule() {
    cout << "Enter student code: ";
    string code;
    cin >> code;
    list<Schedule> schedule = consult.findStudentSchedule(code);

    if(!schedule.empty()) {
        cout << "*****************************************************************************************\n"
             << "   student schedule\n\n";

        for (const auto &s: schedule) {
            cout << "Weekday: " << s.weekday << " \tUC: " << s.ucCode << " \tClass:" << s.classCode
                 << " \tType: " << s.type << " \tStart: " << s.start << "\t\tEnd: " << s.end << "\n";
        }

        cout << "\n0) BACK\n"
             << "*****************************************************************************************" << endl;
    } else {
        cout << "\nStudent not found!\n"
             << "0) Back\n";
    }
    goToInformationMenu();
}

/**
 *  Outputs the class schedule.
 *  Complexity: O(n).
 */
void Menu::viewClassSchedule() {
    cout << "Enter class code: ";
    string code;
    cin >> code;
    list<Schedule> schedule = consult.findClassSchedule(code);

    if(!schedule.empty()) {
        cout << "*****************************************************************************************\n"
             << "   class schedule\n\n";

        for (const auto &s: schedule) {
            cout << "Weekday: " << s.weekday << " \tUC: " << s.ucCode << " \tClass:" << s.classCode
                 << " \tType: " << s.type << " \tStart: " << s.start << "\t\tEnd: " << s.end << "\n";
        }

        cout << "\n0) BACK\n"
             << "*****************************************************************************************" << endl;
        goToInformationMenu();
    } else {
        cout << "\nClass not found!\n"
             << "0) Back" << endl;
    }
    goToInformationMenu();
}

/**
 *  Asks the user what option they want;
 *  1) Show all students in a given class.
 *  2) Show all students in a given uc.
 *  3) Show all students in a given year.
 *  Complexity: O(n).
 */
void Menu::viewStudentsCCY() {
    set<Student> students;
    int year;
    string code;
    cout << "Choose one:\n"
         << "1) Class\n"
         << "2) Course\n"
         << "3) Year\n"
         << "option: ";
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

    if(!students.empty()) {
        cout << "\n************************************************************\n";
        cout << "   list of students\n\n";

        for (const auto &s: students)
            cout << "\t" << s.getStudentCode() << " \t" << s.getStudentName() << "\n";

        cout << "\n                                                   0) BACK\n"
             << "************************************************************" << endl;
    } else {
        cout << "\nResult not found!\n"
             << "0) Back" << endl;
    }
    goToInformationMenu();
}

/**
 *  Outputs the number of students from a given number of UCs.
 *  Complexity:
 */
void Menu::viewNumStudents() {
    cout << "Enter number of UCs: ";
    int ucs;
    cin >> ucs;

    int num = 0;
    cout << "\nNUMBER OF STUDENTS REGISTERED IN AT LEAST " << ucs << " UCs = " << num << "\n"
         << "0) BACK" << endl;
    goToInformationMenu();
}

/**
 *  Asks the user what option they want;
 *  1) The number of students in a given class.
 *  2) The number of students in a given year.
 *  3) The number of students in a given uc.
 *  Complexity: O(1).
 */
void Menu::viewCYUoccupation() {
    unsigned long occupation = -1;
    string code;
    int year;
    cout << "Choose one:\n"
         << "1) Class\n"
         << "2) Year\n"
         << "3) UC\n"
         << "option: ";
    int option;
    do{
        cin >> option;
        switch(option) {
            case 1: {
                cout << "Enter class code: ";
                cin >> code;
                occupation = consult.findClassOccupation(code);
                if(occupation > 0)
                    cout << "\nCLASS " << code << ", " << "OCCUPATION = " << occupation << "\n";
                else
                    cout << "\nClass not found!\n";
            } break;
            case 2: {
                cout << "Enter the year: ";
                cin >> year;
                occupation = consult.findYearOccupation(year);
                if(occupation > 0)
                    cout << "\nYEAR " << year << ", " << "OCCUPATION = " << occupation << "\n";
                else
                    cout << "\nYear not found!\n";
            } break;
            case 3: {
                cout << "Enter UC code: ";
                cin >> code;
                occupation = consult.findUCOccupation(code);
                if (occupation > 0)
                    cout << "\nUC " << code << ", " << "OCCUPATION = " << occupation << "\n";
                else
                    cout << "\nUC not found!\n";
            } break;
            default: cout << "Invalid option, please try again: ";
        }
    } while(option != 1 && option != 2 && option != 3);

    cout << "0) Back" << endl;
    goToInformationMenu();
}

/**
 *  Outputs the top 5 of all UCs with the greatest number of students.
 *  Complexity: O(n).
 */
void Menu::viewUCgreatest() {
    vector<pair<string, int>> ucs = consult.findGreatestUCs();
    cout << "*************************************************************\n"
         << "   ucs with the greatest number of students\n\n";

    for(int i = 0; i < 5; i++) 
        cout << "\t" << ucs[i].first << ": " << ucs[i].second << "\n";

    cout << "\n                                                   0) BACK\n"
         << "************************************************************" << endl;
    goToInformationMenu();
}

/**
 *  Menu for registering a student in a specific UC and class.
 *  Complexity: .
 */
void Menu::menuRegUC() {
    int option;
    string studentCode;
    string ucCode;
    cout << "Student code: ";
    cin >> studentCode;
    cout << "UC code: ";
    cin >> ucCode;
    Student student = consult.findStudent(studentCode);
    if(!student.getStudentCode().empty()) {
        vector<UcClass> classes = consult.listOfClasses(ucCode);

        cout << "\n*************************************************\n"
             << "   choose class\n\n";

        for (int i = 0; i < classes.size(); i++) {
            cout << " " << i+1 << "- " << classes[i].getUcClassCodes().second << " " << classes[i].getStudentsNumber()
                 << "/" << UcClass::capacity << "\n";
        }

        cout << "\n                                         0) BACK"
             << "\n*************************************************\n"
             << "option: ";
        cin >> option;
        if(option == 0)
            registration();

        if(option > 0 && option < classes.size()) {
        data.addRequest(Request(requestType::Add, student, classes[option-1]));
        data.handleRequests();

        }
    } else {
      cout << "Result not found!\n"
           << "0) Back" << endl;
    }
    registration();
}

/**
 *  Menu for remove a student in a specific UC and class.
 *  Complexity: .
 */
void Menu::menuRemoveUC() {
    string studentCode;
    string ucCode;
    cout << "Student code: ";
    cin >> studentCode;
    cout << "UC code: ";
    cin >> ucCode;
    Student student = consult.findStudent(studentCode);
    if(!student.getStudentCode().empty()) {
        UcClass initialUcClass;
        for(const UcClass& ucClass: student.getUcClasses()) {
            if(ucCode == ucClass.getUcClassCodes().first) {
                initialUcClass = ucClass;
            }
        }

        data.addRequest(Request(requestType::Remove, student, initialUcClass));
        data.handleRequests();

    } else {
        cout << "Result not found!\n"
             << "0) Back" << endl;
    }
    registration();
}

/**
 *  Menu for changing a student's class in a given UC.
 *  Complexity: .
 */
void Menu::menuSwitchClass() {
    int option;
    string studentCode;
    string ucCode;
    cout << "Student code: ";
    cin >> studentCode;

    cout << "UC code: ";
    cin >> ucCode;
    Student student = consult.findStudent(studentCode);
    if(!student.getStudentCode().empty()) {
        vector<UcClass> classes = consult.listOfClasses(ucCode);
        UcClass initialUcClass;
        for(const UcClass& ucClass: student.getUcClasses()) {
            if(ucCode == ucClass.getUcClassCodes().first) {
                initialUcClass = ucClass;
            }
        }

        cout << "\n*************************************************\n"
             << "   choose class\n\n";

        for (int i = 0; i < classes.size(); i++) {
            cout << " " << i+1 << "- " << classes[i].getUcClassCodes().second << " " << classes[i].getStudentsNumber()
                 << "/" << UcClass::capacity << "\n";
        }

        cout << "\n                                         0) BACK"
             << "\n*************************************************\n"
             << "option: ";
        cin >> option;
        if(option == 0)
            registration();

        if(option > 0 && option < classes.size()) {
            data.addRequest(Request(requestType::Switch, student, initialUcClass, classes[option - 1]));
            data.handleRequests();

        }
    } else {
        cout << "Result not found!\n"
             << "0) Back" << endl;
    }
    registration();
}

/**
 *  Function to return to the Information menu.
 *  Complexity: O(1).
 */
void Menu::goToInformationMenu() {
    cout << "option: ";
    int option;
    do{
        cin >> option;
        if (option == 0){
            information();
        } else {
            cout << "Invalid option, please try again: ";
        }
    } while(option != 0);
}

/**
 *  Function to return to the Registration menu.
 *  Complexity: O(1).
 */
void Menu::goToRegistrationMenu() {
   cout << "option: ";
   int option;
   do{
       cin >> option;
       if (option == 0){
           registration();
       } else {
           cout << "Invalid option, please try again: ";
       }
   } while(option != 0);
}