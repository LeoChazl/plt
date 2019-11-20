#include "../engine.h"
#include "../state.h"
#include "../ai.h"
#include <iostream>
#include <unistd.h>

using namespace state;
using namespace engine;
using namespace std;
using namespace ai;


RandomAI::RandomAI (int AiID){
    artificialIntelligenceID=AiID;
}


void RandomAI::run (engine::Engine& engine){

    if(engine.getState().getCurrentPlayerID()==artificialIntelligenceID){
        int randomAction;
		int randomPosition;
		int randomAttackPosition;

        //for each Unit controlled by artificial Intelligence Player
        for(unsigned int i=0;i<engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList().size();i++){
            // Reinitialisations de changement de personnage
			int notAllowedMove = false;
			int notAllowedAttack = false;
			//int premierEssai = true;

            //The Unit need to end his turn or dead before changing to another unit
            while (engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getStatus()!=DEAD && engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getStatus()!=WAITING)
            {
                engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->setStatus(SELECTED);

                // initialize random seed: 
                srand(time(NULL));
                if (notAllowedMove == true && notAllowedAttack == true){
                    randomAction = 2;//EndAction=2
                }
                else if (notAllowedMove == true && notAllowedAttack == false){
                    randomAction = rand()%2+1 ; //EndAction=2 or Attack=1
                }
                else if (notAllowedMove == false && notAllowedAttack == true){
                    randomAction = rand()%2;// Move=0 or EndAction=2
                    if(randomAction == 1){
                        randomAction = 2;
                    }
                }
                else{randomAction = rand()%3;}//EndAction=2 or Attack=1 or Move=0


                // 0 : Move
                if (randomAction == 0 && engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getMovementLeft()!= 0){
                    //Initialize a liste of allowed Move
                    std::vector<Position> allowedMoveList =engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->allowedMove(engine.getState());
                    if (allowedMoveList.size() != 0){
                        srand(time(NULL));
                        randomPosition = rand()%allowedMoveList.size();
                        
                        // Move Command
                        Move movement (*engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i], allowedMoveList[randomPosition]);
                        unique_ptr<Command> ptr_movement (new Move(movement));
                        engine.addCommand(0, move(ptr_movement));
                        engine.update();//update engine will use state to notify render about changes

                        notAllowedAttack = false;
                        sleep(1);
                    }
                    else{notAllowedMove = true;}
                }

                // 1 : Attack
                else if (randomAction == 1){
                    //Initialize a list with all attack allowed positions
                    std::vector<Position> allowedAttackPositionList = engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->allowedAttack(engine.getState());

                    if (allowedAttackPositionList.size() !=0){
                        srand(time(NULL));
                        randomAttackPosition = rand()%allowedAttackPositionList.size();
                                            
                        // Check if there are units on the random Attack Position
                        int target=engine.getState().isOccupied(allowedAttackPositionList[randomAttackPosition].getX(),allowedAttackPositionList[randomAttackPosition].getY());
                        if (target != -1){
                            // Commande d'attaque
                            Attack attack(*engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i], *engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[target]);
                            unique_ptr<Command> ptr_attack (new Attack(attack));
                            engine.addCommand(0, move(ptr_attack));
                            engine.update();
                            notAllowedMove = false;
                            sleep(1);
                        }
                    }
                    else{notAllowedAttack = true;}				
                }

                // 2 : EndEntityRound
                else if (randomAction == 2){
                    EndEntityRound endAction(*engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]);
                    unique_ptr<Command> ptr_endAction (new EndEntityRound(endAction));
                    engine.addCommand(0, move(ptr_endAction));
                    engine.update();
                    sleep(1);
                }
            }
            
        }
    }

}

