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
			//currentCommands[i]->execute(currentState);
			currentState.notifyObservers(stateEvent, currentState); // Notify the state which will notify render
			sleep(2);
	}

    // Erase all the commands which were executed
	for(it=currentCommands.begin(); it!=currentCommands.end(); it++){
		currentCommands.erase(it);
	}
}


/*bool Engine::checkRoundEnd(){
	bool roundChange = true;
	bool gameEnd = true;
    int playerId= currentState.getPlayerList()[0]->getId();
	
	for (unsigned int i = 0; i < currentState.getPlayerList().size(); i++){
        int playerId= currentState.getPlayerList()[i]->getId();
        for(unsigned int j = 0 )
		if (currentState.getPlayerList()[i]->getCamp() == joueurActif){
			//countJoueurActif = countJoueurActif + 1;
			if (currentState.getPlayerList()[i]->getMobileEntityList->getStatut() != MORT ){
				if (etatActuel.getPersonnages()[i]->getStatut() != ATTENTE){
					tourChange = false;
				}
			}
	
		}
		
		
		// Si tous les personnages du joueur non actif ne sont pas morts, la partie n'est pas terminee
		else{
			if (etatActuel.getPersonnages()[i]->getStatut() != MORT ){
				partieFinie = false;
			}		
		}
	}

	
	if (partieFinie && tourChange){
		cout << "\tPartie Terminee !" << endl;
		etatActuel.setFin(partieFinie);
		//if (countJoueurActif == 0){							 A MODIFIER}
		if (joueurActif){
			cout << "\tL'armee bleue a gagne !" << endl;
		}
		else {
			cout << "\tL'armee rouge a gagne !" << endl;
		}
		tourChange = false;
	}
		
	else if (tourChange && !partieFinie){
		cout << "\t\t--- Tour Terminé. ---\n" << endl;
		etatActuel.setTour(etatActuel.getTour()+1);
	}
	
	changementTour = tourChange;
	
	return tourChange;

}*/


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

