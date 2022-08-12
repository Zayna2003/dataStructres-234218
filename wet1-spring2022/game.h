//
// Created by Areej on 01/12/2021.
//

#ifndef HW1_GAME_H
#define HW1_GAME_H

#include "Company.h"
#include "Employee.h"
#include "AVL.h"

class Game {
    AVLTree<int, Company*>* CompanysById;
    AVLTree<int, Employee*>* EmployeesById;
    AVLTree<EmployeeLevelKey, Employee*>* EmployeesByLevel;
    int numOfEmployeesInGame;
    int numOfCompanysInGame;
    Employee *highestLevelEmployee;

public:
    Game();

    ~Game();


    void AddCompany(int CompanyId, int Value);

    void AddEmployee( int EmployeeID, int CompanyID, int Salary, int Grade);

    void RemoveCompany( int CompanyID);

    void RemoveEmployee( int EmployeeID);

    void GetCompanyInfo( int CompanyID, int *Value, int *NumEmployees);

    void GetEmployeeInfo( int EmployeeID, int *EmployerID, int *Salary, int *Grade);

    void IncreaseCompanyValue( int CompanyID, int ValueIncrease);

    void PromoteEmployee( int EmployeeID, int SalaryIncrease, int BumpGrade);

    void HireEmployee( int EmployeeID, int NewCompanyID);

    void AcquireCompany( int AcquirerID, int TargetID, double Factor);

    void GetHighestEarner( int CompanyID, int *EmployeeID);

    void GetAllEmployeesBySalary( int CompanyID, int **Employees, int *NumOfEmployees);

    void GetHighestEarnerInEachCompany( int NumOfCompanies, int **Employees);

    void GetNumEmployeesMatching( int CompanyID, int MinEmployeeID, int MaxEmployeeId,
                                       int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees);

    Employee* getHighestLevelEmployee() const;
    void moveEmployeeToCompany(int EmployeeId, int CompanyId);
    //----------------------------------------------- EXCEPTION CLASSES ------------------------------------------------
    class Failure {};
//    class AllocationError {};
//    class InvalidInput {};
};

#endif //HW1_GAME_H
