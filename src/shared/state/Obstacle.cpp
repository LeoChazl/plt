#include "../state.h"

using namespace state;
using namespace std;

// Constructor

Obstacle::Obstacle(){

}

Obstacle::Obstacle(int codeTuile){
    this->codeTuile=codeTuile;
}

// Function

bool const Obstacle::isSpace(){
    return false;
}

int Obstacle::getCodeTuile (){
    return codeTuile;
}
