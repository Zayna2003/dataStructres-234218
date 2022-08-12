
#ifndef HW1_Employee_H
#define HW1_Employee_H

//#include "Company.h"

class employee{
public:
    int EmployeeID;
    int companyId;
    int salary;
    int grade;

    employee(int EmployeeID, int companyId, int salary=0, int grade=0,bool scoreChanged= false );
    ~employee() = default;
    employee(employee& Employee)=default;

    int getCompanyId();
    int getEmployeeID();
    int getSalary();
    int getGrade();
    int getID();

    int setGrade(int score);
    int setSalary(int level);

    bool operator==(const employee& p);
    bool operator!=(const employee& p);

    employee& operator=(employee& e);
    friend bool operator<(const employee& p1, const employee& p2);
    friend bool operator>(const employee& p1, const employee& p2);
    friend int operator-( employee& p1,  employee& p2);
};
typedef employee *Employee;


class employeeByLevel {
public:
    int salary;
    int grade;

//    ~EmployeeLevelKey()=default;

    employeeByLevel():  grade(-1),salary(-1) {};
    employeeByLevel( int grade,int salary=0 );
    employeeByLevel(employeeByLevel& p)=default;
    ~employeeByLevel() = default;

    int getGrade();
    int getSalary();

    int setGrade(int score);
    int setSalary(int level);
//    bool operator==(const PlayerLevelKey& key1, const PlayerLevelKey& key2);
//    bool operator<(const PlayerLevelKey& key1, const PlayerLevelKey& key2);
//    bool operator>(const PlayerLevelKey& key1, const PlayerLevelKey& key2);


    bool operator==(const employeeByLevel& p);
    bool operator!=(const employeeByLevel& p);


    friend bool operator<(const employeeByLevel& p1, const employeeByLevel& p2);
    friend bool operator>(const employeeByLevel& p1, const employeeByLevel& p2);
    friend int operator-( employeeByLevel& p1,  employeeByLevel& p2);
};
typedef employeeByLevel *EmployeeByLevel;
#endif //HW1_Employee_H