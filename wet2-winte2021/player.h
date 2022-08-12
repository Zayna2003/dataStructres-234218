//
// Created by Areej on 01/12/2021.
//
#ifndef HW1_PLAYER_H
#define HW1_PLAYER_H

//#include "group.h"

class player {
    int playerID;
    int groupID;
    int score;
    int level;
    bool scoreChanged;

public:

    player(int playerID, int groupID, int score, int level=0,bool scoreChanged= false );
    player(): playerID(-1), groupID(-1), score(-1), level(-1),scoreChanged(false) {};
    ~player() = default;
    player(player& Player)=default;

    int getGroupID();
    int getPlayerID();
    int getLevel();
    int getScore();
    bool getScoreChanged();
    // returns old score/level value
    int setScore(int score);
    int setLevel(int level);
    bool setScoreChanged(bool b);

    bool operator==(const player& p);
    bool operator!=(const player& p);

    friend bool operator<(const player& p1, const player& p2);
    friend bool operator>(const player& p1, const player& p2);
    friend int operator-( player& p1,  player& p2);
};

typedef player *Player;



class playerByLevel {
public:
    int groupID;
    int score;
    int level;


    playerByLevel( int groupID, int score, int level=0);
    playerByLevel():  groupID(-1), score(-1), level(-1) {};
    ~playerByLevel() = default;
    playerByLevel(playerByLevel& Player)=default;

    int getGroupID();
    int getLevel();
    int getScore();

    int setScore(int score);
    int setLevel(int level);

    bool operator==(const playerByLevel& p);
    bool operator!=(const playerByLevel& p);


    friend bool operator<(const playerByLevel& p1, const playerByLevel& p2);
    friend bool operator>(const playerByLevel& p1, const playerByLevel& p2);
    friend int operator-( playerByLevel& p1,  playerByLevel& p2);

};

typedef playerByLevel *PlayerByLevel;

class playerByScore {
public:
    int groupID;
    int score;
    int level;

    playerByScore( int groupID, int score, int level=0);
    playerByScore():  groupID(-1), score(-1), level(-1) {};
    ~playerByScore() = default;
    playerByScore(playerByScore& Player)=default;

    int getGroupID();
    int getLevel();
    int getScore();

    // returns old score/level value
    int setScore(int score);
    int setLevel(int level);

    bool operator==(const playerByScore& p);
    bool operator!=(const playerByScore& p);


    friend bool operator<(const playerByScore& p1, const playerByScore& p2);
    friend bool operator>(const playerByScore& p1, const playerByScore& p2);
    friend int operator-( playerByScore& p1,  playerByScore& p2);

};

typedef playerByScore *PlayerByScore;
#endif //HW1_PLAYER_H
