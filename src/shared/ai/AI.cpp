#include "../engine.h"
#include "../state.h"
#include "../ai.h"
#include <iostream>
#include <unistd.h>

using namespace state;
using namespace engine;
using namespace std;
using namespace ai;



//constructor
AI::AI():artificialIntelligenceID(artificialIntelligenceID){

}

//void AI::initAi(int AiID,engine::Engine& engine ){

    //Register all moves
    /*for(int i=0;i<engine.getState().getPlayerList()[AiID]->getMobileEntityList()[0]->getMovementRange()/2;i++){
        for(int j=0;j<engine.getState().getPlayerList()[AiID]->getMobileEntityList()[0]->getMovementRange()/2;j++){
            Position destination(engine.getState().getPlayerList()[AiID]->getMobileEntityList()[0]->getX()+i+j,engine.getState().getPlayerList()[AiID]->getMobileEntityList()[0]->getY()+i+j);
            Move deplacement(*engine.getState().getPlayerList()[AiID]->getMobileEntityList()[0], destination);
            std::unique_ptr<engine::Command> ptr_deplacement (new Move(deplacement));
            aiCommandList.push_back(move(ptr_deplacement));
            //aiCommandList[k]=move(ptr_deplacement);
        }
    }*/
   /*int i=1;
   int j=0;
    Position destination(engine.getState().getPlayerList()[AiID]->getMobileEntityList()[0]->getX()+i+j,engine.getState().getPlayerList()[AiID]->getMobileEntityList()[0]->getY()+i+j);
    Move deplacement(*engine.getState().getPlayerList()[AiID]->getMobileEntityList()[0], destination);
    std::unique_ptr<engine::Command> ptr_deplacement (new Move(deplacement));
    aiCommandList.push_back(move(ptr_deplacement));*/

    //Register Attack 
    /*Attack attack3(*engine.getState().getPlayerList()[AiID]->getMobileEntityList()[1], *engine.getState().getPlayerList()[1]->getMobileEntityList()[0]);
    unique_ptr<Command> ptr_attack3 (new Attack(attack3));
    aiCommandList.push_back(move(ptr_attack3));*/
    
//}

/*void AI::run (engine::Engine& engine){

    // initialize random seed: 
    srand (time(NULL));
    // generate number between 1 and command list size 
    int randomCommand = rand() % aiCommandList.size();

    aiCommandList[randomCommand]->execute(engine.getState());
}*/

//Getter and Setter
int AI::getArtificialIntelligenceID(){
    return artificialIntelligenceID;
}

void setArtificialIntelligenceID(int artificialIntelligenceID){
    artificialIntelligenceID=artificialIntelligenceID;
}



