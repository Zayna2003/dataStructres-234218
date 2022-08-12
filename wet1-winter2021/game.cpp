//
// Created by Areej on 01/12/2021.
//

#include "game.h"
#include "AVL.h"

// =====================================================================================================================
//                                                    IMPLEMENTATION - START
// =====================================================================================================================
// --------------------------------------------- CONSTRUCTOR -----------------------------------------------------------
Game::Game() : numOfPlayersInGame(0), numOfGroupsInGame(0), highestLevelPlayer(nullptr) {
    groupsById = new AVLTree<int, Group*>(true);
    playersById = new AVLTree<int, Player*>(false);
    playersByLevel = new AVLTree<PlayerLevelKey, Player*>(false);
}

// --------------------------------------------- DESTRUCTOR -----------------------------------------------------------
/*Game::~Game() {
//    groupsById.treeClear();
//    delete groupsById.root;
//    playersByLevel.treeClear();
//    delete playersByLevel.root;
//    delete highestLevelPlayer;
}*/

// --------------------------------------------- addPlayer FUNCTION ----------------------------------------------------
void Game::addPlayer(int playerId, int groupId, int level) {
    Player *newPlayerByID = new Player(nullptr, playerId, level);
    Player *newPlayerByLevel = new Player(nullptr, playerId, level);

    if (!groupsById->contains(groupId)) {
        delete newPlayerByID;
        delete newPlayerByLevel;
        throw Failure();
    }
    Group *playerGroup = groupsById->Find(groupId);
    // add to players by level tree
    newPlayerByID->setGroup(playerGroup);
    newPlayerByLevel->setGroup(playerGroup);
    // add to players by id tree
    try {
        playersById->insert(playersById->root, playerId, newPlayerByID);
        playersByLevel->insert(playersByLevel->root, PlayerLevelKey(*newPlayerByLevel), newPlayerByLevel);
    } catch (AVLTree<int, Player *>::KeyAlreadyExists &e) {
        delete newPlayerByID;
        delete newPlayerByLevel;
        throw Failure();
    }

 //   Group *playerGroup = groupsById.Find(groupId);
    // add to players by level tree
   // newPlayer->setGroup(playerGroup);
    Player *newPlayerInGroup = new Player(nullptr, playerId, level);
    newPlayerInGroup->group = playerGroup;

    (playerGroup->playerTreeByLevel)->insert((playerGroup->playerTreeByLevel)->root,
                                                                                PlayerLevelKey(playerId, level),
                                                                                newPlayerInGroup);
    (playerGroup->numOfPlayers)++;
    if (playerGroup->highestLevelPlayer != nullptr) {
        if (PlayerLevelKey(*(playerGroup->getHighestLevelPlayerInGroup())) < PlayerLevelKey(*newPlayerInGroup)) {
            playerGroup->highestLevelPlayer = newPlayerInGroup;
        }
    } else {
        playerGroup->highestLevelPlayer = newPlayerInGroup;
    }
    //update the highest level player
    if (highestLevelPlayer != nullptr) {
        if (PlayerLevelKey(*getHighestLevelPlayer()) < PlayerLevelKey(*newPlayerByLevel)) {
            highestLevelPlayer = newPlayerByLevel;
        }
    } else {
        highestLevelPlayer = newPlayerByLevel;
    }

    numOfPlayersInGame++;
}

// --------------------------------------------- addGroup FUNCTION -----------------------------------------------------
void Game::addGroup(int groupId) {
    Group *newGroup = new Group(groupId);
    /*
     *
     *
     * (Group*)malloc(sizeof (Group));
    newGroup->groupID = groupId;
     *
     */
    try {
        groupsById->insert(groupsById->root, groupId, newGroup);
        // numOfGroupsInGame++;
    } catch (AVLTree<int, Group *>::KeyAlreadyExists &e) {
        delete newGroup;
        throw Failure();

    }
    numOfGroupsInGame++;
    //free(newGroup);
}

