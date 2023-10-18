//
// Created by Maureen Ah-shu on 15/10/2023.
//

#ifndef AED2324_PRJ1_G56_MENU_H
#define AED2324_PRJ1_G56_MENU_H

#include "student.h"
#include "stdafx.h"

using namespace std;

class Menu {
public:
    void main();
protected:
    void information();
    void registration();
    void records();
    void viewStudentClass();
    void viewStudent();
    void viewClass();
    void viewStudentsCCY();
    void viewNumStudents();
    void viewCYUoccupation();
    void viewUCgreatest();
    void menuRegUC();
    void menuRegClass();
    void menuRemoveUC();
    void menuRemoveClass();
    void menuSwitchUC();
    void menuSwitchClass();
    void goToMenu();
};


#endif //AED2324_PRJ1_G56_MENU_H
