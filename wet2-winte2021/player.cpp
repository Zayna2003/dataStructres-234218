//
// Created by Areej on 01/12/2021.
//

#include "player.h"

player::player(int playerID, int groupID, int score, int level,bool scoreChanged):
        playerID(playerID),groupID(groupID),score(score),level(level),scoreChanged(false)
{}

int player::getGroupID()  {
    return groupID;
}
bool player::getScoreChanged(){
    return scoreChanged;
}

int player::getPlayerID() {
    return playerID;
}

int player::getLevel() {
    return level;
}

int player::getScore() {
    return score;
}

int player::setScore(int s) {
    int old = this->score;
    this->score = s;
    return old;
}

int player::setLevel(int l) {
    int old = this->level;
    this->level = l;
    return old;
}
bool player::setScoreChanged(bool b){
this->scoreChanged=b;
    return true;
}

bool player::operator==(const player &p) {
    return this->playerID == p.playerID;
}

bool player::operator!=(const player &p) {
    return !(*this == p);
}

bool operator<(const player& p1, const player& p2){
    return (p1.playerID < p2.playerID );
}

bool operator>(const player& p1, const player& p2) {
    return (p1.playerID > p2.playerID );
}

 int operator-( player& p1,  player& p2){
     if(p1==p2) return 0;
     if(p1>p2)  return 1;
     if(p2>p1)  return -1;
}



// -------------------- Implementation ----------------------- //

playerByLevel::playerByLevel( int groupID, int score, int level):
        groupID(groupID),score(score),level(level)
{}

int playerByLevel::getGroupID()  {
    return groupID;
}


int playerByLevel::getLevel() {
    return level;
}

int playerByLevel::getScore() {
    return score;
}

int playerByLevel::setScore(int s) {
    int old = this->score;
    this->score = s;
    return old;
}

int playerByLevel::setLevel(int l) {
    int old = this->level;
    this->level = l;
    return old;
}


bool playerByLevel::operator==(const playerByLevel &p) {
    if (this->level == p.level ){
        if(this->score == p.score){
                return true;
            }}
    return false;
}


bool playerByLevel::operator!=(const playerByLevel &p) {
    return !(*this == p);
}

bool operator<(const playerByLevel& p1, const playerByLevel& p2){
    if (p1.level == p2.level ){
        return  (p1.score < p2.score);
    }
    return (p1.level < p2.level);
}

bool operator>(const playerByLevel& p1, const playerByLevel& p2) {
    if (p1.level == p2.level ){
        return  (p1.score > p2.score);
    }
    return (p1.level > p2.level);
}

int operator-( playerByLevel& p1,  playerByLevel& p2){
    if(p1==p2) return 0;
    if(p1>p2)  return 1;
    if(p2>p1)  return -1;
}
//=====================================================playerByScore==============================================
playerByScore::playerByScore( int groupID, int score, int level):
       groupID(groupID),score(score),level(level)
{}

int playerByScore::getGroupID()  {
    return groupID;
}


int playerByScore::getLevel() {
    return level;
}

int playerByScore::getScore() {
    return score;
}

int playerByScore::setScore(int s) {
    int old = this->score;
    this->score = s;
    return old;
}

int playerByScore::setLevel(int l) {
    int old = this->level;
    this->level = l;
    return old;
}

bool playerByScore::operator==(const playerByScore &p) {
    if (this->score == p.score ) {
        if (this->level == p.level) {
            return true;
        }
    }
    return false;
}

bool playerByScore::operator!=(const playerByScore &p) {
    return !(*this == p);
}

bool operator<(const playerByScore& p1, const playerByScore& p2){
    if (p1.score == p2.score ){
        return  (p1.level < p2.level);
    }
    return (p1.score < p2.score);
}
bool operator>(const playerByScore& p1, const playerByScore& p2) {
    if (p1.score == p2.score ){
        return  (p1.level > p2.level);
    }
    return (p1.score > p2.score);
}

int operator-( playerByScore& p1,  playerByScore& p2){
    if(p1==p2) return 0;
    if(p1>p2)  return 1;
    if(p2>p1)  return -1;
}