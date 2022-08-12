//
// Created by Zayna on 09/06/2022.
//
#include <cmath>
#include "game.h"
#include "Employee.h"
#include "Company.h"
#include "UnionFind.h"
#include "AVLRankTree.h"
// =====================================================================================================================
//                                                    IMPLEMENTATION - START
// =====================================================================================================================
// --------------------------------------------- CONSTRUCTOR -----------------------------------------------------------

Game::Game(int k) {
    numOfCompanies=k;
    totalNumOfPlayers=0;
    playerHashTable = new hashTable();
    allEmployes = new AvlRankTree<employee, int>;
    this->companies = (Company*) malloc(sizeof(Company)*(k+1));
    Levels=new AvlRankTree<employeeByLevel, int>;
    //new Group[k];
    for (int j =1; j <= numOfCompanies; ++j) {
        this->companies[j] = new company(j,j);
    }
    this->groupsUF = new unionFind(numOfCompanies);
    gradesSumSalaryZero=0;
    numEmployeesSalaryZero=0;
}

// --------------------------------------------- DESTRUCTOR -----------------------------------------------------------
Game::~Game() {
    delete this->playerHashTable;
    delete this->allEmployes;
    delete this->Levels;
    for (int j = 1; j <= numOfCompanies; ++j) {
        delete this->companies[j];
    }
    free(this->companies);
    delete this->groupsUF;
}
// --------------------------------------------- MergeGroups FUNCTION ----------------------------------------------------

StatusType Game::AcquireCompany( int companyID1, int companyID2, double factor){

    if(companyID1 >numOfCompanies || companyID2 > numOfCompanies){
        return INVALID_INPUT;
    }
    int root1 = this->groupsUF->Find(companyID1, nullptr);
    int root2 = this->groupsUF->Find(companyID2, nullptr);
    if(root1==root2) return INVALID_INPUT;
    this->groupsUF->Union(companyID1, companyID2, factor);
    int newRoot=this->groupsUF->Find(companyID1, nullptr);
    if(newRoot==root1) {
        MergeGroups(*this->companies[root1], *this->companies[root2]);
    }
    else {
        MergeGroups(*this->companies[root2], *this->companies[root1]);
    }
    return SUCCESS;
}
// --------------------------------------------- AddEmployee FUNCTION ----------------------------------------------------
StatusType Game::AddEmployee( int employeeID, int companyID, int grade){
    if(companyID > (this->numOfCompanies) ){
        return INVALID_INPUT;
    }
    if(this->playerHashTable->Find(employeeID) != -1){
        return FAILURE;
    }
    StatusType res = this->playerHashTable->AddPlayer(employeeID,companyID,0,grade);
    if(res==FAILURE){
        return FAILURE;
    }
    employeeByLevel* ToAdd = new employeeByLevel( grade, 0);

    if(this->Levels->contains(*ToAdd)) {
        this->Levels->insert(this->Levels->root, *ToAdd, 1);
        this->Levels->updateData(this->Levels->root, *ToAdd,grade);
    }
    else this->Levels->insert(this->Levels->root, *ToAdd, 1);

    //AddToCompany
//    int rootCompany = this->groupsUF->Find(companyID, nullptr);
//    employeeByLevel* ToAddInCom = new employeeByLevel( grade, 0);
//    if( this->companies[rootCompany]->Levels->contains(*ToAdd)) {
//        this->companies[rootCompany]->Levels->insert(this->companies[rootCompany]->Levels->root, *ToAddInCom, 1);
//        this->companies[rootCompany]->Levels->updateData(this->companies[rootCompany]->Levels->root, *ToAddInCom,grade);
//    }
//    else  this->companies[rootCompany]->Levels->insert(this->Levels->root, *ToAddInCom, 1);
//    delete ToAddInCom;

    int rootCompany = this->groupsUF->Find(companyID, nullptr);
    Employee new_employee = new employee(employeeID, rootCompany, 0,grade);
    this->companies[rootCompany]->addEmployeeToGroup(*new_employee);

    //company info
    this->companies[companyID]->numOfEmployees++;
    this->companies[companyID]->numEmployeesSalaryZero++;
    this->companies[companyID]->gradesSumSalaryZero+=grade;

    //general info
    this->totalNumOfPlayers++;
    this->numEmployeesSalaryZero++;
    this->gradesSumSalaryZero+=grade;
    delete ToAdd;
    delete new_employee;
    return res;
}

