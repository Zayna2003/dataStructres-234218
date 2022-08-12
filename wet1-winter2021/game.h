//
// Created by Areej on 01/12/2021.
//

#ifndef HW1_GAME_H
#define HW1_GAME_H

#include "group.h"
#include "player.h"
#include "AVL.h"

class Game {
    AVLTree<int, Group*>* groupsById;
    AVLTree<int, Player*>* playersById;
    AVLTree<PlayerLevelKey, Player*>* playersByLevel;
    int numOfPlayersInGame;
    int numOfGroupsInGame;
    Player *highestLevelPlayer;

    void setGroupsToNull(AVLTree<int, Player*>::Node * node);
    void setGroupsToNullLvl(AVLTree<PlayerLevelKey, Player*>::Node * node);
    void setGroupsToNullGroups(AVLTree<int, Group*>::Node * node);

public:
    Game();

    ~Game();

    void addGroup(int groupId);

    void addPlayer(int playerId, int groupID, int level);

    void removePlayer(int playerId);

    void movePlayerToGroup(int playerId, int groupId);

    void replaceGroup(int groupID, int replacementID);

    void increaseLevel(int playerId, int levelIncrease);

    void getHighestLevelPlayer(int groupId, int *playerId);

    Player* getHighestLevelPlayer() const;

    void getAllPlayersByLevel(int groupId, int **players, int *numOfPlayers);

    void getGroupsHighestLevel(int numOfGroups, int **Players);

    const AVLTree<int, Group*> &getGroupsById() const;

    //----------------------------------------------- EXCEPTION CLASSES ------------------------------------------------
    class Failure {};
//    class AllocationError {};
//    class InvalidInput {};
};

#endif //HW1_GAME_H
