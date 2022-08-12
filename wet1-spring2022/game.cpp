

#include "game.h"
#include "AVL.h"

// =====================================================================================================================
//                                                    IMPLEMENTATION - START
// =====================================================================================================================
// --------------------------------------------- CONSTRUCTOR -----------------------------------------------------------
Game::Game() :numOfEmployeesInGame(0), numOfCompanysInGame(0), highestLevelEmployee(nullptr) {
    CompanysById=new AVLTree<int, Company*>(true);
     EmployeesById= new AVLTree<int, Employee*>(false);
     EmployeesByLevel=new AVLTree<EmployeeLevelKey, Employee*>(false);

}

// --------------------------------------------- DESTRUCTOR -----------------------------------------------------------
Game::~Game() {
    //CompanysById.treeClear();
    delete CompanysById;
   // EmployeesByLevel.treeClear();
    delete EmployeesByLevel;
    //EmployeesById.treeClear();
    delete EmployeesById;
   // delete highestLevelEmployee;
}

// --------------------------------------------- addPlayer FUNCTION ----------------------------------------------------
void Game::AddEmployee( int EmployeeID, int CompanyID, int Salary, int Grade) {

    Employee *newEmployeeByID = new Employee(nullptr, EmployeeID, Salary,Grade);
    Employee *newEmployeeByLevel = new Employee(nullptr, EmployeeID, Salary,Grade);

    if (!CompanysById->contains(CompanyID)) {
        delete newEmployeeByID;
        delete newEmployeeByLevel;
        throw Failure();
    }
    Company *EmployeeCompany = CompanysById->Find(CompanyID);
    newEmployeeByID->setCompany(EmployeeCompany);
    newEmployeeByLevel->setCompany(EmployeeCompany);

    try {
        EmployeesById->insert(EmployeesById->root, EmployeeID, newEmployeeByID);
        EmployeesByLevel->insert(EmployeesByLevel->root, EmployeeLevelKey(*newEmployeeByLevel), newEmployeeByLevel);
    } catch (AVLTree<int, Employee *>::KeyAlreadyExists &e) {
        delete newEmployeeByID;
        delete newEmployeeByLevel;
        throw Failure();
    }

    Employee *newPlayerInGroup = new Employee(nullptr, EmployeeID, Salary,Grade);
    newPlayerInGroup->company = EmployeeCompany;

    (EmployeeCompany->EmployeeTreeByLevel)->insert((EmployeeCompany->EmployeeTreeByLevel)->root,
                                                   EmployeeLevelKey(EmployeeID, Salary,Grade),
                                             newPlayerInGroup);
    (EmployeeCompany->numOfEmployees)++;
    if (EmployeeCompany->highestLevelEmployee != nullptr) {
        if (EmployeeLevelKey(*(EmployeeCompany->getHighestLevelEmployeeInCompany())) < EmployeeLevelKey(*newPlayerInGroup)) {
            EmployeeCompany->highestLevelEmployee = newPlayerInGroup;
        }
    } else {
        EmployeeCompany->highestLevelEmployee = newPlayerInGroup;
    }
    //update the highest level player
    if (highestLevelEmployee != nullptr) {
        if (EmployeeLevelKey(*getHighestLevelEmployee()) < EmployeeLevelKey(*newEmployeeByLevel)) {
            highestLevelEmployee = newEmployeeByLevel;
        }
    } else {
        highestLevelEmployee = newEmployeeByLevel;
    }
    numOfEmployeesInGame++;
}

// --------------------------------------------- addGroup FUNCTION -----------------------------------------------------
void Game::AddCompany(int CompanyId, int Value) {
    auto *newGroup = new Company(CompanyId,Value);
    try {
        CompanysById->insert(CompanysById->root, CompanyId, newGroup);
        // numOfGroupsInGame++;
    } catch (AVLTree<int, Company *>::KeyAlreadyExists &e) {
        delete newGroup;
        throw Failure();

    }
    numOfCompanysInGame++;
}

