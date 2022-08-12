//
// Created by Areej on 01/12/2021.
//
#include "library1.h"
#include "game.h"
void *Init(){
    Game* game = new Game();
    return (void*)game;
}

StatusType AddGroup(void *DS, int GroupID){
    if (!DS || GroupID <= 0) {
        return INVALID_INPUT;
    }
    try {
        ((Game*)DS)->addGroup(GroupID);
    }catch (Game::Failure& error){
        return FAILURE;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int Level) {
    if(!DS || PlayerID <=0 || GroupID <= 0 || Level < 0){
        return INVALID_INPUT;
    }
    try{
        ((Game*)DS)->addPlayer(PlayerID, GroupID, Level);
    }catch (Game::Failure& e){
        return FAILURE;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType RemovePlayer(void *DS, int PlayerID){
    if (!DS || PlayerID <= 0) {
        return INVALID_INPUT;
    }
    try {
        ((Game*)DS)->removePlayer(PlayerID);
    }catch (Game::Failure& error){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType ReplaceGroup(void *DS, int GroupID, int ReplacementID) {
    if (!DS || GroupID <= 0 || ReplacementID <= 0 || GroupID==ReplacementID ) {
        return INVALID_INPUT;
    }
    try{
        ((Game*)DS)->replaceGroup(GroupID, ReplacementID);
    }catch (Game::Failure& error){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType IncreaseLevel(void *DS, int PlayerID, int LevelIncrease) {
    if(!DS || PlayerID <= 0 || LevelIncrease <= 0){
        return INVALID_INPUT;
    }
    try{
        ((Game*)DS)->increaseLevel(PlayerID, LevelIncrease);
    }catch (Game::Failure& e){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetHighestLevel(void *DS, int GroupID, int *PlayerID) {
    if (!DS || GroupID == 0 || !PlayerID) {
        return INVALID_INPUT;
    }
    try {
        ((Game*)DS)->getHighestLevelPlayer(GroupID, PlayerID);
    }catch (Game::Failure& error){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetAllPlayersByLevel(void *DS, int GroupID, int **Players, int *numOfPlayers) {
    if(!DS || GroupID == 0 || !Players || !numOfPlayers){
        return INVALID_INPUT;
    }
    try{
        ((Game*)DS)->getAllPlayersByLevel(GroupID, Players, numOfPlayers);
    }catch (Game::Failure& e){
        return FAILURE;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType GetGroupsHighestLevel(void *DS, int numOfGroups, int **Players) {
    if (!DS || numOfGroups <= 0 || !Players) {
        return INVALID_INPUT;
    }
    try{
        ((Game*)DS)->getGroupsHighestLevel(numOfGroups, Players);
    }catch (Game::Failure& e){
        return FAILURE;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

void Quit(void** DS) {
    delete (*((Game**)DS));
    *DS=nullptr;
}
