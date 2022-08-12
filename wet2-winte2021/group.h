//
// Created by Zayna on 01/01/2021.
//

#ifndef HW2_GROUP_H
#define HW2_GROUP_H
#include "AVLRankTree.h"
#include "player.h"



class group {
public:
    int groupID;
    int numOfPlayersUnchangedLevel;
    AvlRankTree<playerByLevel, int> *PlayersTreeByLevel;
    AvlRankTree<playerByScore, int> *PlayersTreeByScore;
    AvlRankTree<int, int> *Levels;
    void RemovePlayer(PlayerByLevel P1,PlayerByScore P2);

    group(int iD);

    group() : groupID(-1), numOfPlayersUnchangedLevel(-1), PlayersTreeByLevel(nullptr)
    ,PlayersTreeByScore(nullptr),Levels(nullptr){};

    group(group &G);

    ~group();

    StatusType AddPlayerToGroup(int playerID, int Level, int score) ;

    StatusType SetPlayerLevel(int playerID, int oldLevel, int score, int newLevel);

    StatusType ChangePlayerScore(int playerID, int oldScore, int Level, int newScore);

    void RemoveInGroup(int playerID,int groupID, int Level, int score);

    StatusType sumHighestPlayerLevelByGroup(int m, double *level) const;

    StatusType NumOfPlayersInGroupInBounds(int GroupID,int score, int lowerLevel,int higherLevel,double *players);

    friend StatusType MergeGroups(group &a,  group &b);

};

typedef group *Group;


#endif //HW2_GROUP_H
