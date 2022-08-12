//
// Created by Areej on 01/12/2021.
//

#ifndef HW1_GAME_H
#define HW1_GAME_H

#include "group.h"
#include "player.h"
#include "AVLRankTree.h"
#include "HashTable.h"
#include "UnionFind.h"



class Game {
    int numOfGroups;
    UnionFind groupsUF;
    HashTable playerHashTable;
    AvlRankTree<playerByLevel, int> *playersByLevel;
    AvlRankTree<playerByScore, int> *playersByScore;
    AvlRankTree<int, int> *Levels;
    Group *groups;
    int scale;
    int numOfPlayers;
public:
    Game(int k,int scale);

    ~Game();

    StatusType MergeGroups( int GroupID1, int GroupID2);

    StatusType AddPlayer( int PlayerID, int GroupID, int score);

    StatusType RemovePlayer(int PlayerID);

    StatusType IncreasePlayerIDLevel(int PlayerID, int LevelIncrease);

    StatusType ChangePlayerIDScore( int PlayerID, int NewScore);

    StatusType GetPercentOfPlayersWithScoreInBounds( int GroupID, int score, int lowerLevel, int higherLevel,
                                                    double * players);

    StatusType AverageHighestPlayerLevelByGroup( int GroupID, int m, double * level);

    StatusType  GetNumOfPlayersInBoundsAux(int GroupID,int score, int lowerLevel,int higherLevel,double *players);

//    StatusType GetPlayersBound( int GroupID, int score, int m,
//                               int * LowerBoundPlayers, int * HigherBoundPlayers);
};




#endif //HW1_GAME_H
