#ifndef HW1_GAME_H
#define HW1_GAME_H

#include "Company.h"
#include "Employee.h"
#include "AVLRankTree.h"
#include "HashTable.h"
#include "UnionFind.h"



class Game {
    int numOfCompanies;
    UnionFind groupsUF;
    HashTable playerHashTable;
    AvlRankTree<employee, int> *allEmployes;
    AvlRankTree<employeeByLevel, int> *Levels;
    Company* companies;
    int totalNumOfPlayers;
    int gradesSumSalaryZero;
    int numEmployeesSalaryZero;

public:
    Game(int k);

    ~Game();

    StatusType AddEmployee(int employeeID, int companyID, int grade);

    StatusType RemoveEmployee( int employeeID);

    StatusType AcquireCompany( int companyID1, int companyID2, double factor);

    StatusType EmployeeSalaryIncrease(int employeeID,int salaryIncrease);

    StatusType PromoteEmployee( int employeeID, int bumpGrade);

    StatusType AverageBumpGradeBetweenSalaryByGroup(int companyID,int lowerSalary,int higherSalary);

    StatusType SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m);

    StatusType  GetNumOfPlayersInBoundsAux(int GroupID, int lowerLevel,int higherLevel,long double *players);

    StatusType CompanyValue(int companyID);

};

#endif //HW1_GAME_H
