
#include "Menu.h"

/**
 *  Outputs the Main menu.
 *  Complexity: O(1).
 */
void Menu::main() {
    std::cout << "******************************************\n"
         << "*                                        *\n"
         << "*        L.EIC Schedules                 *\n"
         << "*                                        *\n"
         << "*     1) SYSTEM INFORMATION              *\n"
         << "*     2) REGISTRATION                    *\n"
         << "*     0) EXIT                            *\n"
         << "*                                        *\n"
         << "******************************************\n"
         << "Option: " << std::endl;
    int option;
    do{
        std::cin >> option;
        switch(option) {
            case 1: information(); break;
            case 2: registration(); break;
            case 0: exit(0);
            default: std::cout << "Invalid option, please try again: ";
        }
    } while(option != 0 && option != 1 && option != 2 && option != 3);
}

/**
 *  Outputs the Information menu.
 *  Complexity: O(1).
 */
void Menu::information() {
    std::cout << "************************************************************\n"
         << "*  system information                                      *\n"
         << "*                                                          *\n"
         << "*     1) SCHEDULE OF A STUDENT OR CLASS                    *\n"
         << "*     2) STUDENTS WITHIN A CLASS, COURSE OR YEAR           *\n"
         << "*     3) NUMBER OF STUDENTS REGISTERED IN AT LEAST N UCs   *\n"
         << "*     4) CLASS, YEAR OR UC OCCUPATION                      *\n"
         << "*     5) UCs WITH THE GREATEST NUMBER OF STUDENTS          *\n"
         << "*                                                          *\n"
         << "*                                                 0) BACK  *\n"
         << "************************************************************\n"
         << "Option: " << std::endl;
    int option;
    do{
        std::cin >> option;
        switch(option) {
            case 1: viewSchedule(); break;
            case 2: viewStudentsCCY(); break;
            case 3: viewNumStudents(); break;
            case 4: viewCYUoccupation(); break;
            case 5: viewUCgreatest(); break;
            case 0: main(); break;
            default: std::cout << "Invalid option, please try again: ";
        }
    } while(option != 0 && option != 1 && option != 2 && option != 3 && option != 4 && option != 5);
}

/**
 *   Outputs the Registration menu.
 *   Complexity: O(1).
 */
