

#ifndef HW1_Company_H
#define HW1_Company_H
#include "AVL.h"
#include "Employee.h"

class Employee;
class EmployeeLevelKey;

class Company {
public:
    int CompanyID;
    int value;
    int numOfEmployees;
    Company& operator=(const Company& g) = default;
    AVLTree<EmployeeLevelKey, Employee*>* EmployeeTreeByLevel;
    Employee* highestLevelEmployee;

    Company(int ID,int Value);
    ~Company();
    void addEmployeeToCompany(Employee* Employee, EmployeeLevelKey key);
    void removeEmployeeFromCompany(EmployeeLevelKey key);
    int getCompanyId() const;
    int getValue()const;
    AVLTree<EmployeeLevelKey, Employee*>* getEmployeeByLevelTree();
    void setEmployeeByLevelTree(AVLTree<EmployeeLevelKey, Employee*>* tree);
    Employee* getHighestLevelEmployeeInCompany() ;
    int getNumOfEmployeesInCompany() ;
    void setNumOfEmployeesInCompany(int num);
    void setHighestLevelEmployeeInCompany(Employee* Employee);
};

#endif //HW1_Company_H
