#include "../state.h"

using namespace state;
using namespace std;

// Constructors
Knight::Knight() : MobileEntity(18,10,100,2,35,15,100,AVAILABLE,LEFT){

}

Knight::Knight(int x, int y) : MobileEntity(x,y,100,2,35,15,100,AVAILABLE,LEFT){
    
}

// Getter

EntityId Knight::getEntityId(){
    return KNIGHT;
}