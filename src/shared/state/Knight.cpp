#include "../state.h"

using namespace state;
using namespace std;

// Constructors
Knight::Knight() : MobileEntity(3,4,0,100,2,2,35,1,15,100,AVAILABLE,LEFT){

}

Knight::Knight(int playerId) : MobileEntity(3,4,playerId,100,2,2,35,1,15,100,AVAILABLE,LEFT){

}

Knight::Knight(int x, int y, int playerId) : MobileEntity(x,y,playerId,100,2,2,35,1,15,100,AVAILABLE,LEFT){
    
}

// Getter

EntityId Knight::getEntityId(){
    return KNIGHT;
}