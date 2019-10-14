#include "Troll.h"

using namespace state;
using namespace std;

Troll::Troll(){

}

EntityId const Troll::getEntityId (){
    return this->entityId;
}

float Troll::attack(shared_ptr<MobileEntity>){ //A compléter en mettant en argument le personnage à attaquer

}