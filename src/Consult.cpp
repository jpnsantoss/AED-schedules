/**
*@file Consult.cpp
*Funções que organizam os dados, de modo a consultá-los.
**/

#include "Consult.h"
#include <algorithm>

/**
*@brief Construtor padrão da classe Consult.
**/

Consult::Consult() {}

/**
*@brief Construtor que recebe um objeto Dataset.
*@param dataset - conjunto de dados a ser usado para a consulta.
**/

Consult::Consult(const Dataset &dataset) {
    this->data = dataset;
}

/**
*@brief Mostra o horário de um estudante.
Complexidade: O(n)
*@param code - código do estudante.
*@see Schedule
*@return lista de objetos Schedule representando o horário do estudante.
**/

list<Schedule> Consult::findStudentSchedule(const string& code) {
    list<Schedule> schedule;
    list<UcClass> ucs;

    for(const Student& s : data.getStudents()) {
        if(code == s.getStudentCode()) {
            ucs = s.getUcClasses();
            break;
        }
    }

    for(const auto& u: ucs) {
        for(const Lesson& l: u.getLessons()) {
            Schedule s;
            s.ucCode = u.getUcClassCodes().first;
            s.classCode = u.getUcClassCodes().second;
            s.weekday = l.getWeekday();
            s.start = l.getStart();
            s.end = l.getEnd();
            s.type = l.getType();

            schedule.emplace_back(s);
        }
    }

    return orderSchedule(schedule);
}

/**
*@brief Mostra o horário de uma turma.
Complexidade: O(n)
*@param code - código da turma.
*@see Schedule
*@return lista de objetos Schedule representando o horário da turma.
**/

list<Schedule> Consult::findClassSchedule(string& code) {
    vector<Lesson> result;
    list<Schedule> schedule;

    for (char& c: code)
        c = (char)toupper(c);

    for(const UcClass& uc: data.getUcClasses()) {
        if(code == uc.getUcClassCodes().second) {
            for(const auto& l: uc.getLessons()) {
                Schedule s;
                s.ucCode = uc.getUcClassCodes().first;
                s.classCode = uc.getUcClassCodes().second;
                s.weekday = l.getWeekday();
                s.start = l.getStart();
                s.end = l.getEnd();
                s.type = l.getType();

                schedule.emplace_back(s);
            }
        }
    }

    return orderSchedule(schedule);
}

/**
*@brief Mostra a lista de estudantes de uma turma.
Complexidade: O(n*m)
*@param code - código da turma.
*@see Student
*@return conjunto de objetos Student representando os estudantes da turma.
**/

set<Student> Consult::findClassStudents(string& code) {
    set<Student> result;

    for (char& c: code)
        c = (char)toupper(c);

    for(const Student& s : data.getStudents()) {
        for(const UcClass& uc : s.getUcClasses()) {
            string classCode = uc.getUcClassCodes().second;
            if(code == classCode)
                result.insert(s);
        }
    }

    return result;
}

/**
*@brief Mostra a lista de estudantes inscritos numa UC.
Complexidade: O(n*m)
*@param code - código da UC.
*@see Student
*@return conjunto de objetos Student representando os estudantes inscritos na UC.
**/

set<Student> Consult::findUcStudents(string& code) {
    set<Student> result;

    for (char& c: code)
        c = (char)toupper(c);

    for(const Student& s : data.getStudents()) {
        for(const UcClass& uc : s.getUcClasses()) {
            string ucCode = uc.getUcClassCodes().first;
            if(code == ucCode)
                result.insert(s);
        }
    }
    return result;
}

/**
*@brief Mostra a lista de estudantes de um determinado ano.
Complexidade: O(n*m)
*@param year - ano desejado.
*@see Student
*@return Conjunto de objetos Student representando os estudantes do ano especificado.
**/

set<Student> Consult::findYearStudents(int year) {
    set<Student> result;

    for(const Student& s : data.getStudents()) {
        for(const UcClass& uc : s.getUcClasses()) {
            string str = uc.getUcClassCodes().second.substr(0, 1);
            if(to_string(year) == str)
                result.insert(s);
        }
    }

    return result;
}

/**
*@brief Calcula o número de alunos inscritos em pelo menos N UCs
Complexidade: O(n)
*@param n
*@see Student
*@return O número de alunos inscritos em pelo menos n UCs.
**/

int Consult::studentsRegisteredUcs(int n) {
    int result;

    for(const Student& s : data.getStudents()) {
        if (s.getUcClasses().size() >= n) {
            result++;
        }
    }

    return result;
}

