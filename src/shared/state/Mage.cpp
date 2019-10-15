#include "../state.h"

using namespace state;
using namespace std;

// Constructors

Mage::Mage() : MobileEntity(20,20,70,3,15,5,100,AVAILABLE,DOWN){
    mana=100;
    manaMax=100;
    spellDamage=45;
    spellAttackRange=2;
}

Mage::Mage(int x, int y) : MobileEntity(x,y,70,3,45,5,100,AVAILABLE,DOWN){
    mana=100;
    manaMax=100;
    spellDamage=45;
    spellAttackRange=2;
}

Mage::Mage(int x, int y, float mana, float manaMax, float spellDamage, int spellAttackRange) : MobileEntity(x,y,70,3,45,5,100,AVAILABLE,DOWN){
    this->mana=mana;
    this->manaMax=manaMax;
    this->spellDamage=spellDamage;
    this->spellAttackRange=spellAttackRange;
}

// Functions

/** Mage casts a ranged attack
 * 
 * param : 
 * target -> target unit who'll take the damage
 */
void Mage::castSpell (MobileEntity& target){
    target.receiveDamage(spellDamage);
}

// Getters

float Mage::getMana (){
    return mana;
}

float Mage::getManaMax (){
    return manaMax;
}

float Mage::getSpellDamage(){
    return spellDamage;
}

int Mage::getSpellAttackRange(){
    return spellAttackRange;
}

EntityId Mage::getEntityId (){
    return MAGE;
}

// Setters

void Mage::setMana(float mana){
    this->mana=mana;
}