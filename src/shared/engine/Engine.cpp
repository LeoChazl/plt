#include "../engine.h"
#include "../state.h"
#include <iostream>
#include <unistd.h>

using namespace state;
using namespace engine;
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
			usleep(200);
	}

    // Erase all the commands which were executed
	for(it=currentCommands.begin(); it!=currentCommands.end(); it++){
		currentCommands.erase(it);
	}
}

void Engine::ScreenRefresh(){
	StateEvent stateEvent(PLAYERCHANGE);
	currentState.notifyObservers(stateEvent, currentState); // Notify the state which will notify render

}

/** Check state to see if a round has ended
 * 
 */
bool Engine::checkRoundEnd(){
	bool playerChange=true;
	bool roundChange = true;
	bool gameEnd = true;

	for(unsigned int k=0; k<currentState.getPlayerList()[currentState.getCurrentPlayerID()]->getMobileEntityList().size();k++){
		if (currentState.getPlayerList()[currentState.getCurrentPlayerID()]->getMobileEntityList()[k]->getStatus()!= DEAD ){
			if (currentState.getPlayerList()[currentState.getCurrentPlayerID()]->getMobileEntityList()[k]->getStatus() != WAITING){
				playerChange = false;
			}
		}
	}

	// For each player
	for (unsigned int i = 0; i < currentState.getPlayerList().size(); i++){
		// For each MobileEntity belonging to each player
		for(unsigned int j = 0;j<currentState.getPlayerList()[i]->getMobileEntityList().size(); j++){

			// As long as the player has a MobileEntity with which he didn't play --> the round is not finished
			if (currentState.getPlayerList()[i]->getId() == currentState.getCurrentPlayerID()){
				if (currentState.getPlayerList()[i]->getMobileEntityList()[j]->getStatus()!= DEAD ){
					if (currentState.getPlayerList()[i]->getMobileEntityList()[j]->getStatus() != WAITING){
						roundChange = false;
					}
				}
			
			}else{ // As long as another player has a MobileEntity alive the game isn't finished
				if(currentState.getPlayerList()[i]->getMobileEntityList()[j]->getStatus()!=DEAD){
					gameEnd=false;
				}
			}
		}
	}

	
	if(playerChange&&!roundChange){
		for (unsigned int i = 0; i < currentState.getPlayerList().size(); i++){
			if (currentState.getPlayerList()[i]->getId() == currentState.getCurrentPlayerID()){
				cout<<"The player "<< currentState.getPlayerList()[i]->getName()<<" end his round!!!"<<endl;
			}
		}
	}

	// If the round changes and the game has ended --> the actual player win the game because all ennemies MobileEntity are dead
	if (roundChange && gameEnd){
		cout << "\tEnd of the game !" << endl;

		for (unsigned int i = 0; i < currentState.getPlayerList().size(); i++){
			if (currentState.getPlayerList()[i]->getId() == currentState.getCurrentPlayerID()){
				cout<<"The player "<< currentState.getPlayerList()[i]->getName()<<" win the game!!!"<<endl;
			}
		}
		roundChange=false;
	}else if(roundChange && !gameEnd){
		cout << "\t\t--- Round has ended. ---\n" << endl;
		currentState.setRound(currentState.getRound() + 1);
	}
	
	return playerChange;
}

/** Sets or resets data to start a new round
 * 
 */
void Engine::checkRoundStart(){
	if (changeRound == true){
	
		// Change the current player
		currentState.setCurrentPlayerID(currentState.getCurrentPlayerID() % currentState.getPlayerList().size());
		cout << "\tCurrent player change" << endl;
		cout << "\t\t--- Round " << currentState.getRound() << " ---\n" << endl;
		
		// For each player
		for (unsigned int i = 0; i < currentState.getPlayerList().size(); i++){
			// For each MobileEntity belonging to each player
			for(unsigned int j = 0;j<currentState.getPlayerList()[i]->getMobileEntityList().size(); j++){

				// For all MobileEntity which do not belong to the currentPlayer and which are not DEAD
				if (currentState.getPlayerList()[i]->getId() != currentState.getCurrentPlayerID() && currentState.getPlayerList()[i]->getMobileEntityList()[j]->getStatus()!= DEAD ){
					// Reset Status to Available
					currentState.getPlayerList()[i]->getMobileEntityList()[j]->setStatus(AVAILABLE);
					
					// Reset movement points for each units
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

void Engine::engineRenderChanged(EngineRenderEvent& engineRenderEvent, state::State& state, state::Position& position, shared_ptr<state::MobileEntity>& selectedMobileEntity, shared_ptr<state::MobileEntity>& targetMobileEntity){
	switch(engineRenderEvent.getEngineRenderEventID()){
		case ARROW_KEYS:
		{
			Move movement(*selectedMobileEntity, position);
			unique_ptr<Command> ptr_move(new Move(movement));
			addCommand(0, move(ptr_move));
			update();
			break;
		}
		case ATTACK:
		{
			Attack attack(*selectedMobileEntity, *targetMobileEntity);
			unique_ptr<Command> ptr_attack(new Attack(attack));
			addCommand(0, move(ptr_attack));
			update();
			break;
		}
		case END_UNIT_ROUND:
		{
			EndEntityRound endEntityRound(*selectedMobileEntity);
			unique_ptr<Command> ptr_endEntityRound(new EndEntityRound(endEntityRound));
			addCommand(0, move(ptr_endEntityRound));
			update();
			break;
		}
		default:
			update();
	}
}


//	Getters

State& Engine::getState(){
	return currentState;
}

map<int, unique_ptr<Command>>& Engine::getCurrentCommands(){
	return currentCommands;
}


//	Destructor

Engine::~Engine (){

}

