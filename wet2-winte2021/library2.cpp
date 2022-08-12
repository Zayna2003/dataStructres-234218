/****************************************************************************/
/*                                                                          */
/* This file contains the interface functions                               */
/* you should use for the wet ex 2                                          */
/*                                                                          */
/****************************************************************************/

/****************************************************************************/
/*                                                                          */
/* File Name : library.h                                                   */
/*                                                                          */
/****************************************************************************/

#include "library2.h"
#include "game.h"

    void *Init(int k, int scale){
        Game* game = new Game(k,scale);
        return (void*)game;
    }

    StatusType MergeGroups(void *DS, int GroupID1, int GroupID2){
        if(!DS || GroupID1 <=0 || GroupID2 <= 0 ){
            return INVALID_INPUT;
        }
        StatusType res=((Game*)DS)->MergeGroups(GroupID1,GroupID2);
        if(res==INVALID_INPUT)
            return INVALID_INPUT;
        if(res==FAILURE)
            return FAILURE;
        else if (res==ALLOCATION_ERROR)
            return ALLOCATION_ERROR;
        return SUCCESS;
    }

    StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int score){
        if(!DS || PlayerID <=0 || GroupID <= 0 || score <=0) {
            return INVALID_INPUT;
        }
        StatusType res=((Game*)DS)->AddPlayer(PlayerID,GroupID,score);
        if(res==INVALID_INPUT)
            return INVALID_INPUT;
        if(res==FAILURE)
            return FAILURE;
        else if (res==ALLOCATION_ERROR)
            return ALLOCATION_ERROR;
        return SUCCESS;
    }

    StatusType RemovePlayer(void *DS, int PlayerID){
        if(!DS || PlayerID <=0 ) {
            return INVALID_INPUT;
        }
        StatusType res=((Game*)DS)->RemovePlayer(PlayerID);
        if(res==INVALID_INPUT)
            return INVALID_INPUT;
        if(res==FAILURE)
            return FAILURE;
        else if (res==ALLOCATION_ERROR)
            return ALLOCATION_ERROR;
        return SUCCESS;
    }

    StatusType IncreasePlayerIDLevel(void *DS, int PlayerID, int LevelIncrease){
        if(!DS || PlayerID <=0 ||LevelIncrease <=0) {
            return INVALID_INPUT;
        }
        StatusType res=((Game*)DS)->IncreasePlayerIDLevel(PlayerID,LevelIncrease);
        if(res==INVALID_INPUT)
            return INVALID_INPUT;
        if(res==FAILURE)
            return FAILURE;
        else if (res==ALLOCATION_ERROR)
            return ALLOCATION_ERROR;
        return SUCCESS;
    }

    StatusType ChangePlayerIDScore(void *DS, int PlayerID, int NewScore){
        if(!DS || PlayerID <=0 ||NewScore <=0) {
            return INVALID_INPUT;
        }
        StatusType res=((Game*)DS)->ChangePlayerIDScore(PlayerID,NewScore);
        if(res==INVALID_INPUT)
            return INVALID_INPUT;
        if(res==FAILURE)
            return FAILURE;
        else if (res==ALLOCATION_ERROR)
            return ALLOCATION_ERROR;
        return SUCCESS;
    }

    StatusType GetPercentOfPlayersWithScoreInBounds(void *DS, int GroupID, int score, int lowerLevel, int higherLevel,
                                                    double * players){
        if(!DS || GroupID <0 ||!players) {
            return INVALID_INPUT;
        }
        StatusType res=((Game*)DS)->GetPercentOfPlayersWithScoreInBounds(GroupID, score, lowerLevel,
                                                                         higherLevel, players);
        if(res==INVALID_INPUT)
            return INVALID_INPUT;
        if(res==FAILURE)
            return FAILURE;
        else if (res==ALLOCATION_ERROR)
            return ALLOCATION_ERROR;
        return SUCCESS;
    }

    StatusType AverageHighestPlayerLevelByGroup(void *DS, int GroupID, int m, double * level){
        if(!DS || GroupID <0 ||m <=0 || !level) {
            return INVALID_INPUT;
        }
        StatusType res=((Game*)DS)->AverageHighestPlayerLevelByGroup(GroupID,m,level);
        if(res==INVALID_INPUT)
            return INVALID_INPUT;
        if(res==FAILURE)
            return FAILURE;
        else if (res==ALLOCATION_ERROR)
            return ALLOCATION_ERROR;
        return SUCCESS;
    }

    StatusType GetPlayersBound(void *DS, int GroupID, int score, int m,
                               int * LowerBoundPlayers, int * HigherBoundPlayers){
        return SUCCESS;
    }

    void Quit(void** DS){
        delete (*((Game**)DS));
        *DS=nullptr;
    }

