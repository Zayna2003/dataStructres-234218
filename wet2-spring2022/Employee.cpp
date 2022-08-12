

#include "Employee.h"
// -------------------- Implementation ----------------------- //

employee::employee(int EmployeeID, int companyId, int salary, int grade,bool scoreChanged):
        EmployeeID(EmployeeID),companyId(companyId),salary(salary),grade(grade)
{}


int employee::getCompanyId()  {
    return companyId;
}

int employee::getID(){
    return EmployeeID;
}

int employee::getEmployeeID() {
    return EmployeeID;
}

int employee::getSalary() {
    return salary;
}

int employee::getGrade() {
    return grade;
}

int employee::setGrade(int s) {
    int old = this->grade;
    this->grade = s;
    return old;
}

int employee::setSalary(int l) {
    int old = this->salary;
    this->salary = l;
    return old;
}

bool employee::operator==(const employee &p) {
    return this->salary == p.salary && this->EmployeeID == p.EmployeeID;
}

bool employee::operator!=(const employee &p) {
    return !(*this == p);
}

bool operator<(const employee& p1, const employee& p2){
    if (p1.salary == p2.salary ){
        return  (p1.EmployeeID < p2.EmployeeID);
    }
    return (p1.salary < p2.salary);
}

bool operator>(const employee& p1, const employee& p2) {
    if (p1.salary == p2.salary ){
        return  (p1.EmployeeID > p2.EmployeeID);
    }
    return (p1.salary > p2.salary);
}

int operator-( employee& p1,  employee& p2){
    if(p1==p2) return 0;
    if(p1>p2)  return 1;
    if(p2>p1)  return -1;
}

employee &employee::operator=(employee &e) {
    this->EmployeeID=e.EmployeeID;
    this->salary=e.salary;
    this->grade=e.grade;
    this->companyId = e.companyId;
    return *this;
}



//---------------------------------------------------------

employeeByLevel::employeeByLevel(  int score, int level):
       grade(score),salary(level){}


int employeeByLevel::getSalary() {
    return salary;
}

int employeeByLevel::getGrade() {
    return grade;
}

int employeeByLevel::setGrade(int score) {
    int old = this->grade;
    this->grade = score;
    return old;
}

int employeeByLevel::setSalary(int level)  {
    int old = this->salary;
    this->salary = level;
    return old;
}


bool employeeByLevel::operator==(const employeeByLevel &p) {
    if (this->salary == p.salary ){
            return true;
        }
    return false;
}


bool employeeByLevel::operator!=(const employeeByLevel &p) {
    return !(*this == p);
}

bool operator<(const employeeByLevel& p1, const employeeByLevel& p2){
    return (p1.salary < p2.salary);
}

bool operator>(const employeeByLevel& p1, const employeeByLevel& p2) {
    return (p1.salary > p2.salary);
}

int operator-( employeeByLevel& p1,  employeeByLevel& p2){
    if(p1==p2) return 0;
    if(p1>p2)  return 1;
    if(p2>p1)  return -1;
}