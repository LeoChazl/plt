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

/*void Engine::checkRoundStart(){
	if (changementTour == true){
	
		joueurActif = !joueurActif;
		cout << "\t-> Changement de joueur <-" << endl;
		cout << "\t\t--- Tour " << etatActuel.getTour() << " ---\n" << endl;
		
		for (unsigned int i = 0; i < etatActuel.getPersonnages().size(); i++){
		
			// Personnages du joueur qui termine son tour et qui ne sont pas morts
			if (etatActuel.getPersonnages()[i]->getCamp() != joueurActif && etatActuel.getPersonnages()[i]->getStatut() != MORT){
				// Reinitialisation du statut
				etatActuel.getPersonnages()[i]->setStatut(DISPONIBLE);
				
				//Reinitialisation des points de mouvement
				if (etatActuel.getPersonnages()[i]->getType() != CHEVALIER){
					etatActuel.getPersonnages()[i]->setChampMove(3);
				}
				else {
					etatActuel.getPersonnages()[i]->setChampMove(5);
				}	
			}
			
			// Regain de PV pour les personnages sur des maisons et fortersse en debut de tour
			else if (etatActuel.getPersonnages()[i]->getCamp() == joueurActif) {
				TerrainPraticable& refTerrainP = static_cast<TerrainPraticable&>(*etatActuel.getGrille()[etatActuel.getPersonnages()[i]->getPosition().getY()][etatActuel.getPersonnages()[i]->getPosition().getX()]);
				
				if(refTerrainP.getTerrainPraticableID() == MAISON || refTerrainP.getTerrainPraticableID() == FORTERESSE){
					etatActuel.getPersonnages()[i]->getStatistiques().setPV(etatActuel.getPersonnages()[i]->getStatistiques().getPV() + refTerrainP.getStatistiques().getPV());
					// Affichage
					cout << "+ " << etatActuel.getPersonnages()[i]->getNom() << " récupère " ;
					cout << refTerrainP.getStatistiques().getPV() << " PV.";
					cout << " (" << etatActuel.getPersonnages()[i]->getStatistiques().getPV() << " PV au total). +" << endl;
				}
			}
		}
		
		changementTour = !changementTour;
	}
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

