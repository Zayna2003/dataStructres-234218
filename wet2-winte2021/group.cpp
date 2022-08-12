//
// Created by Zayna on 01/12/2021.
//

#include "group.h"

group::group(int iD){
     groupID=iD;
     numOfPlayersUnchangedLevel=0;
     PlayersTreeByLevel=new AvlRankTree< playerByLevel ,int>();
     PlayersTreeByScore =new AvlRankTree< playerByScore ,int>();
     Levels =new AvlRankTree< int ,int>();
}
//
group::~group(){
    delete this->PlayersTreeByLevel;
    delete this->PlayersTreeByScore;
    delete this->Levels;
}

group::group(group& G){
    this->groupID=G.groupID;
    this->numOfPlayersUnchangedLevel=G.numOfPlayersUnchangedLevel;
    AvlRankTree< playerByLevel,int>* LevelTree = G.PlayersTreeByLevel;
    AvlRankTree< playerByScore,int>* ScoreTree = G.PlayersTreeByScore;
    AvlRankTree< int,int>* LevelsTree = G.Levels;
    this->PlayersTreeByScore = ScoreTree;
    this->PlayersTreeByLevel = LevelTree;
    this->Levels=LevelsTree;
}

StatusType group::AddPlayerToGroup(int playerID, int Level, int score)  {
    PlayerByLevel P1= new playerByLevel(this->groupID,score,Level);
    PlayerByScore P2=new playerByScore(this->groupID,score,Level);
    AvlRankTree<playerByLevel,int>::Node* Res1 = this->PlayersTreeByLevel->insert(PlayersTreeByLevel->root,*P1,1);
    if(Res1) {
        AvlRankTree<playerByScore,int>::Node* Res2 = this->PlayersTreeByScore->insert(PlayersTreeByScore->root,*P2, 1);
        AvlRankTree<int,int>::Node* Res=this->Levels->insert(Levels->root,Level,1);
        delete P1;
        delete P2;
        if(Res2 && Res ){
        return SUCCESS;
        }
    }
    delete P1;
    delete P2;
    if(Res1 ){
        return SUCCESS;
    }
    return FAILURE;

}

StatusType group::SetPlayerLevel(int playerID, int oldLevel,int score,int newLevel){
    PlayerByLevel P1= new playerByLevel(this->groupID,score,oldLevel);
    PlayerByScore P2=new playerByScore(this->groupID,score,oldLevel);

    this->PlayersTreeByLevel->removeNode(*P1);
    P1->setLevel(newLevel);
    AvlRankTree<playerByLevel,int>::Node* Res1 = this->PlayersTreeByLevel->insert(PlayersTreeByLevel->root,*P1,1);

        this->PlayersTreeByScore->removeNode(*P2);
        P2->setLevel(newLevel);
        AvlRankTree<playerByScore,int>::Node* Res2 = this->PlayersTreeByScore->insert(PlayersTreeByScore->root,*P2, 1);
        this->Levels->removeNode(oldLevel);
        this->Levels->insert(this->Levels->root,newLevel, 1);
        delete P1;
        delete P2;


//    delete P1;
//    delete P2;
    if (Res1){
        return SUCCESS;
    }
    return  FAILURE;
}
void group::RemovePlayer( PlayerByLevel P1,PlayerByScore P2) {
    this->PlayersTreeByLevel->removeNode(*P1);
    this->PlayersTreeByScore->removeNode(*P2);
    this->Levels->removeNode(P1->getLevel());

}
void group::RemoveInGroup( int playerID,int GroupID, int Level, int score){
    PlayerByLevel P1= new playerByLevel(GroupID,score,Level);
    PlayerByScore P2=new playerByScore(GroupID,score,Level);

    this->RemovePlayer( P1, P2);
    delete P1;
    delete P2;
}

StatusType group::ChangePlayerScore(int playerID, int oldScore,int Level,int newScore){
    PlayerByLevel P1= new playerByLevel(this->groupID,oldScore,Level);
    PlayerByScore P2=new playerByScore(this->groupID,oldScore,Level);


    this->PlayersTreeByLevel->removeNode(*P1);
    P1->setScore(newScore);
    AvlRankTree<playerByLevel,int>::Node* Res1 = this->PlayersTreeByLevel->insert(PlayersTreeByLevel->root,*P1,1);

    if(Res1 ) {
        this->PlayersTreeByScore->removeNode(*P2);
        P2->setScore(newScore);
        AvlRankTree<playerByScore,int>::Node* Res2 = this->PlayersTreeByScore->insert(PlayersTreeByScore->root,*P2, 1);
        delete P1;
        delete P2;
        if( Res2){
            return  SUCCESS;
        }
    }
    delete P1;
    delete P2;
    if (Res1){
        return SUCCESS;
    }
    return FAILURE;
    }

