#include "../engine.h"
#include "../state.h"

using namespace engine;

// Constructor

Move::Move(state::MobileEntity& selectedUnit, state::Position& destination): selectedUnit(selectedUnit), destination(destination){
    id=MOVE;
}

// Function

void Move::execute(state::State& state){

}