#include "../engine.h"
#include </home/ensea/plt/src/client/render.h>
#include "../state.h"
#include <iostream>
#include <unistd.h>

using namespace state;
using namespace engine;
using namespace render;
using namespace std;

//Constructor
Engine::Engine () : currentState(){
	changeRound = false;

}

//Return a pointor on the state attribut initialized in the Engine
state::State& Engine::getState (){
	state::State& ptrState=currentState;
	return ptrState;
}

//Add all the command POINTOR in a associative list
void Engine::addCommand (int priority, std::unique_ptr<Command> ptr_cmd){
	currentCommands[priority]=move(ptr_cmd);
}

//Update : Exécute all the currentCommands tabs elements
void Engine::update (){
	StateEvent stateEvent(PLAYERCHANGE);

	map<int, std::unique_ptr<Command>>::iterator it;

    //execute each commands of the currentCommands tab
	for(size_t i=0; i<currentCommands.size();i++){
			currentCommands[i]->execute(currentState);
			currentState.notifyObservers(stateEvent, currentState); //notify the state which will notify render
			sleep(2);
	}

    //Erase all the commands which were executed
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



//Destructor
Engine::~Engine (){
}