// --------------------------------------------- removePlayer FUNCTION -------------------------------------------------
void Game::RemoveEmployee( int EmployeeID) {
    Employee *EmployeeToRemove;
    // remove from players by id tree

    if (!EmployeesById->contains(EmployeeID)) {
        throw Failure();
    }
    EmployeeToRemove = EmployeesById->Find(EmployeeID);
    // remove from company
    Company *toRemoveFromGroup = EmployeeToRemove->getCompany();
    if (toRemoveFromGroup) {
        toRemoveFromGroup->removeEmployeeFromCompany(EmployeeLevelKey(*EmployeeToRemove));
        if (toRemoveFromGroup->getEmployeeByLevelTree()->root) {
            toRemoveFromGroup->setHighestLevelEmployeeInCompany(toRemoveFromGroup->getEmployeeByLevelTree()->GetMax()->data);
        } else {
            toRemoveFromGroup->setHighestLevelEmployeeInCompany(nullptr);
        }
    }
    EmployeesByLevel->removeNode(EmployeeLevelKey(*EmployeeToRemove));
    EmployeesById->removeNode(EmployeeID);

    //delete EmployeeToRemove;
    if ((EmployeesByLevel->root)) {
        highestLevelEmployee = EmployeesByLevel->GetMax()->data;
    } else {
        highestLevelEmployee = nullptr;
    }
    numOfEmployeesInGame--;
   // (toRemoveFromGroup->numOfPlayers)--;
}

void Game::RemoveCompany( int CompanyID){
    Company *CompanyToRemove;
    if (!CompanysById->contains(CompanyID)) {
        throw Failure();
    }
    CompanyToRemove=CompanysById->Find(CompanyID);
    if (CompanyToRemove->getNumOfEmployeesInCompany()>0){
        throw Failure();
    }
    CompanysById->removeNode(CompanyID);
}


void Game::GetCompanyInfo( int CompanyID, int *Value, int *NumEmployees){
    Company *CompanyInfo;
    if (!CompanysById->contains(CompanyID)) {
        throw Failure();
    }
    CompanyInfo=CompanysById->Find(CompanyID);
    *Value=CompanyInfo->getValue();
    *NumEmployees=CompanyInfo->getNumOfEmployeesInCompany();
}

void Game::GetEmployeeInfo( int EmployeeID, int *EmployerID, int *Salary, int *Grade){
    Employee *EmployeeInfo;
    if (!EmployeesById->contains(EmployeeID)) {
        throw Failure();
    }
    EmployeeInfo=EmployeesById->Find(EmployeeID);
    *EmployerID=EmployeeInfo->getCompany()->getCompanyId();
    *Salary=EmployeeInfo->getSalary();
    *Grade=EmployeeInfo->getGrade();
}

void Game::IncreaseCompanyValue( int CompanyID, int ValueIncrease){
    Company *CompanyInfo;
    if (!CompanysById->contains(CompanyID)) {
        throw Failure();
    }
    CompanyInfo=CompanysById->Find(CompanyID);
    CompanyInfo->value+=ValueIncrease;
}


void Game::PromoteEmployee( int EmployeeID, int SalaryIncrease, int BumpGrade){
    Employee *EmployeeInfo;
    if (!EmployeesById->contains(EmployeeID)) {
        throw Failure();
    }
    EmployeeInfo=EmployeesById->Find(EmployeeID);
    Company * c=EmployeeInfo->getCompany();
    int cc=c->getCompanyId();
    int s=(EmployeeInfo->getSalary())+SalaryIncrease;
    int g=EmployeeInfo->getGrade();
    if(BumpGrade >0) g++;

    RemoveEmployee(EmployeeID);
    AddEmployee(EmployeeID,cc,s,g);
}

void Game::HireEmployee( int EmployeeID, int NewCompanyID){
    Employee *EmployeeInfo;
    if (!EmployeesById->contains(EmployeeID)) {
        throw Failure();
    }
    if (!CompanysById->contains(NewCompanyID)) {
        throw Failure();
    }
    EmployeeInfo=EmployeesById->Find(EmployeeID);
    if(EmployeeInfo->getCompany()->getCompanyId()==NewCompanyID){
        throw Failure();
    }
    int s=EmployeeInfo->getSalary();
    int g=EmployeeInfo->getGrade();
    RemoveEmployee(EmployeeID);
    AddEmployee(EmployeeID,NewCompanyID,s,g);

}

