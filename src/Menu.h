//
// Created by jpsantos on 25-10-2023.
//

#ifndef AED2324_PRJ1_G56_MENU_H
#define AED2324_PRJ1_G56_MENU_H

#include <iostream>
#include <vector>
#include "Student.h"
#include "Consult.h"

using namespace std;

class Menu {
public:
    Menu(const Dataset &dataset) : consult(dataset), data(dataset) {}
    void main();
private:
    Dataset data;
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
