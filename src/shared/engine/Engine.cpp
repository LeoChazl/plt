#include "../engine.h"
#include </home/ensea/plt/src/client/render.h>
#include "../state.h"
#include <iostream>
#include <unistd.h>

using namespace state;
using namespace engine;
using namespace render;
using namespace std;

//	Constructor

Engine::Engine () : currentState(){
	changeRound = false;
}

// Functions

/** Add command pointors in an associative list
 * 
 * params :
 * priority -> index in the list 
 * ptr_cmd -> pointor on the command
 */ 
void Engine::addCommand (int priority, std::unique_ptr<Command> ptr_cmd){
	currentCommands[priority]=move(ptr_cmd);
}

/** Executes all the commands in the associative list
 * 
 */
void Engine::update (){
	StateEvent stateEvent(PLAYERCHANGE);

	map<int, std::unique_ptr<Command>>::iterator it;

    // Execute each command of the currentCommands table
	for(size_t i=0; i<currentCommands.size();i++){
			currentCommands[i]->execute(currentState);
			currentState.notifyObservers(stateEvent, currentState); // Notify the state which will notify render
			sleep(2);
	}

    // Erase all the commands which were executed
	for(it=currentCommands.begin(); it!=currentCommands.end(); it++){
		currentCommands.erase(it);
	}
}


bool Engine::checkRoundEnd(){
	bool roundChange = true;
	bool gameEnd = true;

	//for each player
	for (unsigned int i = 0; i < currentState.getPlayerList().size(); i++){
		//for each MobileEntity beloging to each player
		for(unsigned int j = 0;j<currentState.getPlayerList()[i]->getMobileEntityList().size(); j++){

			//Until the player has MObileEntity with which he didn't play --> the round is not finished
			if (currentState.getPlayerList()[i]->getId() == currentState.getCurrentPlayerID()){
				if (currentState.getPlayerList()[i]->getMobileEntityList()[j]->getStatus()!= DEAD ){
					if (currentState.getPlayerList()[i]->getMobileEntityList()[j]->getStatus() != WAITING){
						roundChange = false;
					}
				}
			
			}else{//Until ennemie player have MobileEntity alive the game didn't finished
				if(currentState.getPlayerList()[i]->getMobileEntityList()[j]->getStatus()!=DEAD){
					gameEnd=false;
				}
			}
		}
	}

	
	//If the roundChage and the GameEnd --> the actual player win the game because all ennemeies MobileENtity are dead
	if (roundChange && gameEnd){
		cout << "\tPartie Terminee !" << endl;
		//currentState.setFin(partieFinie);

		for (unsigned int i = 0; i < currentState.getPlayerList().size(); i++){
			if (currentState.getPlayerList()[i]->getId() == currentState.getCurrentPlayerID()){
				cout<<"Le joueur "<< currentState.getPlayerList()[i]->getName()<<" a gagné la partie!!!"<<endl;
			}
		}
		roundChange=false;
	}else if(roundChange && !gameEnd){
		cout << "\t\t--- Tour Terminé. ---\n" << endl;
		//etatActuel.setTour(etatActuel.getTour()+1);

	}
	
	return roundChange;
}

void Engine::checkRoundStart(){
	if (changeRound == true){
	
		//change the current player
		currentState.setCurrentPlayerID(currentState.getCurrentPlayerID() % currentState.getPlayerList().size());
		cout << "\t-> Changement de joueur <-" << endl;
		//cout << "\t\t--- Tour " << etatActuel.getTour() << " ---\n" << endl;
		
		//for each player
		for (unsigned int i = 0; i < currentState.getPlayerList().size(); i++){
			//for each MobileEntity beloging to each player
			for(unsigned int j = 0;j<currentState.getPlayerList()[i]->getMobileEntityList().size(); j++){

				// For all MobileEntity which are not beloging to the cureentPlayer and which are not DEAD
				if (currentState.getPlayerList()[i]->getId() != currentState.getCurrentPlayerID() && currentState.getPlayerList()[i]->getMobileEntityList()[j]->getStatus()!= DEAD ){
					// Reset Status to --> Available
					currentState.getPlayerList()[i]->getMobileEntityList()[j]->setStatus(AVAILABLE);
					
					//Reset movement Points to each units
					if (currentState.getPlayerList()[i]->getMobileEntityList()[j]->getEntityId() == KNIGHT){
						currentState.getPlayerList()[i]->getMobileEntityList()[j]->setMovementRange(2);
					}
					else if(currentState.getPlayerList()[i]->getMobileEntityList()[j]->getEntityId() == TROLL) {
						currentState.getPlayerList()[i]->getMobileEntityList()[j]->setMovementRange(3);

					}else if(currentState.getPlayerList()[i]->getMobileEntityList()[j]->getEntityId() == MAGE) {
						currentState.getPlayerList()[i]->getMobileEntityList()[j]->setMovementRange(4);

					}	
				}
				
			}
		}
		
		changeRound = !changeRound;
	}
}


//	Getters

State& Engine::getState (){
	return currentState;
}

map<int, unique_ptr<Command>>& Engine::getCurrentCommands(){
	return currentCommands;
}


//	Destructor
Engine::~Engine (){
}