//-------------------------------------------------------------------------------------------
void Game::moveEmployeeToCompany(int EmployeeId, int CompanyId) {
    Employee *employee;
    Company *company;

    employee=EmployeesById->Find(EmployeeId);
    company=CompanysById->Find(CompanyId);

    company->addEmployeeToCompany(employee, EmployeeLevelKey(*employee));
    if (company->getHighestLevelEmployeeInCompany()) {
        if (EmployeeLevelKey(*company->getHighestLevelEmployeeInCompany())
            < EmployeeLevelKey(*employee)) {
            company->setHighestLevelEmployeeInCompany(employee);
        }
    } else {
        company->setHighestLevelEmployeeInCompany(employee);
    }
    if (employee->getCompany()) {
        Company *oldGroup = employee->getCompany();
        oldGroup->removeEmployeeFromCompany(EmployeeLevelKey(*employee));
        if (oldGroup->getEmployeeByLevelTree()->root) {
            oldGroup->setHighestLevelEmployeeInCompany
                    (oldGroup->getEmployeeByLevelTree()->GetMax()->data);

        } else {
            oldGroup->setHighestLevelEmployeeInCompany(nullptr);
        }
    }
    employee->setCompany(company);
}
//--------------------------------------------------------------------------------------------
void Game::AcquireCompany( int AcquirerID, int TargetID, double Factor) {
    Company *AcquirerCompany;
    Company *TargetCompany;

    if (!CompanysById->contains(AcquirerID) || !CompanysById->contains(TargetID)) {
        throw Failure();
    }

    AcquirerCompany = CompanysById->Find(AcquirerID);
    TargetCompany = CompanysById->Find(TargetID);

    double value = ((double) (AcquirerCompany->getValue()) / (double) (TargetCompany->getValue()));
    if (value < 10) throw Failure();


    int NumOfEmployeesInCompany = TargetCompany->getNumOfEmployeesInCompany();
    Employee **EmployeesArray = (Employee **) malloc(sizeof(Employee *) * NumOfEmployeesInCompany);

    TargetCompany->getEmployeeByLevelTree()->printintwo(EmployeesArray, &NumOfEmployeesInCompany);

    for (int i = 0; i < NumOfEmployeesInCompany; i++) {
        // movePlayerToGroup(playersArray[i].getID(), replacementID);
        int tempID = EmployeesArray[i]->getID(), tempLvl = EmployeesArray[i]->getSalary(),
        tempGrade=EmployeesArray[i]->getGrade();
        RemoveEmployee(EmployeesArray[i]->getID());
        AddEmployee(tempID, AcquirerID, tempLvl,tempGrade);
    }
    free(EmployeesArray);
    AcquirerCompany->value=(Factor)*((AcquirerCompany->value+TargetCompany->value));
    CompanysById->removeNode(TargetID);

}


void Game::GetHighestEarner( int CompanyID, int *EmployeeID){
    if (CompanyID < 0) {
        if(numOfEmployeesInGame<=0) throw Failure();
        if (!highestLevelEmployee) {
            *EmployeeID = -1;
            return;
        } else {
            *EmployeeID = highestLevelEmployee->getID();
            return;
        }
    } else {
        Company *company;
        if (!CompanysById->contains(CompanyID)) {
            throw Failure();
        }
        company = CompanysById->Find(CompanyID);
        if(company->getNumOfEmployeesInCompany() <=0) throw Failure();
        if (!company->getHighestLevelEmployeeInCompany()) {
            *EmployeeID = -1;
            return;
        }
        *EmployeeID = company->getHighestLevelEmployeeInCompany()->getID();
    }
}


void Game::GetAllEmployeesBySalary( int CompanyID, int **Employees, int *NumOfEmployees){
    Company *company;
    if (CompanyID < 0) {
        *NumOfEmployees = numOfEmployeesInGame;
        if (numOfEmployeesInGame == 0) {
          //  *Employees = nullptr;
           // return;
           throw Failure();
        } else {
            Employee *EmployeesArray = (Employee *) malloc(numOfEmployeesInGame * sizeof(Employee));
            EmployeesByLevel->printin(EmployeesArray, NumOfEmployees);

            *Employees = (int *) malloc((*NumOfEmployees) * sizeof(int));
            for (int i = 0; i < *NumOfEmployees; i++) {
                (*Employees)[i] = EmployeesArray[(*NumOfEmployees)-1-i].getID();
            }
            free(EmployeesArray);
            return;
        }
    }

    if (CompanyID > 0) {
        if (!CompanysById->contains(CompanyID)) {
            throw Failure();
        }
        company=CompanysById->Find(CompanyID);
        *NumOfEmployees = company->getNumOfEmployeesInCompany();
        if (company->getNumOfEmployeesInCompany() == 0) {
           // *Employees = nullptr;
        //    return;
        throw Failure();
        }

        Employee *playersArray = (Employee *) malloc(sizeof(Employee) * (*NumOfEmployees));
        (company->EmployeeTreeByLevel)->printin(playersArray, NumOfEmployees);

        *Employees = (int *) malloc((*NumOfEmployees) * sizeof(int));
        for (int i = 0; i < *NumOfEmployees; i++) {
            (*Employees)[i] = playersArray[(*NumOfEmployees)-1-i].getID();
        }
        free(playersArray);
        return;
    }
}

