#include "../state.h"

using namespace state;
using namespace std;

// Constructors
Knight::Knight() : MobileEntity(11,8,100,2,35,15,100,AVAILABLE,LEFT){
    srand(time(0));
    int x = rand() % 14;
    int y = rand() % 4;
    this->setX(this->getX() + x);
    this->setY(this->getY() + y);
}

Knight::Knight(int x, int y) : MobileEntity(x,y,100,2,35,15,100,AVAILABLE,LEFT){
    
}

// Getter

EntityId Knight::getEntityId(){
    return KNIGHT;
}