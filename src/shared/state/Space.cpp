#include "../state.h"

using namespace state;
using namespace std;

// Constructor

Space::Space(){

}

Space::Space (SpaceTypeID SpaceID){
    this->SpaceID=SpaceID;
}

// Function

bool const Space::isSpace(){
    return true;
}

SpaceTypeID Space::getSpaceTypeID(){
    return SpaceID;
}