Employee *Game:: getHighestLevelEmployee() const {
    return highestLevelEmployee;
}

void Game::GetHighestEarnerInEachCompany( int NumOfCompanies, int **Employees){
    int minNumOfPlayers = 1;
    int group_i = 0;
    int numOfPlayersInGame2 = 0;// (int)malloc( sizeof(int));
    if(numOfCompanysInGame<NumOfCompanies){
        throw Failure();
    }
    *Employees = (int *) malloc((NumOfCompanies) * sizeof(int));
    Company *groupArray = (Company *) malloc(sizeof(Company) * numOfCompanysInGame);

    //   groupArray = new Group* [*numOfPlayersInGame];
    // int** groupArray;
    CompanysById->printin(groupArray, &numOfPlayersInGame2);

    for (int i = 0; i < numOfPlayersInGame2; i++) {
        int numOfPLayersInGroup = groupArray[i].getNumOfEmployeesInCompany();
        if (numOfPLayersInGroup < minNumOfPlayers) {
            continue;
        }
        if (group_i < NumOfCompanies) {
            int jhjg = (*(groupArray[i].getHighestLevelEmployeeInCompany())).getID();
            (*Employees)[group_i++] = jhjg;
        } else {
            break;
        }
        // group_i++;
    }
    free(groupArray);
    if(group_i<NumOfCompanies){
        free(*Employees);
        *Employees =NULL;
        throw Failure();
    }

}

void Game::GetNumEmployeesMatching( int CompanyID, int MinEmployeeID, int MaxEmployeeId,
                              int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees){
    *TotalNumOfEmployees=0;
    *NumOfEmployees=0;
    Company *company;
    if (CompanyID < 0) {
        if (numOfEmployeesInGame == 0) {
            throw Failure();
        }
        else {
            Employee *EmployeesArray = (Employee *) malloc(numOfEmployeesInGame * sizeof(Employee));
            int num=0;
            EmployeesByLevel->printin(EmployeesArray,&num );

            int* Employees= (int*)malloc(numOfEmployeesInGame * sizeof(int));
            int s=0,g=0;
            //*Employees = (int *) malloc((*NumOfEmployees) * sizeof(int));
            for (int i = 0; i < numOfEmployeesInGame; i++) {
                (Employees)[i] = EmployeesArray[(numOfEmployeesInGame)-1-i].getID();
                if((Employees)[i] >=MinEmployeeID && (Employees)[i]<=MaxEmployeeId){
                (*TotalNumOfEmployees)++;
                s=EmployeesArray[(numOfEmployeesInGame)-1-i].getSalary();
                g=EmployeesArray[(numOfEmployeesInGame)-1-i].getGrade();
                if(s>=MinSalary && g>=MinGrade){
                    (*NumOfEmployees)++;}}
            }
            free(EmployeesArray);
            free(Employees);
            return;
        }
    }

    if (CompanyID > 0) {
        if (!CompanysById->contains(CompanyID)) {
            throw Failure();
        }
        company=CompanysById->Find(CompanyID);
        if (company->getNumOfEmployeesInCompany() == 0) {
            throw Failure();
        }
        int NumOfEm=company->getNumOfEmployeesInCompany();
        Employee *EmployeesArray = (Employee *) malloc(sizeof(Employee) * (NumOfEm));
        int num=0;
        (company->EmployeeTreeByLevel)->printin(EmployeesArray, &num);

       // *Employees = (int *) malloc((*NumOfEmployees) * sizeof(int));
        int* Employees= (int*)malloc(NumOfEm * sizeof(int));
        int s=0,g=0;

        for (int i = 0; i < NumOfEm; i++) {
            (Employees)[i] = EmployeesArray[(NumOfEm)-1-i].getID();
            if((Employees)[i] >=MinEmployeeID && (Employees)[i]<=MaxEmployeeId){
                (*TotalNumOfEmployees)++;
            s=EmployeesArray[(NumOfEm)-1-i].getSalary();
            g=EmployeesArray[(NumOfEm)-1-i].getGrade();
            if(s >=MinSalary && g>=MinGrade){
                (*NumOfEmployees)++;}  }      }
        free(EmployeesArray);
        free(Employees);
        return;
    }
}
















