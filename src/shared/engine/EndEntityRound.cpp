#include "../engine.h"
#include <iostream>
#include <unistd.h>

using namespace engine;
using namespace state;
using namespace std;

// Constructor

EndEntityRound::EndEntityRound(state::MobileEntity& selectedUnit): selectedUnit(selectedUnit){

}

// Function

void EndEntityRound::execute(state::State& state){
    int waitingTime=40000;
    string entityName = "";
    switch(selectedUnit.getEntityId()){
        case TROLL: 
            entityName = "troll";
            break;
        case MAGE:
            entityName = "mage";
            break;
        case KNIGHT:
            entityName = "knight";
            break;
    }

	if (selectedUnit.getStatus()!=WAITING && selectedUnit.getStatus()!=DEAD){
		selectedUnit.setStatus(WAITING);
        state.getCursor().setCodeTuile(0);
		cout << "The " << entityName << " finished his round.\n" << endl;
        usleep(waitingTime);
	}
	else if(selectedUnit.getStatus()==WAITING){
		cout << "The " << entityName << " has already finished his round.\n" <<endl;
        usleep(waitingTime);
	}
}