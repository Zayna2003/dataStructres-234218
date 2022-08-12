
#include "Company.h"

Company::Company(int ID,int Value): CompanyID(ID),value(Value),numOfEmployees(0),   highestLevelEmployee() {
    EmployeeTreeByLevel = new AVLTree< EmployeeLevelKey,  Employee*>(false);
}

void Company::addEmployeeToCompany(Employee *Employee, EmployeeLevelKey key) {
    EmployeeTreeByLevel->root = EmployeeTreeByLevel->insert(EmployeeTreeByLevel->root, key, Employee);
    numOfEmployees++;
}

void Company::removeEmployeeFromCompany(EmployeeLevelKey key) {
    EmployeeTreeByLevel->removeNode(key);
    numOfEmployees--;
}

int Company::getCompanyId() const {
    return CompanyID;
}
int Company::getValue()const{
    return value;
}
AVLTree<EmployeeLevelKey, Employee*> *Company::getEmployeeByLevelTree() {
    return EmployeeTreeByLevel;
}

void Company::setEmployeeByLevelTree(AVLTree<EmployeeLevelKey, Employee*> *tree) {
    EmployeeTreeByLevel = tree;
}

Employee* Company::getHighestLevelEmployeeInCompany()  {
    return highestLevelEmployee;
}

int Company::getNumOfEmployeesInCompany() {
    return numOfEmployees;
}

void Company::setNumOfEmployeesInCompany(int num) {
    numOfEmployees = num;
}

void Company::setHighestLevelEmployeeInCompany(Employee *Employee) {
    highestLevelEmployee = Employee;
}
Company::~Company(){
    delete EmployeeTreeByLevel;
}
;