// --------------------------------------------- RemovePlayer FUNCTION -------------------------------------------------
StatusType Game::RemoveEmployee( int employeeID){
//    if(employeeID==355){
//        int i=0;
//    }
    if(this->playerHashTable->Find(employeeID) == -1){
        return FAILURE;
    }

    employee *e = this->playerHashTable->GetPlayer(employeeID);
    if(e== nullptr){
        return FAILURE;
    }

    int rootCompany = this->groupsUF->Find(e->companyId, nullptr);
    employee* empToDlt = new employee(employeeID, e->companyId, e->salary);

    if(e->salary == 0){
        this->companies[rootCompany]->gradesSumSalaryZero-=e->grade;
        this->companies[rootCompany]->numEmployeesSalaryZero--;
        this->gradesSumSalaryZero-=e->grade;
        this->numEmployeesSalaryZero--;
        this->companies[rootCompany]->removeEmployeeFromGroup(*empToDlt,e->grade);
    }
    else if(e->salary> 0){
        this->companies[rootCompany]->removeEmployeeFromGroup(*empToDlt,e->grade);
        this->allEmployes->removeNode(*empToDlt);

    }

    EmployeeByLevel toDeleteLevel= new employeeByLevel(e->grade,e->salary);
    this->Levels->removeNodeForW(*toDeleteLevel,e->grade);
    delete toDeleteLevel;


//    EmployeeByLevel toDeleteFromGroup= new employeeByLevel(e->grade,e->salary);
//    this->companies[rootCompany]->Levels->removeNodeForW(*toDeleteLevel,e->grade);
//    delete toDeleteFromGroup;

    //deletions
    this->playerHashTable->DeletePlayer(employeeID);

    this->companies[rootCompany]->numOfEmployees--;
    this->totalNumOfPlayers--;

    delete empToDlt;
    return SUCCESS;
}
// --------------------------------------------- IncreasePlayerIDLevel FUNCTION ------------------------------------------------
StatusType Game::EmployeeSalaryIncrease(int employeeID,int salaryIncrease) {
    int companyID = this->playerHashTable->GetGroupID(employeeID);
    if(companyID==-1) {
        return FAILURE;
    }

    employee *e = this->playerHashTable->GetPlayer(employeeID);
    int Old_Salary=this->playerHashTable->GetLevel(employeeID);
    int grade=this->playerHashTable->GetScore(employeeID);
    employee * old_e = new employee(employeeID, companyID, Old_Salary,grade);

    this->playerHashTable->SetLevel(employeeID, e->salary+salaryIncrease);
    int rootCompany = this->groupsUF->Find(companyID, nullptr);

    Employee new_employee = new employee(employeeID, companyID, Old_Salary+salaryIncrease,grade);

    if(Old_Salary==0){
        this->allEmployes->insert(allEmployes->root,*new_employee,1);
        this->companies[rootCompany]->removeEmployeeFromGroup(*old_e,old_e->grade);
        this->companies[rootCompany]->addEmployeeToGroup(*new_employee);

        //update grades sum and count for salary = 0
        //in company
        this->companies[rootCompany]->gradesSumSalaryZero-=e->grade;
        this->companies[rootCompany]->numEmployeesSalaryZero--;

        //global
        this->numEmployeesSalaryZero--;
        this->gradesSumSalaryZero-=e->grade;
    }

    if(Old_Salary>0){
        employee* empToDlt = new employee(employeeID, e->companyId, Old_Salary);
        this->companies[rootCompany]->removeEmployeeFromGroup(*empToDlt,e->grade);
        this->allEmployes->removeNode(*empToDlt);
        this->allEmployes->insert(allEmployes->root,*new_employee,1);
        this->companies[rootCompany]->addEmployeeToGroup(*new_employee);
        delete empToDlt;
    }
    employeeByLevel* ToDlt = new employeeByLevel( e->grade, Old_Salary);
    employeeByLevel* ToAdd = new employeeByLevel( e->grade, Old_Salary+salaryIncrease);
    this->Levels->removeNodeForW(*ToDlt,e->grade);

    if(this->Levels->contains(*ToAdd)) {
        this->Levels->insert(this->Levels->root, *ToAdd, 1);
        this->Levels->updateData(this->Levels->root, *ToAdd,grade);
    }
    else {
        this->Levels->insert(this->Levels->root, *ToAdd, 1);
    }

    delete ToDlt;
    delete ToAdd;
    delete old_e;
    delete new_employee;
    return SUCCESS;

}

// --------------------------------------------- ChangePlayerIDScore FUNCTION ------------------------------------------------
StatusType Game::PromoteEmployee( int employeeID, int bumpGrade){
    int companyID = this->playerHashTable->GetGroupID(employeeID);
    if(companyID==-1) return FAILURE;
    if(bumpGrade<0){
        return SUCCESS;
    }

    int salary=this->playerHashTable->GetLevel(employeeID);
    int oldGrade=this->playerHashTable->GetScore(employeeID);

    this->playerHashTable->SetScore(employeeID, oldGrade+bumpGrade);
    int rootCompany = this->groupsUF->Find(companyID, nullptr);
    Employee new_employee=  new employee( employeeID, companyID, salary,oldGrade+bumpGrade);

    if(salary>0){
        employee* empToDlt = new employee(employeeID, companyID,salary);
        this->companies[rootCompany]->removeEmployeeFromGroup(*empToDlt,oldGrade);
        this->allEmployes->removeNode(*empToDlt);
        this->allEmployes->insert(allEmployes->root,*new_employee,1);
        this->companies[rootCompany]->addEmployeeToGroup(*new_employee);
        delete empToDlt;

    }

    if(salary == 0){
        this->gradesSumSalaryZero+=bumpGrade;
        this->companies[rootCompany]->gradesSumSalaryZero+=bumpGrade;

        employeeByLevel* ToUpdate = new employeeByLevel( oldGrade, salary);
        this->companies[rootCompany]->Levels->updateData(this->companies[rootCompany]->Levels->root, *ToUpdate,bumpGrade);

        delete ToUpdate;

    }
    employeeByLevel* ToUpdate = new employeeByLevel( oldGrade, salary);
    this->Levels->updateData(this->Levels->root, *ToUpdate,bumpGrade);

    delete ToUpdate;
    delete new_employee;
    return SUCCESS;
}


