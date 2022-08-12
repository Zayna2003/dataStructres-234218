//
// Created by Areej on 01/12/2021.
//
#include "game.h"
#include "player.h"
#include "UnionFind.h"
#include "AVLRankTree.h"
// =====================================================================================================================
//                                                    IMPLEMENTATION - START
// =====================================================================================================================
// --------------------------------------------- CONSTRUCTOR -----------------------------------------------------------
Game::Game(int k,int s) {
    numOfGroups=k;
    scale=s;
    numOfPlayers=0;
    playerHashTable = new hashTable();
    this->playersByLevel = new AvlRankTree<playerByLevel, int>;
    this->playersByScore = new AvlRankTree<playerByScore, int>;
    this->Levels = new AvlRankTree<int, int>;
    this->groups = (Group*) malloc(sizeof(Group)*(k+1));
            //new Group[k];
    for (int j =1; j <= numOfGroups; ++j) {
        this->groups[j] = new group(j);
    }
    this->groupsUF = new unionFind(numOfGroups,groups);
    for (int i = 1; i <= numOfGroups ; ++i) {
        this->groupsUF->makeSet(i);
    }}
// --------------------------------------------- DESTRUCTOR -----------------------------------------------------------
Game::~Game() {
    delete this->playerHashTable;
    delete this->playersByLevel;
    delete this->playersByScore;
    delete this->Levels;

    for (int j = 1; j <= numOfGroups; ++j) {
        delete this->groups[j];
    }
   // delete[] this->groups;
   free(this->groups);
    delete this->groupsUF;
//free(this->groupsUF);


}
// --------------------------------------------- MergeGroups FUNCTION ----------------------------------------------------

StatusType Game::MergeGroups( int GroupID1, int GroupID2){
    if(GroupID1 >numOfGroups || GroupID2 >numOfGroups){
        return INVALID_INPUT;
    }
    int root1 = this->groupsUF->Find(GroupID1);
    int root2 = this->groupsUF->Find(GroupID2);

    this->groupsUF->Union(root1, root2);
    return SUCCESS;
}
// --------------------------------------------- addPlayer FUNCTION ----------------------------------------------------

StatusType Game::AddPlayer( int PlayerID, int GroupID, int score){
    if(GroupID > (this->numOfGroups) || score>scale){
        return INVALID_INPUT;
    }
    int root= this->groupsUF->Find(GroupID);
    if(this->playerHashTable->Find(PlayerID) != -1){
        return FAILURE;
    }
    PlayerByLevel p_level =new playerByLevel(root,score,0);
    PlayerByScore p_score =new playerByScore(root,score,0);
    StatusType res=this->playerHashTable->AddPlayer(PlayerID,GroupID,score,0);
    if(res==SUCCESS){
        groups[root]->numOfPlayersUnchangedLevel++;
        groupsUF->size_[root]++;
    }

    this->groups[root]->AddPlayerToGroup(PlayerID,0,score);
    this->playersByLevel->insert(playersByLevel->root,*p_level, 1);
    this->playersByScore->insert(playersByScore->root,*p_score, 1);
    this->Levels->insert(Levels->root, 0, 1);

    this->numOfPlayers++;
    delete p_level;
    delete p_score;
    return res;
    return  SUCCESS;
}


// --------------------------------------------- RemovePlayer FUNCTION -------------------------------------------------
StatusType Game::RemovePlayer(int PlayerID){
    int groupID = this->playerHashTable->GetGroupID(PlayerID);
    if(groupID==-1) return FAILURE;
    int playerLevel=this->playerHashTable->GetLevel(PlayerID);
    int score =this->playerHashTable->GetScore(PlayerID);

    if(this->playerHashTable->Find(PlayerID) == -1){
        return FAILURE;
    }
    int root = this->groupsUF->Find(groupID);
    PlayerByLevel p_level =new playerByLevel(root,score,playerLevel);
    PlayerByScore p_score =new playerByScore(root,score,playerLevel);

        this->groups[root]->RemoveInGroup(PlayerID,root,playerLevel,score);
        this->playersByLevel->removeNode(*p_level);
        this->playersByScore->removeNode(*p_score);
        this->Levels->removeNode(playerLevel);


    this->playerHashTable->DeletePlayer(PlayerID);
    this->numOfPlayers--;
    (groupsUF->size_[root])--;
    delete p_level;
    delete p_score;
    return SUCCESS;
}

// --------------------------------------------- IncreasePlayerIDLevel FUNCTION ------------------------------------------------
StatusType Game::IncreasePlayerIDLevel(int playerId, int levelIncrease) {
      int groupID = this->playerHashTable->GetGroupID(playerId);
    if(groupID==-1) return FAILURE;
      int playerLevel=this->playerHashTable->GetLevel(playerId);
      int score =this->playerHashTable->GetScore(playerId);
      int root = this->groupsUF->Find(groupID);

    PlayerByLevel p_level =new playerByLevel(groupID,score,playerLevel);
    PlayerByScore p_score =new playerByScore(groupID,score,playerLevel);
    if(this->playerHashTable->Find(playerId) == -1){
        return FAILURE;
    }

        this->groups[root]->SetPlayerLevel(playerId,playerLevel,score,
                                           playerLevel+levelIncrease);
        this->playersByLevel->removeNode(*p_level);
        p_level->setLevel(playerLevel+levelIncrease);
        this->playersByLevel->insert(playersByLevel->root,*p_level,1);
        this->playersByScore->removeNode(*p_score);
        p_score->setLevel(playerLevel+levelIncrease);
        this->playersByScore->insert(playersByScore->root,*p_score,1);
        this->Levels->removeNode(playerLevel);

        this->Levels->insert(Levels->root, playerLevel + levelIncrease, 1);
    this->playerHashTable->SetLevel(playerId,playerLevel+levelIncrease);
    delete p_level;
    delete p_score;

    return SUCCESS;
}

