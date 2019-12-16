#include "../engine.h"
#include "../state.h"
#include <stdio.h>
#include <iostream>
#include <unistd.h>

using namespace engine;
using namespace state;
using namespace std;

// Constructor

Move::Move(state::MobileEntity& selectedUnit, state::Position& destination): selectedUnit(selectedUnit), destination(destination){
    
}

// Function

void Move::execute(state::State& state){
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

    cout << "The " << entityName << " will move or try to move." << endl;

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
                if(destination.getX()>selectedUnit.getX()){
                    selectedUnit.setDirection(RIGHT);
                }
                else if(destination.getX()<selectedUnit.getX()){
                    selectedUnit.setDirection(LEFT);
                }
                else if(destination.getY()>selectedUnit.getY()){
                    selectedUnit.setDirection(DOWN);
                }
                else{
                    selectedUnit.setDirection(UP);
                }
                selectedUnit.setX(destination.getX());
                selectedUnit.setY(destination.getY());
                selectedUnit.setMovementLeft(selectedUnit.getMovementLeft()-1);
                state.getCursor().setX(destination.getX());
                state.getCursor().setY(destination.getY());

                shared_ptr<Player> ownerPlayer = state.getPlayer(selectedUnit.getPlayerId());

                cout << "The " << entityName << " of " << ownerPlayer->getName() << " moved to (" << destination.getX() << "," << destination.getY() << ") and has " << selectedUnit.getMovementLeft() << " movements left.\n" << endl;
                usleep(waitingTime);
            } else {
                cout << "The unit cannot move to the destination :(" << destination.getX()<< ", " << destination.getY() << ").\n" << endl;
                usleep(waitingTime);
            }
        } else {
            cout<<"LEFT MOVEMENT POINTS: "<<selectedUnit.getMovementLeft()<<endl;
            cout << "The " << entityName << " doesn't have any movement left.\n" << endl;
            usleep(waitingTime);
        }
    } else {
        cout << "The " << entityName << " is not allowed to move.\n" << endl;
        usleep(waitingTime);
    }
}