

#include "Employee.h"
// -------------------- Implementation ----------------------- //


Company *Employee::getCompany()  {
    return company;
}

int Employee::getID()const {
    return EmployeeID;
}

int Employee::getGrade() const {
    return grade;
}
int Employee::getSalary() const {
    return salary;
}


void Employee::setCompany(Company *newGroup) {
    company = newGroup;
}

void Employee::setID(int ID) {
    EmployeeID = ID;
}

void Employee::setGrade(int newLevel) {
    grade =  newLevel;
}

//Comparing operators to get the highest grade//

bool operator==(const EmployeeLevelKey &key1, const EmployeeLevelKey &key2) {
    return (key1.EmployeeID == key2.EmployeeID) && (key1.salary == key2.salary);
}

bool operator<(const EmployeeLevelKey &key1, const EmployeeLevelKey &key2) {
    if (key1.salary == key2.salary) {
        return key1.EmployeeID > key2.EmployeeID;
    }
    return key1.salary < key2.salary;
}
bool operator>(const EmployeeLevelKey &key1, const EmployeeLevelKey &key2) {
//    if (key1.grade == key2.grade) {
//        return key1.playerID < key2.playerID;
//    }
//    return key1.grade > key2.grade;
    return !(key1 == key2) &&  !(key1 < key2);
}

int EmployeeLevelKey::getGrade() {
    return grade;
}

int EmployeeLevelKey::getID() {
    return EmployeeID;
}

int EmployeeLevelKey::getSalary() {
    return salary;
}

bool operator-(const EmployeeLevelKey &key1, const EmployeeLevelKey &key2){
    if(key1>key2) return true;
    return false;
}