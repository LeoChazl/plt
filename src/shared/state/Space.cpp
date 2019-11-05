#include "../state.h"

using namespace state;
using namespace std;

// Constructors

Space::Space(){

}

Space::Space (int codeTuile){
    this->codeTuile=codeTuile;
}

// Function

bool const Space::isSpace(){
    return true;
}