// --------------------------------------------- removePlayer FUNCTION -------------------------------------------------
void Game::removePlayer(int playerId) {
    Player *playerToRemove;
    // remove from players by id tree

    if (!playersById->contains(playerId)) {
        throw Failure();
    }
    playerToRemove = playersById->Find(playerId);
    // remove from group
    Group *toRemoveFromGroup = playerToRemove->getGroup();
    if (toRemoveFromGroup) {
        toRemoveFromGroup->removePlayerFromGroup(PlayerLevelKey(*playerToRemove));
        if (toRemoveFromGroup->getPlayerByLevelTree()->root) {
            toRemoveFromGroup->setHighestLevelPlayerInGroup(toRemoveFromGroup->getPlayerByLevelTree()->GetMax()->data);
        } else {
            toRemoveFromGroup->setHighestLevelPlayerInGroup(nullptr);
        }
    }
    playersByLevel->removeNode(PlayerLevelKey(*playerToRemove));
    playersById->removeNode(playerId);
    // delete playerToRemove;
    if ((playersByLevel->root)) {
        highestLevelPlayer = playersByLevel->GetMax()->data;
    } else {
        highestLevelPlayer = nullptr;
    }
    numOfPlayersInGame--;
   // (toRemoveFromGroup->numOfPlayers)--;
}

// --------------------------------------------- replaceGroup FUNCTION -------------------------------------------------
void Game::movePlayerToGroup(int playerId, int groupId) {
    Player *player;
    Group *group;
    /*try {
        player = playersById.Find(playerId);
        group = groupsById.Find(groupId);
    } catch (AVLTree<int, Player *>::KeyDoesNotExist &e) {
        throw e.what();
    } catch (AVLTree<int, Group *>::KeyDoesNotExist &e) {
        throw e.what();
    }*/
    // check if player already in group
    player=playersById->Find(playerId);
    group=groupsById->Find(groupId);

    group->addPlayerToGroup(player, PlayerLevelKey(*player));
    if (group->getHighestLevelPlayerInGroup()) {
        if (PlayerLevelKey(*group->getHighestLevelPlayerInGroup())
            < PlayerLevelKey(*player)) {
            group->setHighestLevelPlayerInGroup(player);
        }
    } else {
        group->setHighestLevelPlayerInGroup(player);
    }
    if (player->getGroup()) {
        Group *oldGroup = player->getGroup();
        oldGroup->removePlayerFromGroup(PlayerLevelKey(*player));
        if (oldGroup->getPlayerByLevelTree()->root) {
            oldGroup->setHighestLevelPlayerInGroup
                    (oldGroup->getPlayerByLevelTree()->GetMax()->data);

        } else {
            oldGroup->setHighestLevelPlayerInGroup(nullptr);
        }
    }
    player->setGroup(group);
}

void Game::replaceGroup(int groupID, int replacementID) {
    Group *oldGroup;
    Group *newGroup;
    if (!groupsById->contains(groupID) || !groupsById->contains(replacementID)  ) {
        throw Failure();
    }
    oldGroup=groupsById->Find(groupID);
    newGroup=groupsById->Find(replacementID);
    int numOfPlayersInGroup = oldGroup->getNumOfPlayersInGroup();
    Player **playersArray = (Player **) malloc(sizeof(Player*) * numOfPlayersInGroup);

    oldGroup->getPlayerByLevelTree()->printintwo(playersArray, &numOfPlayersInGroup);

    for (int i = 0; i < numOfPlayersInGroup; i++) {
        // movePlayerToGroup(playersArray[i].getID(), replacementID);
        int tempID = playersArray[i]->getID(), tempLvl = playersArray[i]->getLevel();
        removePlayer(playersArray[i]->getID());
        addPlayer(tempID, replacementID, tempLvl);
    }
    free(playersArray);
    groupsById->removeNode(groupID);
}

// --------------------------------------------- getHighestLevelPlayer FUNCTION ----------------------------------------
void Game::getHighestLevelPlayer(int groupId, int *playerId) {
    if (groupId < 0) {
        if (!highestLevelPlayer) {
            *playerId = -1;
            return;
        } else {
            *playerId = highestLevelPlayer->getID();
            return;
        }
    } else {
        Group *group;
        if (!groupsById->contains(groupId)) {
            throw Failure();
        }
        group = groupsById->Find(groupId);
        if (!group->getHighestLevelPlayerInGroup()) {
            *playerId = -1;
            return;
        }
        *playerId = group->getHighestLevelPlayerInGroup()->getID();
    }
}

Player *Game::getHighestLevelPlayer() const {
    return highestLevelPlayer;
}

// --------------------------------------------- increaseLevel FUNCTION ------------------------------------------------
void Game::increaseLevel(int playerId, int levelIncrease) {
   // Player *playerToIncrease;
    // remove from players by id tree
    /*try {
       bool b = playersById.contains(playerId);
    } catch (AVLTree<int, Player *>::KeyDoesNotExist &e) {
        throw Failure();
    }*/

    if (!playersById->contains(playerId)) {
        throw Failure();
    }
    Player *playerToIncrease=playersById->Find(playerId);

    int temp_group_id = playerToIncrease->getGroup()->getGroupId();
    int increased_level = playerToIncrease->getLevel() + levelIncrease;

    // exception are handled in the functions
    removePlayer(playerId);
    addPlayer(playerId, temp_group_id, increased_level);
}

