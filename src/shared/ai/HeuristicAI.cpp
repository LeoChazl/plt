#include "../engine.h"
#include "../state.h"
#include "../ai.h"
#include <iostream>
#include <unistd.h>

using namespace state;
using namespace engine;
using namespace std;
using namespace ai;

//Constructor
HeuristicAI::HeuristicAI(int AiID){
        artificialIntelligenceID=AiID;
}

// Functions 

void HeuristicAI::run (engine::Engine& engine){
    

}

std::vector<state::Position> HeuristicAI::algorithmAStar (engine::Engine& engine, state::Position start, state::Position goal){
    vector<Position> listPosition;
    return listPosition;
}