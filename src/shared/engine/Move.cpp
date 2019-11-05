#include "../engine.h"
#include "../state.h"
#include <stdio.h>

using namespace engine;
using namespace state;
using namespace std;

// Constructor

Move::Move(state::MobileEntity& selectedUnit, state::Position& destination): selectedUnit(selectedUnit), destination(destination){
    id=MOVE;
}

// Function

void Move::execute(state::State& state){
    bool moveFeasible=false;
    // Unit is ready to move
    if(selectedUnit.getStatus()==AVAILABLE || selectedUnit.getStatus()==SELECTED){
        // Check if unit has still movement left
        if(selectedUnit.getMovementLeft()>0){
            vector<Position> allowedMoveList = selectedUnit.allowedMove(state);

            // Check if the destination is allowed
            for(unsigned int i=0;i<allowedMoveList.size();i++){
                if(allowedMoveList[i].equal(destination)){
                    moveFeasible=true;
                    break;
                }
            }

            // Change the state
            if(moveFeasible){
                selectedUnit.setX(destination.getX());
                selectedUnit.setY(destination.getY());
                selectedUnit.setMovementLeft(selectedUnit.getMovementLeft()-1);

                //cout << "The unit " << selectedUnit.getEntityId() << " of " << 
            }
        }
    }
}