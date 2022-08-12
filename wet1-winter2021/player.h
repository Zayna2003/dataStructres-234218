//
// Created by Areej on 01/12/2021.
//
#ifndef HW1_PLAYER_H
#define HW1_PLAYER_H

#include "group.h"
class Group;

class Player {
public:
    Group* group;
    int playerID;
    int level;
    Player(int playerID) : group(NULL), playerID(playerID), level(-1) {};
    Player(Group* group, int playerID, int level) :
    group(group), playerID(playerID), level(level) {};
    Group* getGroup() ;
    int getID();
    int getLevel() const;
    void setGroup(Group* newGroup);
    void setID(int ID);
    void setLevel(int newLevel);
};

class PlayerLevelKey {
public:
    int playerID;
    int level;

    PlayerLevelKey(): playerID(-1), level(-1) {}; // Constructor#1: empty key
    PlayerLevelKey(int ID, int level): playerID(ID), level(level) {}; // Constructor#2: init with player's id and level
    PlayerLevelKey(Player& p): playerID(p.getID()), level(p.getLevel()) {}; //Constructor#3: init with player

    int getLevel();
//    bool operator==(const PlayerLevelKey& key1, const PlayerLevelKey& key2);
//    bool operator<(const PlayerLevelKey& key1, const PlayerLevelKey& key2);
//    bool operator>(const PlayerLevelKey& key1, const PlayerLevelKey& key2);

};
bool operator>(const PlayerLevelKey &key1, const PlayerLevelKey &key2);
bool operator<(const PlayerLevelKey &key1, const PlayerLevelKey &key2);
bool operator==(const PlayerLevelKey &key1, const PlayerLevelKey &key2);

#endif //HW1_PLAYER_H
