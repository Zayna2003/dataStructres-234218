
#include "library1.h"
#include "game.h"


void *Init(){
    Game* game = new Game();
    return (void*)game;
}

StatusType AddCompany(void *DS, int CompanyID, int Value){
    if (!DS || CompanyID <= 0 ||Value <=0) {
        return INVALID_INPUT;
    }
    try {
        ((Game*)DS)->AddCompany(CompanyID,Value);
    }catch (Game::Failure& error){
        return FAILURE;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Salary, int Grade) {
    if(!DS || EmployeeID <=0 || CompanyID <= 0 || Salary <= 0 || Grade<0){
        return INVALID_INPUT;
    }
    try{
        ((Game*)DS)->AddEmployee(EmployeeID, CompanyID, Salary,Grade);
    }catch (Game::Failure& e){
        return FAILURE;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType RemoveEmployee( void *DS,int EmployeeID){
    if (!DS || EmployeeID <= 0) {
        return INVALID_INPUT;
    }
    try {
        ((Game*)DS)->RemoveEmployee(EmployeeID);
    }catch (Game::Failure& error){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType RemoveCompany(void *DS, int CompanyID){
    if (!DS || CompanyID <= 0 ) {
        return INVALID_INPUT;
    }
    try {
        ((Game*)DS)->RemoveCompany(CompanyID);
    }catch (Game::Failure& error){
        return FAILURE;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType GetCompanyInfo(void *DS, int CompanyID, int *Value, int *NumEmployees){
    if (!DS || CompanyID <= 0 || !Value || !NumEmployees) {
        return INVALID_INPUT;
    }
    try {
        ((Game*)DS)->GetCompanyInfo(CompanyID,Value,NumEmployees);
    }catch (Game::Failure& error){
        return FAILURE;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType GetEmployeeInfo(void *DS, int EmployeeID, int *EmployerID, int *Salary, int *Grade){
    if (!DS || EmployeeID <= 0 || !EmployerID || !Salary ||!Grade) {
        return INVALID_INPUT;
    }
    try {
        ((Game*)DS)->GetEmployeeInfo(EmployeeID,EmployerID,Salary,Grade);
    }catch (Game::Failure& error){
        return FAILURE;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType IncreaseCompanyValue(void *DS, int CompanyID, int ValueIncrease){
    if(!DS || CompanyID <=0 || ValueIncrease <= 0 ){
        return INVALID_INPUT;
    }
    try{
        ((Game*)DS)->IncreaseCompanyValue(CompanyID, ValueIncrease);
    }catch (Game::Failure& e){
        return FAILURE;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType PromoteEmployee(void *DS, int EmployeeID, int SalaryIncrease, int BumpGrade){
    if(!DS || EmployeeID <=0 || SalaryIncrease <= 0 ){
        return INVALID_INPUT;
    }
    try{
        ((Game*)DS)->PromoteEmployee(EmployeeID, SalaryIncrease,BumpGrade);
    }catch (Game::Failure& e){
        return FAILURE;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType HireEmployee(void *DS, int EmployeeID, int NewCompanyID){
    if(!DS || EmployeeID <=0 || NewCompanyID <= 0 ){
        return INVALID_INPUT;
    }
    try{
        ((Game*)DS)->HireEmployee(EmployeeID, NewCompanyID);
    }catch (Game::Failure& e){
        return FAILURE;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType AcquireCompany(void *DS, int AcquirerID, int TargetID, double Factor){
    if(!DS || AcquirerID <=0 || TargetID <= 0 || TargetID==AcquirerID || Factor <1.00){
        return INVALID_INPUT;
    }
    try{
        ((Game*)DS)->AcquireCompany( AcquirerID,  TargetID,  Factor);
    }catch (Game::Failure& e){
        return FAILURE;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}


StatusType GetHighestEarner(void *DS, int CompanyID, int *EmployeeID){
    if (!DS || CompanyID == 0 || !EmployeeID) {
        return INVALID_INPUT;
    }
    try {
        ((Game*)DS)->GetHighestEarner(CompanyID, EmployeeID);
    }catch (Game::Failure& error){
        return FAILURE;
    }
    return SUCCESS;
}


StatusType GetAllEmployeesBySalary(void *DS, int CompanyID, int **Employees, int *NumOfEmployees){
    if(!DS || CompanyID == 0 || !Employees || !NumOfEmployees){
        return INVALID_INPUT;
    }
    try{
        ((Game*)DS)->GetAllEmployeesBySalary(CompanyID, Employees, NumOfEmployees);
    }catch (Game::Failure& e){
        return FAILURE;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType GetHighestEarnerInEachCompany(void *DS, int NumOfCompanies, int **Employees){
    if (!DS || NumOfCompanies <1 || !Employees) {
        return INVALID_INPUT;
    }
    try{
        ((Game*)DS)->GetHighestEarnerInEachCompany(NumOfCompanies, Employees);
    }catch (Game::Failure& e){
        return FAILURE;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType GetNumEmployeesMatching(void *DS, int CompanyID, int MinEmployeeID, int MaxEmployeeId,
                                   int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees){


    if (!DS || CompanyID ==0 || !TotalNumOfEmployees || !NumOfEmployees ||MinEmployeeID<0 ||
            MaxEmployeeId<0 ||MinSalary<0 ||MinGrade<0 || MaxEmployeeId<MinEmployeeID ) {
                  return INVALID_INPUT;
    }
    try{
        ((Game*)DS)->GetNumEmployeesMatching(CompanyID, MinEmployeeID,MaxEmployeeId,MinSalary,MinGrade,
                                             TotalNumOfEmployees, NumOfEmployees  );
    }catch (Game::Failure& e){
        return FAILURE;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

void Quit(void** DS) {
    delete (*((Game**)DS));
    *DS=nullptr;
}
