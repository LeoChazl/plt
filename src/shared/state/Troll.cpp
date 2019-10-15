#include "../state.h"

using namespace state;
using namespace std;

// Constructors

Troll::Troll() : MobileEntity(6,6,100,2,35,15,100,AVAILABLE,DOWN){
    
}

Troll::Troll(int x, int y) : MobileEntity(x,y,100,2,35,15,100,AVAILABLE,DOWN){
    
}

// Getter

EntityId Troll::getEntityId(){
    return TROLL;
}