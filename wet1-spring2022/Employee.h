
#ifndef HW1_Employee_H
#define HW1_Employee_H

#include "Company.h"
class Company;

class Employee{
public:
    Company* company;
    int EmployeeID;
    int salary;
    int grade;
//    ~Employee()=default;
    Employee(int EmployeeID) : company(NULL), EmployeeID(EmployeeID), grade(-1) {};
    Employee(Company* company, int EmployeeID, int salary,int grade) :
            company(company),  EmployeeID(EmployeeID),salary(salary), grade(grade) {};
    Company* getCompany() ;
    int getID()const;
    int getSalary() const;
    int getGrade()const;
    void setCompany(Company* newCompany);
    void setID(int ID);
    void setGrade(int newGrade);
};

class EmployeeLevelKey {
public:
    int EmployeeID;
    int salary;
    int grade;
//    ~EmployeeLevelKey()=default;

    EmployeeLevelKey(): EmployeeID(-1),salary(-1), grade(-1) {};
    EmployeeLevelKey(int ID, int salary,int grade): EmployeeID(ID), salary(salary),grade(grade) {};
    EmployeeLevelKey(Employee& p): EmployeeID(p.getID()), salary(p.getSalary()),grade(p.getGrade()) {};

    int getGrade();
    int getID();
    int getSalary();
//    bool operator==(const PlayerLevelKey& key1, const PlayerLevelKey& key2);
//    bool operator<(const PlayerLevelKey& key1, const PlayerLevelKey& key2);
//    bool operator>(const PlayerLevelKey& key1, const PlayerLevelKey& key2);

};
bool operator>(const EmployeeLevelKey &key1, const EmployeeLevelKey &key2);
bool operator<(const EmployeeLevelKey &key1, const EmployeeLevelKey &key2);
bool operator==(const EmployeeLevelKey &key1, const EmployeeLevelKey &key2);
bool operator-(const EmployeeLevelKey &key1, const EmployeeLevelKey &key2);
#endif //HW1_Employee_H
