#include "../engine.h"
#include "../state.h"
#include "../ai.h"
#include <iostream>
#include <unistd.h>

using namespace state;
using namespace engine;
using namespace std;
using namespace ai;

// Constructor
AI::AI():artificialIntelligenceID(artificialIntelligenceID){

}

// Getter and Setter
int AI::getArtificialIntelligenceID(){
    return artificialIntelligenceID;
}

void setArtificialIntelligenceID(int artificialIntelligenceID){
    artificialIntelligenceID=artificialIntelligenceID;
}

AI::~AI(){
    
}