StatusType group::sumHighestPlayerLevelByGroup(int m, double *level) const {
    return this->Levels->GetSumHighestRanks(m,level);
}

 StatusType MergeGroups (group& a,  group& b){
     int b_size_level=0;
     int b_size_score=0;
     int b_size_levels=0;
     b.PlayersTreeByLevel->Size(b.PlayersTreeByLevel->root,&b_size_level);
     b.PlayersTreeByScore->Size(b.PlayersTreeByScore->root,&b_size_score);
     b.Levels->Size(b.Levels->root,&b_size_levels);

     AvlRankTree<playerByLevel ,int>::Node** array1 = new AvlRankTree<playerByLevel ,int>::Node*[b_size_level];
     b.PlayersTreeByLevel->GetTreeInOrder(array1);

     AvlRankTree<playerByScore ,int>::Node** array2 = new AvlRankTree<playerByScore ,int>::Node*[b_size_score];
     b.PlayersTreeByScore->GetTreeInOrder(array2);

     AvlRankTree<int ,int>::Node** array3 = new AvlRankTree<int ,int>::Node*[b_size_levels];
     b.Levels->GetTreeInOrder(array3);

     for(int i = 0; i < b_size_level; i++) {
         if(array1[i] !=nullptr) {
             AvlRankTree<playerByLevel, int>::Node *status = a.PlayersTreeByLevel->insert(a.PlayersTreeByLevel->root,
                                                                                          (array1[i]->key),
                                                                                          (array1[i]->data));

         if (!status ) {
             for (int j = 0; j < i ; j++) {
                 a.PlayersTreeByLevel->removeNode((array1[i]->key));
             }
             delete [] array1;
             delete [] array2;
             delete [] array3;
             return FAILURE;
         }
     }}

     for(int i = 0; i < b_size_score; i++) {
         if(array2[i] !=nullptr) {
         AvlRankTree<playerByScore,int>::Node* status = a.PlayersTreeByScore->insert(a.PlayersTreeByScore->root,(array2[i]->key),(array2[i]->data));
         if (!status ) {
             for (int j = 0; j < i ; j++) {
                 a.PlayersTreeByScore->removeNode((array2[i]->key));
             }
             delete [] array1;
             delete [] array2;
             delete [] array3;
             return FAILURE;
         }
     }}

     for(int i = 0; i < b_size_levels; i++) {
         if(array3[i] !=nullptr) {
         AvlRankTree<int,int>::Node* status = a.Levels->insert(a.Levels->root,(array3[i]->key),(array3[i]->data));
         if (!status ) {
             for (int j = 0; j < i ; j++) {
                 a.Levels->removeNode((array3[i]->key));
             }
             delete [] array1;
             delete [] array2;
             delete [] array3;
             return FAILURE;
         }
     }}

     for(int i = 0; i < b_size_level-1; i++) {
         if(array1[i] !=nullptr) {
         b.PlayersTreeByLevel->removeNode((array1[i]->key));
     }}
     for(int i = 0; i < b_size_score-1; i++) {
         if(array2[i] !=nullptr) {
         b.PlayersTreeByScore->removeNode((array2[i]->key));
     }}

     for(int i = 0; i < b_size_levels; i++) {
         if(array3[i] !=nullptr) {
         b.Levels->removeNode((array3[i]->key));
     }}

     delete [] array1;
     delete [] array2;
     delete [] array3;
     return SUCCESS;
}


StatusType group::NumOfPlayersInGroupInBounds(int GroupID,int score,
         int lowerLevel,int higherLevel,double *players){

    PlayerByScore LowerPlayer = new playerByScore(GroupID, score, lowerLevel);
    PlayerByScore higherPlayer = new playerByScore(GroupID, score, higherLevel);
    double players1;
    while (!PlayersTreeByScore->contains(*LowerPlayer) && (LowerPlayer->level)<(higherPlayer->level)){
        (LowerPlayer->level)++;
    }
    while (!PlayersTreeByScore->contains(*higherPlayer) && (higherPlayer->level)>(LowerPlayer->level)){
        (higherPlayer->level)--;
    }
    StatusType Res1 = this->PlayersTreeByScore->GetNumOfPlayersInBounds(*LowerPlayer, *higherPlayer, &players1);
    double players2;
    if (Res1 == SUCCESS) {

        while (!Levels->contains(lowerLevel) && (lowerLevel)<(higherLevel)){
            (lowerLevel)++;
        }
        while (!Levels->contains(higherLevel) && (higherLevel)>(lowerLevel)){
            (higherLevel)--;
        }

        StatusType Res2 = this->Levels->GetNumOfPlayersInBounds(lowerLevel, higherLevel, &players2);
        if(players2 !=0) {
            *players = ((double) (players1)) / ((double) (players2));
        }
        else{
            (*players)=0;
            return  FAILURE;
        }
        *players=100* (*players);
        delete LowerPlayer;
        delete higherPlayer;

        return Res2;
    }
    delete LowerPlayer;
    delete higherPlayer;
    return Res1;
}
