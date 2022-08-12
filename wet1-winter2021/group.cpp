//
// Created by Areej on 01/12/2021.
//

#include "group.h"

Group::Group(int ID): groupID(ID),numOfPlayers(0), highestLevelPlayer() {
    playerTreeByLevel = new AVLTree<PlayerLevelKey, Player*>(false);
}

void Group::addPlayerToGroup(Player *player, PlayerLevelKey key) {
    playerTreeByLevel->insert(playerTreeByLevel->root, key, player);
    numOfPlayers++;
}

void Group::removePlayerFromGroup(PlayerLevelKey key) {
    playerTreeByLevel->removeNode(key);
    numOfPlayers--;
}

int Group::getGroupId() const {
    return groupID;
}

AVLTree<PlayerLevelKey, Player*> *Group::getPlayerByLevelTree() {
    return playerTreeByLevel;
}

void Group::setPlayerByLevelTree(AVLTree<PlayerLevelKey, Player*> *tree) {
    playerTreeByLevel = tree;
}

Player* Group::getHighestLevelPlayerInGroup()  {
    return highestLevelPlayer;
}

int Group::getNumOfPlayersInGroup() {
    return numOfPlayers;
}

void Group::setNumOfPlayersInGroup(int num) {
    numOfPlayers = num;
}

void Group::setHighestLevelPlayerInGroup(Player *player) {
    highestLevelPlayer = player;
}

Group::~Group() {
    delete playerTreeByLevel;
};


