#ifndef HW2_COMPANY_H
#define HW2_COMPANY_H

#include "AVLRankTree.h"
#include "Employee.h"



class company{
public:
    int CompanyID;
    int numOfEmployees;
    AvlRankTree<employee, int> *companyEmployees;
    AvlRankTree<employeeByLevel, int> *Levels;
    double companyValue;
    int gradesSumSalaryZero;
    int numEmployeesSalaryZero;
    
    company(int iD,int value);
    ~company();
    
    StatusType addEmployeeToGroup(employee& e);

    StatusType removeEmployeeFromGroup(employee& e,int data);

    StatusType sumHighestEmployeeSalaryByCompany(int m,long long int *sum);

    StatusType NumOfPlayersInGroupInBounds(int GroupID,int score,
                                           int lowerLevel,int higherLevel,long double *players);

    friend StatusType MergeGroups(company &a,  company &b);

//    friend StatusType  NumOfPlayersInGroupInBounds(int GroupID,int score,
//                                                    int lowerLevel,int higherLevel,long double *players);

    };

typedef company* Company;

#endif
