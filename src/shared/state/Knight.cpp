#include "Knight.h"

using namespace state;
using namespace std;

Knight::Knight(){

}

EntityId const Knight::getEntityId (){
    return this->entityId;
}

float Knight::attack(shared_ptr<MobileEntity>){ //A compléter en mettant en argument le personnage à attaquer
    return 0;
}