void Menu::registration() {
    std::cout << "******************************************\n"
         << "*  registration                          *\n"
         << "*                                        *\n"
         << "*     1) REGISTRATION IN UC              *\n"
         << "*     2) REMOVE UC                       *\n"
         << "*     3) SWITCH CLASS                    *\n"
         << "*     4) UNDO                            *\n"
         << "*                                        *\n"
         << "*                               0) BACK  *\n"
         << "******************************************\n"
         << "Option: " << std::endl;
    int option;
    do{
        std::cin >> option;
        switch(option) {
            case 1: menuRegUC(); break;
            case 2: menuRemoveUC(); break;
            case 3: menuSwitchClass(); break;
            case 4: data.undoRequest(); main(); break;
            case 0: main(); break;
            default: std::cout << "Invalid option, please try again: ";
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
    std::cout << "Choose one:\n"
         << "1) Student\n"
         << "2) Class\n"
         << "option: ";
    int option;
    do{
        std::cin >> option;
        if (option == 1){
            viewStudentSchedule();
        } else {
            if (option == 2) {
                viewClassSchedule();
            } else {
                std::cout << "Invalid option, please try again: ";
            }
        }
    } while(option != 1 && option != 2);
}

/**
 *  Outputs the user schedule.
 *  Complexity: O(n).
 */
void Menu::viewStudentSchedule() {
    std::cout << "Enter student code: ";
    std::string code;
    std::cin >> code;
    std::list<Schedule> schedule = consult.findStudentSchedule(code);

    if(!schedule.empty()) {
        std::cout << "*****************************************************************************************\n"
             << "   student schedule\n\n";

        for (const auto &s: schedule) {
            std::cout << "Weekday: " << s.weekday << " \tUC: " << s.ucCode << " \tClass:" << s.classCode
                 << " \tType: " << s.type << " \tStart: " << s.start << "\t\tEnd: " << s.end << "\n";
        }

        std::cout << "\n0) BACK\n"
             << "*****************************************************************************************" << std::endl;
    } else {
        std::cout << "\nStudent not found!\n"
             << "0) Back\n";
    }
    goToInformationMenu();
}

/**
 *  Outputs the class schedule.
 *  Complexity: O(n).
 */
void Menu::viewClassSchedule() {
    std::cout << "Enter class code: ";
    std::string code;
    std::cin >> code;
    std::list<Schedule> schedule = consult.findClassSchedule(code);

    if(!schedule.empty()) {
        std::cout << "*****************************************************************************************\n"
             << "   class schedule\n\n";

        for (const auto &s: schedule) {
            std::cout << "Weekday: " << s.weekday << " \tUC: " << s.ucCode << " \tClass:" << s.classCode
                 << " \tType: " << s.type << " \tStart: " << s.start << "\t\tEnd: " << s.end << "\n";
        }

        std::cout << "\n0) BACK\n"
             << "*****************************************************************************************" << std::endl;
        goToInformationMenu();
    } else {
        std::cout << "\nClass not found!\n"
             << "0) Back" << std::endl;
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
    std::set<Student> students;
    int year;
    std::string code;
    std::cout << "Choose one:\n"
         << "1) Class\n"
         << "2) Course\n"
         << "3) Year\n"
         << "option: ";
    int option;
    do{
        std::cin >> option;
        switch(option) {
            case 1: {
                std::cout << "Enter class code: ";
                std::cin >> code;
                students = consult.findClassStudents(code);
            } break;
            case 2: {
                std::cout << "Enter course code: ";
                std::cin >> code;
                students = consult.findUcStudents(code);
            } break;
            case 3: {
                std::cout << "Enter the year: ";
                std::cin >> year;
                students = consult.findYearStudents(year);
            } break;
            default: std::cout << "Invalid option, please try again: ";
        }
    } while(option != 1 && option != 2 && option != 3);

    if(!students.empty()) {
        std::cout << "\n************************************************************\n";
        std::cout << "   list of students\n\n";

        for (const auto &s: students)
            std::cout << "\t" << s.getStudentCode() << " \t" << s.getStudentName() << "\n";

        std::cout << "\n                                                   0) BACK\n"
             << "************************************************************" << std::endl;
    } else {
        std::cout << "\nResult not found!\n"
             << "0) Back" << std::endl;
    }
    goToInformationMenu();
}

/**
 *  Outputs the number of students from a given number of UCs.
 *  Complexity:
 */
void Menu::viewNumStudents() {
    std::cout << "Enter number of UCs: ";
    int ucs;
    std::cin >> ucs;

    int num = 0;
    std::cout << "\nNUMBER OF STUDENTS REGISTERED IN AT LEAST " << ucs << " UCs = " << num << "\n"
         << "0) BACK" << std::endl;
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
    std::string code;
    int year;
    std::cout << "Choose one:\n"
         << "1) Class\n"
         << "2) Year\n"
         << "3) UC\n"
         << "option: ";
    int option;
    do{
        std::cin >> option;
        switch(option) {
            case 1: {
                std::cout << "Enter class code: ";
                std::cin >> code;
                occupation = consult.findClassOccupation(code);
                if(occupation > 0)
                    std::cout << "\nCLASS " << code << ", " << "OCCUPATION = " << occupation << "\n";
                else
                    std::cout << "\nClass not found!\n";
            } break;
            case 2: {
                std::cout << "Enter the year: ";
                std::cin >> year;
                occupation = consult.findYearOccupation(year);
                if(occupation > 0)
                    std::cout << "\nYEAR " << year << ", " << "OCCUPATION = " << occupation << "\n";
                else
                    std::cout << "\nYear not found!\n";
            } break;
            case 3: {
                std::cout << "Enter UC code: ";
                std::cin >> code;
                occupation = consult.findUCOccupation(code);
                if (occupation > 0)
                    std::cout << "\nUC " << code << ", " << "OCCUPATION = " << occupation << "\n";
                else
                    std::cout << "\nUC not found!\n";
            } break;
            default: std::cout << "Invalid option, please try again: ";
        }
    } while(option != 1 && option != 2 && option != 3);

    std::cout << "0) Back" << std::endl;
    goToInformationMenu();
}

/**
 *  Outputs the top 5 of all UCs with the greatest number of students.
 *  Complexity: O(n).
 */
void Menu::viewUCgreatest() {
    std::vector<std::pair<std::string, int>> ucs = consult.findGreatestUCs();
    std::cout << "*************************************************************\n"
         << "   ucs with the greatest number of students\n\n";

    for(int i = 0; i < 5; i++)
        std::cout << "\t" << ucs[i].first << ": " << ucs[i].second << "\n";

    std::cout << "\n                                                   0) BACK\n"
         << "************************************************************" << std::endl;
    goToInformationMenu();
}

/**
 *  Menu for registering a student in a specific UC and class.
 *  Complexity: .
 */
void Menu::menuRegUC() {
    int option;
    std::string studentCode;
    std::string ucCode;
    std::cout << "Student code: ";
    std::cin >> studentCode;
    std::cout << "UC code: ";
    std::cin >> ucCode;
    Student student = consult.findStudent(studentCode);
    if(!student.getStudentCode().empty()) {
        std::vector<UcClass> classes = consult.listOfClasses(ucCode);

        std::cout << "\n*************************************************\n"
             << "   choose class\n\n";

        for (int i = 0; i < classes.size(); i++) {
            std::cout << " " << i+1 << "- " << classes[i].getUcClassCodes().second << " " << classes[i].getStudentsNumber()
                 << "/" << UcClass::capacity << "\n";
        }

        std::cout << "\n                                         0) BACK"
             << "\n*************************************************\n"
             << "option: ";
        std::cin >> option;
        if(option == 0)
            registration();

        if(option > 0 && option < classes.size()) {
        data.addRequest(Request(requestType::Add, student, classes[option-1]));
        data.handleRequests();

        }
    } else {
        std::cout << "Result not found!\n"
           << "0) Back" << std::endl;
    }
    registration();
}

/**
 *  Menu for remove a student in a specific UC and class.
 *  Complexity: .
 */
void Menu::menuRemoveUC() {
    std::string studentCode;
    std::string ucCode;
    std::cout << "Student code: ";
    std::cin >> studentCode;
    std::cout << "UC code: ";
    std::cin >> ucCode;
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
        std::cout << "Result not found!\n"
             << "0) Back" << std::endl;
    }
    registration();
}

/**
 *  Menu for changing a student's class in a given UC.
 *  Complexity: .
 */
void Menu::menuSwitchClass() {
    int option;
    std::string studentCode;
    std::string ucCode;
    std::cout << "Student code: ";
    std::cin >> studentCode;

    std::cout << "UC code: ";
    std::cin >> ucCode;
    Student student = consult.findStudent(studentCode);
    if(!student.getStudentCode().empty()) {
        std::vector<UcClass> classes = consult.listOfClasses(ucCode);
        UcClass initialUcClass;
        for(const UcClass& ucClass: student.getUcClasses()) {
            if(ucCode == ucClass.getUcClassCodes().first) {
                initialUcClass = ucClass;
            }
        }

        std::cout << "\n*************************************************\n"
             << "   choose class\n\n";

        for (int i = 0; i < classes.size(); i++) {
            std::cout << " " << i+1 << "- " << classes[i].getUcClassCodes().second << " " << classes[i].getStudentsNumber()
                 << "/" << UcClass::capacity << "\n";
        }

        std::cout << "\n                                         0) BACK"
             << "\n*************************************************\n"
             << "option: ";
        std::cin >> option;
        if(option == 0)
            registration();

        if(option > 0 && option < classes.size()) {
            data.addRequest(Request(requestType::Switch, student, initialUcClass, classes[option - 1]));
            data.handleRequests();

        }
    } else {
        std::cout << "Result not found!\n"
             << "0) Back" << std::endl;
    }
    registration();
}

/**
 *  Function to return to the Information menu.
 *  Complexity: O(1).
 */
void Menu::goToInformationMenu() {
    std::cout << "option: ";
    int option;
    do{
        std::cin >> option;
        if (option == 0){
            information();
        } else {
            std::cout << "Invalid option, please try again: ";
        }
    } while(option != 0);
}

/**
 *  Function to return to the Registration menu.
 *  Complexity: O(1).
 */
void Menu::goToRegistrationMenu() {
    std::cout << "option: ";
   int option;
   do{
       std::cin >> option;
       if (option == 0){
           registration();
       } else {
           std::cout << "Invalid option, please try again: ";
       }
   } while(option != 0);
}