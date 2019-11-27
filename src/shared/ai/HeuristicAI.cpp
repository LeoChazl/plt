#include "../engine.h"
#include "../state.h"
#include "../ai.h"
#include <iostream>
#include <unistd.h>

using namespace state;
using namespace engine;
using namespace std;
using namespace ai;

//Constructor
HeuristicAI::HeuristicAI(int AiID){
        artificialIntelligenceID=AiID;
}

// Functions 

void HeuristicAI::run (engine::Engine& engine){
    //The current player ID is equal AI ID -> AI turn
    if(engine.getState().getCurrentPlayerID()==artificialIntelligenceID){
        artificialIntelligenceID=artificialIntelligenceID-1;//In order to use the id as an array index
        int action;

        //for each Unit controlled by artificial Intelligence Player
        for(unsigned int i=0;i<engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList().size();i++){

            //The Unit need to end his turn or dead before changing to another unit
            while (engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getStatus()!=DEAD && engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getStatus()!=WAITING)
            {
                //Set the status of the current Unit as selected
                engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->setStatus(SELECTED);
                bool ennemyUnitsAllDead=true;

                /*** Check if there are ennemy units still alive***/
                for (size_t l = 0; l < engine.getState().getPlayerList().size(); l++){
                    if(engine.getState().getPlayerList()[l]->getId()!=artificialIntelligenceID){
                        for (size_t k = 0; k < engine.getState().getPlayerList()[i]->getMobileEntityList().size(); k++)
                        {
                            if(engine.getState().getPlayerList()[l]->getMobileEntityList()[k]->getStatus()!=DEAD){
                                ennemyUnitsAllDead = false; //there are ennemy units still alive
                                break;
                            }
                        }
                    }
                }

                //No Units alive--> AI 
                if (ennemyUnitsAllDead){
						action = 2;//EndAction=2
				}
				else{
                    //AI Units health are weak --> run (Move)
                    if(engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getHealth()<=10){
                        action=0; //Move=0
                    }else{
                        //Recover in a list all attackable positions
                        std::vector<Position> allowedAttackPositionList = engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->allowedAttack(engine.getState());
                        std::vector<Position> occupiedPositionInAttackZone;
                        int x_unit,y_unit;
                        if(allowedAttackPositionList.size()!=0){
                            //Check and recover in a list all units position inside the attack Zone
                            for (size_t m = 0; m < allowedAttackPositionList.size(); m++)
                            {
                                x_unit=allowedAttackPositionList[m].getX();
                                y_unit=allowedAttackPositionList[m].getY();
                                if(engine.getState().isOccupied(x_unit,y_unit)){
                                    occupiedPositionInAttackZone.push_back(allowedAttackPositionList[i]);
                                }
                            }

                            //There are units in attackable zone
                            state::Position unitToAttack;
                            if(occupiedPositionInAttackZone.size()!=0){
                                unitToAttack=attackSuccessScoring(occupiedPositionInAttackZone,engine);

                            }else{//No units in attackable zone
                                action=0;//Move=0
                            }
                        }

                    }
                }





            }

        }

    }

}

state::Position HeuristicAI::attackSuccessScoring (std::vector<state::Position> occupiedPositionInAttackZone,engine::Engine& engine){
    for (size_t i = 0; i < occupiedPositionInAttackZone.size(); i++)
    {
        
    }
    
}


std::vector<state::Position> HeuristicAI::algorithmAStar (engine::Engine& engine, state::Position start, state::Position goal){
    vector<Position> listPosition;
    return listPosition;
}