#include "../state.h"

using namespace state;
using namespace std;

// Constructors

Obstacle::Obstacle(){

}

Obstacle::Obstacle(int codeTuile){
    this->codeTuile=codeTuile;
}

// Function

bool const Obstacle::isSpace(){
    return false;
}
