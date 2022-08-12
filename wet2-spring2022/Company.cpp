
#include "Company.h"


company::company(int iD,int Value){
    CompanyID=iD;
    numOfEmployees=0;
    companyValue=Value;
    companyEmployees = new AvlRankTree<employee, int>;
    Levels=new AvlRankTree<employeeByLevel, int>;
    this->numEmployeesSalaryZero=0;
    this->gradesSumSalaryZero=0;

}

company::~company(){
    delete this->companyEmployees;
    delete this->Levels;
}

StatusType company::addEmployeeToGroup(employee& e) {
    if(e.salary>0){
    if(this->companyEmployees->insert(this->companyEmployees->root, e, 1)== nullptr){
        return FAILURE;
    }}

    employeeByLevel* ToAdd = new employeeByLevel( e.grade, e.salary);
    if(this->Levels->contains(*ToAdd)) {
        this->Levels->insert(this->Levels->root, *ToAdd, 1);
        this->Levels->updateData(this->Levels->root, *ToAdd,e.grade);
    }
    else this->Levels->insert(this->Levels->root, *ToAdd, 1);
    delete ToAdd;
    return SUCCESS;
}

StatusType company::removeEmployeeFromGroup(employee &e,int data) {
    if(e.salary>0)  this->companyEmployees->removeNode(e);

    EmployeeByLevel toDeleteLevel= new employeeByLevel(data,e.salary);
    this->Levels->removeNodeForW(*toDeleteLevel,data);
    delete toDeleteLevel;

    return SUCCESS;
}

StatusType company::sumHighestEmployeeSalaryByCompany(int m,long long  int *sum){
    return this->companyEmployees->GetSumHighestRanks(companyEmployees->root,m,sum);
}


StatusType MergeGroups(company& a,  company& b){
    int b_size_level=0;
    int b_size_=0;

    b.companyEmployees->Size(b.companyEmployees->root,&b_size_level);
    b.Levels->Size(b.Levels->root,&b_size_);

    AvlRankTree<employee,int>::Node** array1 = new AvlRankTree<employee ,int>::Node*[b_size_level];
    b.companyEmployees->GetTreeInOrder(array1);

    AvlRankTree<employeeByLevel,int>::Node** array2 = new AvlRankTree<employeeByLevel ,int>::Node*[b_size_];
    b.Levels->GetTreeInOrder(array2);

    for(int i = 0; i < b_size_level; i++) {
        if(array1[i] !=nullptr) {

            AvlRankTree<employee, int>::Node *status = a.companyEmployees->insert(a.companyEmployees->root,
                                                                                            (array1[i]->key),
                                                                                            (array1[i]->data));
            if (!status ) {
                for (int j = 0; j < i ; j++) {
                    a.companyEmployees->removeNode((array1[i]->key));
                }
                delete [] array1;
                delete [] array2;
                return FAILURE;
            }
        }
    }


    AvlRankTree<employeeByLevel, int>::Node *status ;
    for(int i = 0; i < b_size_; i++) {
        if(array2[i] !=nullptr) {
            if(a.Levels->contains((array2[i]->key))) {
                status = a.Levels->insert(a.Levels->root,(array2[i]->key),(array2[i]->data));
                a.Levels->updateData(a.Levels->root, array2[i]->key,(array2[i]->key).getGrade());

            }
            else {
                status = a.Levels->insert(a.Levels->root,(array2[i]->key),(array2[i]->data));
            }

            if (!status ) {
                for (int j = 0; j < i ; j++) {
                    a.Levels->removeNodeForW((array2[i]->key),(array2[i]->data));
                }
                delete [] array1;
                delete [] array2;
                return FAILURE;
            }
        }
    }

/*
    for(int i = 0; i < b_size_level-1; i++) {
        if(array1[i] !=nullptr) {
            b.companyEmployees->removeNode((array1[i]->key));
        }
    }


    for(int i = 0; i < b_size_-1; i++) {
        if(array2[i] !=nullptr) {
            b.Levels->removeNodeForW((array2[i]->key),(array2[i]->data));
        }
    }*/

    delete [] array1;
    delete [] array2;

    return SUCCESS;
}



StatusType company::NumOfPlayersInGroupInBounds(int GroupID,int score,
                                              int lowerLevel,int higherLevel,long double *players){

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
//    if(GroupID==1){
//        int I=0 ;
//    }
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
        delete LowerPlayer;
        delete higherPlayer;
        return FAILURE;
    }
    delete LowerPlayer;
    delete higherPlayer;

    return Res1;
}