/**
*@brief Indica a ocupação da turma.
Complexidade: O(n*m)
*@param code - código da turma
*@see Student
*@return O número de estudantes matriculados na turma.
**/

unsigned long Consult::findClassOccupation(string& code) {
    set<Student> result;

    for (char& c: code)
        c = (char)toupper(c);

    for(const Student& s : data.getStudents()) {
        for(const UcClass& uc : s.getUcClasses()) {
            string classCode = uc.getUcClassCodes().second;
            if(code == classCode)
                result.insert(s);
        }
    }

    return result.size();
}

/**
*@brief Indica a ocupação de um determinado ano.
Complexidade: O(n*m)
*@param year - ano desejado
*@see Student
*@return O número de estudantes matriculados no ano específico.
**/

unsigned long Consult::findYearOccupation(int year) {
    set<Student> result;

    for(const Student& s : data.getStudents()) {
        for(const UcClass& uc : s.getUcClasses()) {
            string str = uc.getUcClassCodes().second.substr(0, 1);
            if(to_string(year) == str)
                result.insert(s);
        }
    }

    return result.size();
}

/**
*@brief Indica a ocupação de uma determinada UC.
Complexidade: O(n*m)
*@param code - código da turma
*@see Student
*@return O número de estudantes matriculados numa determinada turma.
**/

unsigned long Consult::findUCOccupation(string& code) {
    set<Student> result;

    for (char& c: code)
        c = (char)toupper(c);

    for(const Student& s : data.getStudents()) {
        for(const UcClass& uc : s.getUcClasses()) {
            string ucCode = uc.getUcClassCodes().first;
            if(code == ucCode)
                result.insert(s);
        }
    }

    return result.size();
}

/**
*@brief Indica as UCs com maior ocupação.
Complexidade: O((n*m)+ p*log(p))
*@see Student
*@see UcClass
*@return Um vetor de pares do tipo (UC, ocupação) ordenado por ocupação decrescente.
**/

vector<pair<string, int>> Consult::findGreatestUCs() {
    std::map<std::string, unsigned long> ucOccupations;

    for (const Student& s : data.getStudents()) {
        for (const UcClass& uc : s.getUcClasses()) {
            string ucCode = uc.getUcClassCodes().first;
            ucOccupations[ucCode]++;
        }
    }

    vector<pair<string, int>> result(ucOccupations.begin(), ucOccupations.end());

    sort(result.begin(), result.end(), [](const auto& map1, const auto& map2) {
        return map2.second < map1.second;
    });

    return result;
}

vector<UcClass> Consult::listOfClasses(string &code) {
    set<UcClass> ucClass;

    for (char& c: code)
        c = (char)toupper(c);

    for(const UcClass& uc: data.getUcClasses()) {
        if(code == uc.getUcClassCodes().first)
            ucClass.insert(uc);
    }

    vector<UcClass> classes(ucClass.begin(), ucClass.end());

    return classes;
}

Student * Consult::findStudent(std::string &code) {
    for (char& c: code)
        c = (char)toupper(c);

    for(const Student& s: data.getStudents()) {
        if(code == s.getStudentCode())
            return const_cast<Student *>(&s);
    }
    return nullptr;
}

UcClass * Consult::findUc(std::string &code) {
    for (char& c: code)
        c = (char)toupper(c);

    for(const UcClass& uc: data.getUcClasses()) {
        if(code == uc.getUcClassCodes().first)
            return const_cast<UcClass *>(&uc);
    }
    return nullptr;
}

/**
*@brief Ordena o horário de cada aula, por dia da semana.
Complexidade: O(n*log(n))
*@param schedule - horário a ser ordenado.
*@see Schedule
*@return O horário de aulas ordenado.
**/

list<Schedule> Consult::orderSchedule(list<Schedule> schedule) {
    std::map<std::string, int> weekdaysMap = {
            {"Monday", 1},
            {"Tuesday", 2},
            {"Wednesday", 3},
            {"Thursday", 4},
            {"Friday", 5}
    };

    schedule.sort([&weekdaysMap](const Schedule& obj1, const Schedule& obj2) {
        int weekday1 = weekdaysMap[obj1.weekday];
        int weekday2 = weekdaysMap[obj2.weekday];

        if (weekday1 != weekday2) {
            return weekday1 < weekday2;
        }
        return obj1.start < obj2.start;
    });

    return schedule;
}