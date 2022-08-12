#include <cstdio>
#include <cmath>
#include <new>
#include <cassert>
#include "HashTable.h"
#include "Employee.h"


hashTable::hashTable() : playersNum(0), tableSize(START_SIZE), deletedCounter(0), addCounter(0) {
    this->table = new Employee [START_SIZE];

    for (int i = 0; i< this->tableSize; i++) {
        this->table[i] = nullptr;
    }
    this->deletedPlayer = new employee(0,0,0,0);
}

hashTable::~hashTable() {
    for (int i = 0; i< this->tableSize; i++) {
        if (this->table[i] != nullptr && this->table[i] != this->deletedPlayer) {
            delete this->table[i];
        }
    }
    delete deletedPlayer;
    delete[] this->table;
}

hashTable::hashTable(hashTable &ht)
        : playersNum(ht.playersNum), tableSize(ht.tableSize), addCounter(ht.addCounter), deletedPlayer(ht.deletedPlayer) {
    this->table = new Employee [ht.tableSize];
    for (int i = 0; i< this->tableSize; i++) {
        this->table[i] = ht.table[i];
    }
}


void hashTable::CleanTable() {
    Employee  *newTable = new Employee [this->tableSize];
    Employee * oldTable = this->table;
    this->table = newTable;

    for (int i = 0; i < this->tableSize; i++) {
        this->table[i] = nullptr;
    }

    for (int i = 0; i < this->tableSize; i++) {
        if (oldTable[i] != nullptr && oldTable[i] != this->deletedPlayer) {
            this->AddNode(oldTable[i]);
        }
    }
    delete[] oldTable;
}

StatusType hashTable::MakeBiggerTable() {
    int oldSize = this->tableSize;
    this->tableSize = this->tableSize + START_SIZE;
    Employee * newTable = new Employee  [this->tableSize];
    Employee * oldTable = this->table;
    this->table = newTable;


    for (int i = 0; i < this->tableSize; i++) {
        this->table[i] = nullptr;
    }
    for (int i = 0; i < oldSize; i++) {
        if (oldTable[i] != nullptr && oldTable[i] != this->deletedPlayer) {
            this->AddNode(oldTable[i]);
        }
    }
    delete[] oldTable;
    return SUCCESS;
}

// basic funcs of th hashtable

int hashTable::CheckCell(int k) {
    if (this->table[k] == nullptr) {
        return EMPTY;
    } else if (this->table[k] == this->deletedPlayer) {
        return DELETED;
    }
    return FULL;
}

int hashTable::Find(int playerID) {
    for (int i = 0; i < this->tableSize; i++) {
        if (this->table[i] != nullptr && this->table[i] != this->deletedPlayer &&
            this->table[i]->getEmployeeID() == playerID) {
            return i;
        }
    }
    return -1;
}

int hashTable::HashFunc(int playerID, int times) {
    return (this->HFunc(playerID) + times)%(this->tableSize);
}

int hashTable::HFunc(int playerID) {
    double phi = (sqrt(5)-1)/2;
    double a = phi*playerID;
    int b = (int) a;
    double offset = (a - b)*this->tableSize;
    return (int) offset;
}

int hashTable::Step(int playerID) {
    int a = 5;
    while (this->tableSize%a == 0) {
        a = a+2;
    }
    int step = (playerID)%a;
    if (step == 0) {
        step++;
    }
    return step;
}

StatusType hashTable::AddNode(Employee player) {
    assert (player != nullptr);
    if(this->addCounter == this->tableSize) {
        try {
            this->MakeBiggerTable();
        }
        catch (std::bad_alloc& ba) {
            return ALLOCATION_ERROR;
        }
    }
    for (int i = 0; i < this->tableSize; i++) {
        int plc = this->HashFunc(player->getEmployeeID(),i);
        if (this->CheckCell(plc) != FULL) {
            this->table[plc] = player;
            return SUCCESS;
        }
    }
    return FAILURE;
}


StatusType hashTable::AddPlayer(int playerID, int groupID,int Level,int score ) {
    if(playerID <= 0) {
        return INVALID_INPUT;
    } else if(this->Find(playerID) != -1) {
        return FAILURE;
    }


    Employee toAdd;
    try{ toAdd = new employee(playerID, groupID,Level,score);
    }
    catch (std::bad_alloc& ba) {
        return ALLOCATION_ERROR;
    }
    if(this->addCounter == this->tableSize) {
        try{ this->MakeBiggerTable();
        }
        catch (std::bad_alloc& ba) {
            return ALLOCATION_ERROR;
        }
    }

    for (int i = 0; i < this->tableSize; i++) {
        int plc = this->HashFunc(playerID,i);
        if (this->CheckCell(plc) != FULL) {
            this->table[plc] = toAdd;
            (this->addCounter)++;
            return SUCCESS;
        }
    }
    return FAILURE;
}

StatusType hashTable::DeletePlayer(int playerID) {
    int plc = this->Find(playerID);
    if(playerID <= 0) {
        return INVALID_INPUT;
    } else if(plc == -1) {
        return FAILURE;
    }
    this->deletedCounter ++;
    this->addCounter --;
    Employee temp = this->table[plc];
    this->table[plc] = this->deletedPlayer;
    delete temp;
    return SUCCESS;
}

StatusType hashTable::SetLevel(int playerID, int Level) {
    if (Level <= 0 || playerID <= 0) {
        return INVALID_INPUT;
    }
    int plc = this->Find(playerID);
    if (plc == -1) {
        return FAILURE;
    }
    this->table[plc]->setSalary(Level);
    return SUCCESS;
}

StatusType  hashTable::SetScore(int playerID, int score){
    int plc = this->Find(playerID);
    if (plc == -1) {
        return FAILURE;
    }
    this->table[plc]->setGrade(score);
    return SUCCESS;
}
/*
bool hashTable::getScoreFlag(int playerID){
    int plc = this->Find(playerID);
    return this->table[plc]->getScoreChanged();
}
StatusType hashTable::changeScoreFlag(int playerID, bool score) {
    int plc = this->Find(playerID);
    if (plc == -1) {
        return FAILURE;
    }
    this->table[plc]->setScoreChanged(score);
    return SUCCESS;
}*/


int hashTable::GetGroupID(int playerID) {
    int index = this->Find(playerID);
    if (index < 0) {
        return index;
    }
    return this->table[index]->getCompanyId();
}

int hashTable::GetLevel(int playerID) {
    return this->table[this->Find(playerID)]->getSalary();
}

Employee hashTable::GetPlayer(int playerID) {
    int index = this->Find(playerID);
    if (index < 0) {
        return nullptr;
    }
    return this->table[index];
}

int hashTable::GetScore(int playerID) {
    int index = this->Find(playerID);
    if (index < 0) {
        return -1;
    }
    return this->table[index]->getGrade();
}