// --------------------------------------------- getAllPlayersByLevel FUNCTION -----------------------------------------
void Game::getAllPlayersByLevel(int groupId, int **players, int *numOfPlayers) {
    Group *group;
    if (groupId < 0) {
        *numOfPlayers = numOfPlayersInGame;
        if (numOfPlayersInGame == 0) {
            *players = nullptr;
            return;
        } else {
            Player *playersArray = (Player *) malloc(numOfPlayersInGame * sizeof(Player));
            playersByLevel->printin(playersArray, numOfPlayers);

            *players = (int *) malloc((*numOfPlayers) * sizeof(int));
            for (int i = 0; i < *numOfPlayers; i++) {
                (*players)[i] = playersArray[(*numOfPlayers)-1-i].getID();
            }
            free(playersArray);
            return;
        }
    }

    if (groupId > 0) {
        if (!groupsById->contains(groupId)) {
            throw Failure();
        }
        group=groupsById->Find(groupId);
        *numOfPlayers = group->getNumOfPlayersInGroup();
        if (group->getNumOfPlayersInGroup() == 0) {
            *players = nullptr;
            return;
        }

        Player *playersArray = (Player *) malloc(sizeof(Player) * (*numOfPlayers));
        (group->playerTreeByLevel)->printin(playersArray, numOfPlayers);

        *players = (int *) malloc((*numOfPlayers) * sizeof(int));
        for (int i = 0; i < *numOfPlayers; i++) {
            (*players)[i] = playersArray[(*numOfPlayers)-1-i].getID();
        }
        free(playersArray);
        return;
    }
}

// --------------------------------------------- getGroupsHighestLevel FUNCTION -----------------------------------------
void Game::getGroupsHighestLevel(int numOfGroups, int **Players) {
    int minNumOfPlayers = 1;
    int group_i = 0;
    int numOfPlayersInGame2 = 0;// (int)malloc( sizeof(int));
    if(numOfGroupsInGame<numOfGroups){
        throw Failure();
    }
    *Players = (int *) malloc((numOfGroups) * sizeof(int));
    Group *groupArray = (Group *) malloc(sizeof(Group) * numOfGroupsInGame);

    //   groupArray = new Group* [*numOfPlayersInGame];
    // int** groupArray;
    groupsById->printin(groupArray, &numOfPlayersInGame2);

    for (int i = 0; i < numOfPlayersInGame2; i++) {
        int numOfPLayersInGroup = groupArray[i].getNumOfPlayersInGroup();
        if (numOfPLayersInGroup < minNumOfPlayers) {
            continue;
        }
        if (group_i < numOfGroups) {
            int jhjg = (*(groupArray[i].getHighestLevelPlayerInGroup())).getID();
            (*Players)[group_i++] = jhjg;
        } else {
            break;
        }
        // group_i++;
    }
    free(groupArray);
    if(group_i<numOfGroups){
        *Players =NULL;
        throw Failure();
    }

}

// --------------------------------------------- getGroupsById FUNCTION -----------------------------------------
//const AVLTree<int, Group *> &Game::getGroupsById() const {
//    return groupsById;
//}

Game::~Game() {

    delete groupsById;
    delete playersById;
    delete playersByLevel;
    //setGroupsToNullLvl(playersByLevel.root);
    //setGroupsToNullGroups(groupsById.root);
    //setGroupsToNull(playersById.root);
}

void Game::setGroupsToNull(AVLTree<int, Player *>::Node *node) {
    if (node) {
        setGroupsToNull(node->left);
        setGroupsToNull(node->right);
        if(node->data){
            node->data->group = nullptr;
        }
    }
}

void Game::setGroupsToNullLvl(AVLTree<PlayerLevelKey, Player *>::Node* node) {
    if (node) {
        setGroupsToNullLvl(node->left);
        setGroupsToNullLvl(node->right);
        if(node->data){
            node->data->group = nullptr;
        }
    }
}

void Game::setGroupsToNullGroups(AVLTree<int, Group *>::Node *node) {
    if (node) {
        setGroupsToNullGroups(node->left);
        setGroupsToNullGroups(node->right);
        if(node->data){
            setGroupsToNullLvl(node->data->playerTreeByLevel->root);
        }
    }
}



// =====================================================================================================================
//                                                    IMPLEMENTATION - END
// =====================================================================================================================








