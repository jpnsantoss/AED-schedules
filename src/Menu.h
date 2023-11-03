
#ifndef AED2324_PRJ1_G56_MENU_H
#define AED2324_PRJ1_G56_MENU_H

#include <iostream>
#include <vector>
#include "Student.h"
#include "Consult.h"

class Menu {
public:
    Menu(Dataset& data) : data(data), consult(Consult(data)) {}
    void main();
private:
    Dataset& data;
    Consult consult;
    void information();
    void registration();
    void viewSchedule();
    void viewStudentSchedule();
    void viewClassSchedule();
    void viewStudentsCCY();
    void viewNumStudents();
    void viewCYUoccupation();
    void viewUCgreatest();
    void menuRegUC();
    void menuRemoveUC();
    void menuSwitchClass();
    void undo();
    void goToInformationMenu();
    void goToRegistrationMenu();
};



#endif //AED2324_PRJ1_G56_MENU_H
