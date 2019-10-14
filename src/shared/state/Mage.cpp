#include "../state.h"

using namespace state;
using namespace std;

//Constructor
Mage::Mage(){
    mana=100;
    manaMax=100;
}

//Function
void Mage::castSpell (shared_ptr<MobileEntity> target){
    float targetHealth=target->getHealth();
    targetHealth-=damage;

    if((target->getMaxHealth())<0){// If the target Health is left than "0" after the attack
        target->setHealth(0);
    }else{
        target->setHealth(targetHealth);
    }
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

