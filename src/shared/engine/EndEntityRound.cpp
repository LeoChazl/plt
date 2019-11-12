#include "../engine.h"
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

// Constructor

EndEntityRound::EndEntityRound(state::MobileEntity& selectedUnit): selectedUnit(selectedUnit){

}

// Function

void EndEntityRound::execute(state::State& state){
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
		cout << entityName << " finished his round." << endl;
	}
	else if(selectedUnit.getStatus()==WAITING){
		cout << entityName << " has already finished his round." <<endl; 
	}
}