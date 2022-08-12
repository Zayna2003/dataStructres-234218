//
// Created by Areej on 01/12/2021.
//

#include "player.h"
// -------------------- Implementation ----------------------- //


Group *Player::getGroup()  {
    return group;
}

int Player::getID() {
    return playerID;
}

int Player::getLevel() const {
    return level;
}

void Player::setGroup(Group *newGroup) {
     group = newGroup;
}

void Player::setID(int ID) {
    playerID = ID;
}

void Player::setLevel(int newLevel) {
    level =  newLevel;
}

//Comparing operators to get the highest level//

bool operator==(const PlayerLevelKey &key1, const PlayerLevelKey &key2) {
    return (key1.playerID == key2.playerID) && (key1.level == key2.level);
}

bool operator<(const PlayerLevelKey &key1, const PlayerLevelKey &key2) {
    if (key1.level == key2.level) {
        return key1.playerID > key2.playerID;
    }
    return key1.level < key2.level;
}
bool operator>(const PlayerLevelKey &key1, const PlayerLevelKey &key2) {
//    if (key1.level == key2.level) {
//        return key1.playerID < key2.playerID;
//    }
//    return key1.level > key2.level;
    return !(key1 == key2) &&  !(key1 < key2);
}

int PlayerLevelKey::getLevel() {
    return level;
}
