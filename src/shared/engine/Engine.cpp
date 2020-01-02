#include "../engine.h"
#include "../state.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "../../../extern/jsoncpp-1.8.0/jsoncpp.cpp"

using namespace state;
using namespace engine;
using namespace std;

//	Constructor

Engine::Engine () : currentState(){
	changeRound = false;
	record["size"] = 0;
	record["tabCommand"][0] = "";
}

// Functions

/** Add command pointors in an associative list
 * 
 * params :
 * priority -> index in the list 
 * ptr_cmd -> pointor on the command
 */ 

void Engine::addCommand(int priority, std::unique_ptr<Command> ptr_cmd){
	Json::Value newCommand = ptr_cmd->serialize();
	record["tabCommand"][record["size"].asUInt()] = newCommand;
	record["size"] = record["size"].asUInt() + 1;
	
	currentCommands[priority]=move(ptr_cmd);	
}

/** Executes all the commands in the associative list
 * 
 */
void Engine::update(){
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

void Engine::screenRefresh(){
	StateEvent stateEvent(PLAYERCHANGE);
	currentState.notifyObservers(stateEvent, currentState); // Notify the state which will notify render

}

/** Check state to see if a round has ended
 * 
 */
bool Engine::checkRoundEnd(){
	bool playerChange = true;
	bool roundChange = true;
	bool gameEnd = true;
	int currentPlayerID=currentState.getCurrentPlayerID();

	// For each player
	for (unsigned int i = 0; i < currentState.getPlayerList().size(); i++){
		// For each MobileEntity belonging to each player
		for(unsigned int j = 0;j<currentState.getPlayerList()[i]->getMobileEntityList().size(); j++){

			// As long as a player has a MobileEntity with which he didn't play --> the round is not finished
			if(currentState.getPlayerList()[i]->getId() == currentState.getCurrentPlayerID()){
				if (currentState.getPlayerList()[i]->getMobileEntityList()[j]->getStatus()!= DEAD ){
					if (currentState.getPlayerList()[i]->getMobileEntityList()[j]->getStatus() != WAITING){
						playerChange = false;
					}
				}
			}
			if (currentState.getPlayerList()[i]->getMobileEntityList()[j]->getStatus()!= DEAD ){
				if (currentState.getPlayerList()[i]->getMobileEntityList()[j]->getStatus() != WAITING){
					roundChange = false;
				}
			}
			// As long as another player has a MobileEntity alive the game isn't finished
			if(currentState.getPlayerList()[i]->getId()!=currentPlayerID){
				if(currentState.getPlayerList()[i]->getMobileEntityList()[j]->getStatus()!=DEAD){
					gameEnd=false;
				}
			}
		}
	}

	if(playerChange && !roundChange){
		cout << "The player " << currentState.getCurrentPlayerID() << " ends his round.\n"<< endl;
		currentState.setCurrentPlayerID(currentState.getCurrentPlayerID()+1);//Increase the Player ID
		cout << "The player " << currentState.getCurrentPlayerID() << " starts his round.\n" << endl;

	// If the round changes and the game has ended --> the actual player win the game because all ennemies MobileEntity are dead
	} else if(roundChange && gameEnd){
		cout << "End of the game !" << endl;

		for (unsigned int i = 0; i < currentState.getPlayerList().size(); i++){
			if (currentState.getPlayerList()[i]->getId() == currentState.getCurrentPlayerID()){
				cout<<"The player "<< currentState.getPlayerList()[i]->getName()<<" win the game!!!"<<endl;
			}
		}
		
		roundChange=false;
	}else if(roundChange && !gameEnd){
		cout << "Round has ended.\n" << endl;
		currentState.setRound(currentState.getRound() + 1);
		changeRound=true;
	}
	
	return roundChange;
}

/** Sets or resets data to start a new round
 * 
 */
void Engine::checkRoundStart(){
	if (changeRound == true){
	
		// Change the current player
		currentState.setCurrentPlayerID(1);//Reset player ID to "1"=> first player
		cout << "\t\t--- Round " << currentState.getRound() << " ---\n" << endl;
		
		// For each player
		for (unsigned int i = 0; i < currentState.getPlayerList().size(); i++){
			// For each MobileEntity belonging to each player
			for(unsigned int j = 0;j<currentState.getPlayerList()[i]->getMobileEntityList().size(); j++){

				// For all MobileEntity which do not belong to the currentPlayer and which are not DEAD
				if (currentState.getPlayerList()[i]->getMobileEntityList()[j]->getStatus()!= DEAD ){
					// Reset Status to Available
					currentState.getPlayerList()[i]->getMobileEntityList()[j]->setStatus(AVAILABLE);
					
					// Reset movement points for each units
					if (currentState.getPlayerList()[i]->getMobileEntityList()[j]->getEntityId() == KNIGHT){
						currentState.getPlayerList()[i]->getMobileEntityList()[j]->setMovementRange(2);
						currentState.getPlayerList()[i]->getMobileEntityList()[j]->setMovementLeft(2);

					}
					else if(currentState.getPlayerList()[i]->getMobileEntityList()[j]->getEntityId() == TROLL) {
						currentState.getPlayerList()[i]->getMobileEntityList()[j]->setMovementRange(3);
						currentState.getPlayerList()[i]->getMobileEntityList()[j]->setMovementLeft(3);

					}else if(currentState.getPlayerList()[i]->getMobileEntityList()[j]->getEntityId() == MAGE) {
						currentState.getPlayerList()[i]->getMobileEntityList()[j]->setMovementRange(4);
						currentState.getPlayerList()[i]->getMobileEntityList()[j]->setMovementLeft(4);

					}	
				}
				
			}
		}
		changeRound = !changeRound;
	}
}

/** Check if the game end or not
 * 
 */
bool Engine::checkGameEnd(){
	bool gameEnd = true;
	int currentPlayerID=currentState.getCurrentPlayerID();

	// For each player
	for (unsigned int i = 0; i < currentState.getPlayerList().size(); i++){
		// For each MobileEntity belonging to each player
		for(unsigned int j = 0;j<currentState.getPlayerList()[i]->getMobileEntityList().size(); j++){
			// As long as another player has a MobileEntity alive the game isn't finished
			if(currentState.getPlayerList()[i]->getId()!=currentPlayerID){
				if(currentState.getPlayerList()[i]->getMobileEntityList()[j]->getStatus()!=DEAD){

					//cout<<"The player "<< currentState.getPlayerList()[i]->getName()<<" win the game!!!"<<endl;
					gameEnd=false;
				}
			}
		}
	}
	return gameEnd;

}


void Engine::engineRenderChanged(EngineRenderEvent& engineRenderEvent, state::State& state, state::Position& position, shared_ptr<state::MobileEntity>& selectedMobileEntity, shared_ptr<state::MobileEntity>& targetMobileEntity){
	switch(engineRenderEvent.getEngineRenderEventID()){
		case ARROW_KEYS:
		{
			Move movement(*selectedMobileEntity, position);//Initialize the movement pointor with the unit to move and the position to reach
			unique_ptr<Command> ptr_move(new Move(movement));
			addCommand(0, move(ptr_move));
			update();
			break;
		}
		case ATTACK:
		{
			Attack attack(*selectedMobileEntity, *targetMobileEntity); //Initialize the Attack constrctor with attacker and target
			unique_ptr<Command> ptr_attack(new Attack(attack));
			addCommand(0, move(ptr_attack));//add to engine commands
			update();// update the engine which will execute the attack and update engine and state
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

/** Read commands from a .txt file and executes them
 * 
 * params : 
 * fileName -> name of the .txt file 
 */

void Engine::replayCommands(std::string fileName){
	cout << "Replay is starting" << endl;

	// Opening the .txt file
	ifstream commandsFile(fileName);
	if (commandsFile){
		Json::Value root;
		Json::Reader reader;
		if(!reader.parse(commandsFile, root)){
			cout 	<< "Failed to parse commands\n" << reader.getFormattedErrorMessages();
		}
		// Closing the file in reading mode
		commandsFile.close();
						
		cout << "Size of the commands table of "<< fileName << " : " << root["tabCommand"].size() << endl;
						
		// Converting commands from Json to objects
		for (unsigned int i = 0; i < root["tabCommand"].size(); i++){
			// Move case
			if(root["tabCommand"][i]["id"].asUInt() == 1){
				Position destination(root["tabCommand"][i]["xDestination"].asUInt(),root["tabCommand"][i]["yDestination"].asUInt());
				
				Move movement(*currentState.getMobileEntity(root["tabCommand"][i]["xSelectyedUnit"].asUInt(),root["tabCommand"][i]["ySelectyedUnit"].asUInt()), destination);
		
				unique_ptr<Command> ptr_move(new Move(movement));
				addCommand(0, move(ptr_move));
				update();

				if(checkRoundEnd()){
					cout<<"Round  change"<<endl;
					checkRoundStart();
				}
			}

			// Attack case
			else if(root["tabCommand"][i]["id"].asUInt() == 2){
				Attack attack(*currentState.getMobileEntity(root["tabCommand"][i]["xAttacker"].asUInt(),root["tabCommand"][i]["yAttacker"].asUInt()),*currentState.getMobileEntity(root["tabCommand"][i]["xTarget"].asUInt(),root["tabCommand"][i]["yTarget"].asUInt()));
								
				unique_ptr<Command> ptr_attack (new Attack(attack));
				addCommand(0, move(ptr_attack));
				update();

				if(checkRoundEnd()){
					cout<<"Round  change"<<endl;
					checkRoundStart();
				}
			}

			// End entity round case
			else if(root["tabCommand"][i]["id"].asUInt() == 3){
				EndEntityRound endEntityround(*currentState.getMobileEntity(root["tabCommand"][i]["xSelectedUnit"].asUInt(),root["tabCommand"][i]["ySelectedUnit"].asUInt()));
					
				unique_ptr<Command> ptr_endEntityRound (new EndEntityRound(endEntityround));
				addCommand(0, move(ptr_endEntityRound));
				update();

				if(checkRoundEnd()){
					cout<<"Round  change"<<endl;
					checkRoundStart();
				}
			}
			else{
				cout << "The command " << i << " is unknown" << endl;
			}						
		}								
	}				
	else{
		cerr << "Unable to open the commands file (read)" << endl;
	}							
	cout << "The replay has ended" << endl;
}

//	Getters and Setters

State& Engine::getState(){
	return currentState;
}

map<int, unique_ptr<Command>>& Engine::getCurrentCommands(){
	return currentCommands;
}

bool Engine::getChangeRound (){
	return changeRound;
}

bool Engine::getStop (){
	return stop;
}

Json::Value Engine::getRecord(){
	return record;
}

void Engine::setCurrentState (state::State currentState){
	this->currentState=currentState;
}

void Engine::setCurrentCommands (std::map<int,std::unique_ptr<Command>> currentCommands){
	this->currentCommands=move(currentCommands);
}

void Engine::setChangeRound (bool changeRound){
	this->changeRound=changeRound;
}

void Engine::setStop (bool stop){
	this->stop=stop;
}

//	Destructor

Engine::~Engine (){

}

