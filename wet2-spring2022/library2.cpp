//
// Created by Zayna on 09/06/2022.
//

/****************************************************************************/
/*                                                                          */
/* This file contains the interface functions                               */
/* you should use for the wet ex 2                                          */
/*                                                                          */
/****************************************************************************/

/****************************************************************************/
/*                                                                          */
/* File Name : library.h                                                   */
/*                                                                          */
/****************************************************************************/

#include "library2.h"
#include "game.h"

void *Init(int k){
    Game* game = new Game(k);
    return (void*)game;
}


StatusType AddEmployee(void *DS, int employeeID, int companyID, int grade){
    if(!DS || employeeID <=0 || companyID <= 0 || grade <0 ) {
        return INVALID_INPUT;
    }
    StatusType res=((Game*)DS)->AddEmployee( employeeID, companyID, grade);
    if(res==INVALID_INPUT)
        return INVALID_INPUT;
    if(res==FAILURE)
        return FAILURE;
    else if (res==ALLOCATION_ERROR)
        return ALLOCATION_ERROR;
    return SUCCESS;
}

StatusType RemoveEmployee(void *DS, int employeeID){
    if(!DS || employeeID <=0 ) {
        return INVALID_INPUT;
    }
    StatusType res=((Game*)DS)->RemoveEmployee(employeeID);
    if(res==INVALID_INPUT)
        return INVALID_INPUT;
    if(res==FAILURE)
        return FAILURE;
    else if (res==ALLOCATION_ERROR)
        return ALLOCATION_ERROR;
    return SUCCESS;
}

StatusType AcquireCompany(void *DS, int companyID1, int companyID2, double factor){
    if(!DS || companyID1 <=0 || companyID2 <= 0 ||factor<=0.0 || companyID2==companyID1){
        return INVALID_INPUT;
    }
    StatusType res=((Game*)DS)->AcquireCompany(companyID1,companyID2,factor);
    if(res==INVALID_INPUT)
        return INVALID_INPUT;
    if(res==FAILURE)
        return FAILURE;
    else if (res==ALLOCATION_ERROR)
        return ALLOCATION_ERROR;
    return SUCCESS;
}


StatusType EmployeeSalaryIncrease(void *DS, int employeeID, int salaryIncrease){
    if(!DS || employeeID <=0 ||salaryIncrease <=0) {
        return INVALID_INPUT;
    }
    StatusType res=((Game*)DS)->EmployeeSalaryIncrease(employeeID,salaryIncrease);
    if(res==INVALID_INPUT)
        return INVALID_INPUT;
    if(res==FAILURE)
        return FAILURE;
    else if (res==ALLOCATION_ERROR)
        return ALLOCATION_ERROR;
    return SUCCESS;
}

StatusType PromoteEmployee(void *DS, int employeeID, int bumpGrade){
    if(!DS || employeeID <=0 ) {
        return INVALID_INPUT;
    }
    StatusType res=((Game*)DS)->PromoteEmployee(employeeID, bumpGrade);
    if(res==INVALID_INPUT)
        return INVALID_INPUT;
    if(res==FAILURE)
        return FAILURE;
    else if (res==ALLOCATION_ERROR)
        return ALLOCATION_ERROR;
    return SUCCESS;
}

StatusType AverageBumpGradeBetweenSalaryByGroup(void *DS, int companyID, int lowerSalary, int higherSalary){
    if(!DS || companyID <0 || lowerSalary<0 || higherSalary<0 || lowerSalary>higherSalary) {
        return INVALID_INPUT;
    }
    StatusType res=((Game*)DS)->AverageBumpGradeBetweenSalaryByGroup(companyID,lowerSalary,higherSalary);
    if(res==INVALID_INPUT)
        return INVALID_INPUT;
    if(res==FAILURE)
        return FAILURE;
    else if (res==ALLOCATION_ERROR)
        return ALLOCATION_ERROR;
    return SUCCESS;
}

StatusType  SumOfBumpGradeBetweenTopWorkersByGroup(void *DS, int companyID, int m){
    if(!DS || companyID <0 ||m <=0 ) {
        return INVALID_INPUT;
    }
    StatusType res=((Game*)DS)->SumOfBumpGradeBetweenTopWorkersByGroup( companyID, m);
    if(res==INVALID_INPUT)
        return INVALID_INPUT;
    if(res==FAILURE)
        return FAILURE;
    else if (res==ALLOCATION_ERROR)
        return ALLOCATION_ERROR;
    return SUCCESS;
}

StatusType CompanyValue(void *DS, int companyID){
    if(!DS || companyID <=0 ) {
        return INVALID_INPUT;
    }
    StatusType res=((Game*)DS)->CompanyValue(companyID);
    if(res==INVALID_INPUT)
        return INVALID_INPUT;
    if(res==FAILURE)
        return FAILURE;
    else if (res==ALLOCATION_ERROR)
        return ALLOCATION_ERROR;
    return SUCCESS;
}


void Quit(void** DS){
    delete (*((Game**)DS));
    *DS=nullptr;
}