// --------------------------------------------- ChangePlayerIDScore FUNCTION ------------------------------------------------
StatusType Game::ChangePlayerIDScore( int PlayerID, int NewScore){
    if(NewScore >scale){
        return INVALID_INPUT;
    }

    int root = this->playerHashTable->GetGroupID(PlayerID);
             if(root==-1) return FAILURE;
    int groupID=this->groupsUF->Find(root);

    int playerLevel=this->playerHashTable->GetLevel(PlayerID);
    int score =this->playerHashTable->GetScore(PlayerID);
    PlayerByLevel p_level =new playerByLevel(groupID,score,playerLevel);
    PlayerByScore p_score =new playerByScore(groupID,score,playerLevel);


        this->groups[groupID]->ChangePlayerScore(PlayerID, score,playerLevel, NewScore);
        this->playersByLevel->removeNode(*p_level);
        p_level->setScore(NewScore);
        this->playersByLevel->insert(playersByLevel->root,*p_level,1);
        this->playersByScore->removeNode(*p_score);
        p_score->setScore(NewScore);
        this->playersByScore->insert(playersByScore->root,*p_score,1);

    this->playerHashTable->SetScore(PlayerID,NewScore);
    delete p_level;
    delete p_score;
    return SUCCESS;
}

// --------------------------------------------- AverageHighestPlayerLevelByGroup FUNCTION ------------------------------------------------
StatusType Game::AverageHighestPlayerLevelByGroup( int GroupID, int m, double * level){
    if(GroupID >numOfGroups ){
        return INVALID_INPUT;
    }
    int root =this->groupsUF->Find(GroupID);
    //if(root==-1) root=GroupID;
    if(((m>(groupsUF->size_[root])-1) && (GroupID != 0)) || ((GroupID == 0) && (m>this->numOfPlayers)) ){
        return FAILURE;
    }
    if (m == 0) {
        *level = 0;
        return SUCCESS;
    }

    if (GroupID == 0){
        return this->Levels->GetSumHighestRanks(m, level);
    }
    else {
        int root = this->groupsUF->Find(GroupID);
        return this->groups[root]->sumHighestPlayerLevelByGroup(m, level);
    }
}
//----------------------------------------------------
StatusType Game::GetNumOfPlayersInBoundsAux(int GroupID,
   int score, int lowerLevel,int higherLevel,double *players) {

    PlayerByScore LowerPlayer = new playerByScore(GroupID, score, lowerLevel);
    PlayerByScore higherPlayer = new playerByScore(GroupID, score, higherLevel);
    double players1;
    while (!playersByScore->contains(*LowerPlayer) && (LowerPlayer->level)<(higherPlayer->level)){
        (LowerPlayer->level)++;
    }
    while (!playersByScore->contains(*higherPlayer) && (higherPlayer->level)>(LowerPlayer->level)){
        (higherPlayer->level)--;
    }
    StatusType Res1 = this->playersByScore->GetNumOfPlayersInBounds(*LowerPlayer, *higherPlayer, &players1);

    if (Res1 == SUCCESS) {

        while (!Levels->contains(lowerLevel) && (lowerLevel)<(higherLevel)){
            (lowerLevel)++;
        }
        while (!Levels->contains(higherLevel) && (higherLevel)>(lowerLevel)){
            (higherLevel)--;
        }
        double players2;
        StatusType Res2 = this->Levels->GetNumOfPlayersInBounds(lowerLevel, higherLevel, &players2);

        if(players2 !=0) {
            *players = ((double) (players1)) / ((double) (players2));
        }
        else {
            (*players)=0;
            return FAILURE;}
        *players=100* (*players);
        delete LowerPlayer;
        delete higherPlayer;

        return Res2;
    }
    return Res1;
}
// --------------------------------------------- GetPercentOfPlayersWithScoreInBounds FUNCTION ------------------------------------------------
StatusType Game::GetPercentOfPlayersWithScoreInBounds( int GroupID, int score, int lowerLevel, int higherLevel,
                                                 double * players){
        if(GroupID> numOfGroups){
            return INVALID_INPUT;
        }
    if(lowerLevel>higherLevel  || higherLevel<0  ) return FAILURE;
    if (GroupID == 0){

        return GetNumOfPlayersInBoundsAux( -1,score, lowerLevel,higherLevel,players);
    }
    else {
        int root = this->groupsUF->Find(GroupID);
        return this->groups[root]->NumOfPlayersInGroupInBounds(root,score, lowerLevel,higherLevel,players);
    }

}


// =====================================================================================================================
//                                                    IMPLEMENTATION - END
// =====================================================================================================================








