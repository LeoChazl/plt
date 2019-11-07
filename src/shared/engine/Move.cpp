#include "../engine.h"
#include "../state.h"
#include <stdio.h>
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

// Constructor

Move::Move(state::MobileEntity& selectedUnit, state::Position& destination): selectedUnit(selectedUnit), destination(destination){
    
}

// Function

void Move::execute(state::State& state){
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

    cout << "The unit " << entityName << " will move or try to move." << endl;

    bool moveFeasible=false;
    // Unit is ready to move
    if(selectedUnit.getStatus()==AVAILABLE || selectedUnit.getStatus()==SELECTED){
        // Check if unit has still movement left
        cout<<"e1"<<endl;
        if(selectedUnit.getMovementLeft()>0){
            cout<<"e2"<<endl;
            vector<Position> allowedMoveList = selectedUnit.allowedMove(state);

            // Check if the destination is allowed
            cout<<allowedMoveList.size()<<endl;
            for(unsigned int i=0;i<allowedMoveList.size();i++){
                if(allowedMoveList[i].equal(destination)){
                    moveFeasible=true;
                    break;
                }
            }
            cout<<"e3"<<endl;

            // Change the state
            if(moveFeasible){
                cout<<"e5"<<endl;
                selectedUnit.setX(destination.getX());
                selectedUnit.setY(destination.getY());
                selectedUnit.setMovementLeft(selectedUnit.getMovementLeft()-1);

                shared_ptr<Player> ownerPlayer = state.getPlayer(selectedUnit.getPlayerId());

                cout << "The unit " << entityName << " of " << ownerPlayer->getName() << " moved to (" << destination.getX() << "," << destination.getY() << ") and has " << selectedUnit.getMovementLeft() << " movements left.\n" << endl;
            } else {
                cout << "The unit cannot move to the destination.\n" << endl;
            }
        } else {
            cout << "The unit doesn't have any movement left.\n" << endl;
        }
    } else {
        cout << "The unit is not allowed to move.\n" << endl;
    }
}