// --------------------------------------------- AverageHighestPlayerLevelByGroup FUNCTION ------------------------------------------------
StatusType Game::SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m){

    if(companyID>numOfCompanies){
        return INVALID_INPUT;
    }
    if(companyID==0){
        int size=0;
        this->allEmployes->Size(allEmployes->root,&size);
        if( m > size){
            return FAILURE;
        }
        long long int sum=0;
        StatusType res= this->allEmployes->GetSumHighestRanks(allEmployes->root,m,&sum);
        if(res==SUCCESS){
            printf("SumOfBumpGradeBetweenTopWorkersByGroup: %lld\n", sum);
            return  res;
        }
        return  res;
    }

    if(companyID!=0){
        int size=0;
        int root = this->groupsUF->Find(companyID, nullptr);
        this->companies[root]->companyEmployees->Size(this->companies[root]->companyEmployees->root,&size);
        if( m > size){
            return FAILURE;
        }
        long long int sum=0;
        StatusType res= this->companies[root]->sumHighestEmployeeSalaryByCompany(m,&sum);
        if(res==SUCCESS){
            printf("SumOfBumpGradeBetweenTopWorkersByGroup: %lld\n", sum);
            return  res;
        }
        return  res;
    }
    return SUCCESS;
}


//----------------------------------------------------
StatusType Game::GetNumOfPlayersInBoundsAux(int GroupID, int lowerLevel,int higherLevel,long double *players) {

    EmployeeByLevel LowerPlayer = new employeeByLevel( 0,lowerLevel);
    EmployeeByLevel higherPlayer = new employeeByLevel( 0,higherLevel);
    int high=higherLevel;
    int low=lowerLevel;

    while (!Levels->contains(*LowerPlayer) && (LowerPlayer->salary)<(higherPlayer->salary)){
        (LowerPlayer->salary)++;
    }
    while (!Levels->contains(*higherPlayer) && (higherPlayer->salary)>(LowerPlayer->salary)){
        (higherPlayer->salary)--;
    }
    long double players1=0;
    long double players2=0;
    StatusType Res1 = this->Levels->GetNumOfPlayersInBounds(*LowerPlayer, *higherPlayer, &players2,&players1);


//    players1+=gradesSumSalaryZero;
//    players2+=numEmployeesSalaryZero;

    if(players2 !=0) {
        (*players) = (double)players1 /(double) players2;
    }
    else if(players2==players1==0){
        *players =0;
    }
    else {
        (*players)=-1;
        return FAILURE;}
    delete LowerPlayer;
    delete higherPlayer;

    return Res1;
}
// --------------------------------------------- GetPercentOfPlayersWithScoreInBounds FUNCTION ------------------------------------------------
StatusType Game::AverageBumpGradeBetweenSalaryByGroup(int companyID,int lowerSalary,int higherSalary) {

    if (companyID > numOfCompanies) {
        return INVALID_INPUT;
    }
//    if(companyID==1){
//        int i=0;
//    }
    long double players;
    if (lowerSalary > higherSalary || higherSalary < 0) return FAILURE;
    if (companyID == 0) {
        StatusType res = GetNumOfPlayersInBoundsAux(-1, lowerSalary, higherSalary, &players);
        if (res == SUCCESS) {
              printf("AverageBumpGradeBetweenSalaryByGroup: %.1f\n", (players));
            //printf("AverageBumpGradeBetweenSalaryByGroup: %.1f\n", floor(10 * players + 0.5f) / 10);

            return res;
        }
        return res;
    } else {
        int root = this->groupsUF->Find(companyID, nullptr);
        StatusType res = this->companies[root]->NumOfPlayersInGroupInBounds(root, 0, lowerSalary, higherSalary,
                                                                            &players);
        if (players == -1) return FAILURE;
        if (res == SUCCESS) {
           printf("AverageBumpGradeBetweenSalaryByGroup: %.1f\n", players);
           //printf("AverageBumpGradeBetweenSalaryByGroup: %.1f\n", floor(10 * players + 0.5f) / 10);
            return res;
        }
    }
    return SUCCESS;
}


//--------------------------------------------------------------------------------
StatusType Game::CompanyValue(int companyID){

    if(companyID> numOfCompanies){
        return INVALID_INPUT;
    }
    double dataToReturn;
    int root = this->groupsUF->Find(companyID, &dataToReturn);
    printf("CompanyValue: %.1f\n", dataToReturn);
    return SUCCESS;
}
// =====================================================================================================================
//                                                    IMPLEMENTATION - END
// =====================================================================================================================








