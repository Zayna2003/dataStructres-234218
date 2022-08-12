#ifndef WET2_HashTable_H
#define WET2_HashTable_H
#define START_SIZE 10
#define EMPTY 0
#define DELETED 1
#define FULL 2

#include "player.h"
#include "AVLRankTree.h"

class hashTable {
    int playersNum;
    int tableSize;
    int deletedCounter;
    int addCounter;
    Player* table;
    Player deletedPlayer;
public:
    int CheckCell(int k);

    void CleanTable();

    int HashFunc(int playerID, int times);

    int HFunc(int playerID);

    int Step(int playerID);

    int Find(int playerID);

    StatusType MakeBiggerTable();

    StatusType AddNode(Player player);


    hashTable();

    ~hashTable();

    hashTable(hashTable &ht);

    StatusType AddPlayer(int playerID, int groupID, int score, int level);

    StatusType DeletePlayer(int playerID);

    Player GetPlayer(int playerID);

    //StatusType SetPlayer(int playerID, int Level);
    StatusType SetScore(int playerID, int score);

    StatusType changeScoreFlag(int playerID, bool score);

    bool getScoreFlag(int playerID);

    StatusType SetLevel(int playerID, int level);

    int GetGroupID(int playerID);

    int GetLevel(int playerID);

    int GetScore(int playerID);
};

typedef hashTable *HashTable;

#endif
