#include "../state.h"

using namespace state;
using namespace std;

// Constructors
Mage::Mage() : MobileEntity(10,11,0,70,4,4,45,2,5,100,AVAILABLE,DOWN){
    mana=100;
    manaMax=100;
}

Mage::Mage(int playerId) : MobileEntity(10,11,playerId,70,4,4,45,2,5,100,AVAILABLE,DOWN){
    mana=100;
    manaMax=100;
}

Mage::Mage(int x, int y, int playerId) : MobileEntity(x,y,playerId,70,4,4,45,2,5,100,AVAILABLE,DOWN){
    mana=100;
    manaMax=100;
}

Mage::Mage(int x, int y, int playerId, float mana, float manaMax) : MobileEntity(x,y,playerId,70,4,4,45,2,5,100,AVAILABLE,DOWN){
    this->mana=mana;
    this->manaMax=manaMax;
}

// Getters

float Mage::getMana (){
    return mana;
}

float Mage::getManaMax (){
    return manaMax;
}

EntityId Mage::getEntityId (){
    return MAGE;
}

// Setters

void Mage::setMana(float mana){
    this->mana=mana;
}