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
		int randomAttaque;

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
            }
            
        }
    }

}

