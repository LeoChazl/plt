#include "Mage.h"

using namespace state;
using namespace std;

//Constructor
Mage::Mage(){
    this->mana=100;
    this->manaMax=100;
}

//Function
float Mage::castSpell (shared_ptr<MobileEntity>){

}

//Getters and Setters
float Mage::getMana (){
    return mana;
}

EntityId const Mage::getEntityId (){
    return entityId;
}

void Mage::setMana (float mana){
    this->mana=mana;
}

