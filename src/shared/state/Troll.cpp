#include "../state.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace state;
using namespace std;

// Constructors
Troll::Troll() : MobileEntity(0,8,100,2,35,15,100,AVAILABLE,DOWN){
    srand(time(0));
    int x = rand() % 5;
    int y = rand() % 12;
    this->setX(this->getX() + x);
    this->setY(this->getY() + y);
}

Troll::Troll(int x, int y) : MobileEntity(x,y,100,2,35,15,100,AVAILABLE,DOWN){
    
}

// Getter

EntityId Troll::getEntityId(){
    return TROLL;
}