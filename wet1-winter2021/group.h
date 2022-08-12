//
// Created by Areej on 01/12/2021.
//

#ifndef HW1_GROUP_H
#define HW1_GROUP_H
#include "AVL.h"
#include "player.h"

class Player;
class PlayerLevelKey;

class Group {
public:
    int groupID;
    int numOfPlayers;
    Group& operator=(const Group& g) = default;
    AVLTree<PlayerLevelKey, Player*>* playerTreeByLevel;
    Player* highestLevelPlayer;

    Group(int ID);
    ~Group();
    void addPlayerToGroup(Player* player, PlayerLevelKey key);
    void removePlayerFromGroup(PlayerLevelKey key);
    int getGroupId() const;
    AVLTree<PlayerLevelKey, Player*>* getPlayerByLevelTree();
    void setPlayerByLevelTree(AVLTree<PlayerLevelKey, Player*>* tree);
    Player* getHighestLevelPlayerInGroup() ;
    int getNumOfPlayersInGroup() ;
    void setNumOfPlayersInGroup(int num);
    void setHighestLevelPlayerInGroup(Player* player);
};

#endif //HW1_GROUP_H
