#include "../state.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace state;
using namespace std;

// Constructors
Troll::Troll() : MobileEntity(0,7,0,100,3,35,1,15,100,AVAILABLE,DOWN){

}

Troll::Troll(int playerId) : MobileEntity(0,7,playerId,100,3,35,1,15,100,AVAILABLE,DOWN){
    
}

Troll::Troll(int x, int y, int playerId) : MobileEntity(x,y,playerId,100,3,35,1,15,100,AVAILABLE,DOWN){
    
}

// Getter

EntityId Troll::getEntityId(){
    return TROLL;
}