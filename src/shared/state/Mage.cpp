#include "../state.h"

using namespace state;
using namespace std;

// Constructors

Mage::Mage(){
    MobileEntity(20,20,70,3,15,5,100,MAGE,AVAILABLE,DOWN);
    mana=100;
    manaMax=100;
    spellDamage=45;
    spellAttackRange=2;
}

Mage::Mage(int x, int y){
    MobileEntity(x,y,70,3,45,5,100,MAGE,AVAILABLE,DOWN);
    mana=100;
    manaMax=100;
    spellDamage=45;
    spellAttackRange=2;
}

// Function

/** Mage casts a ranged attack
 * 
 * param : 
 * target -> target unit who'll take the damage
 */
void Mage::castSpell (MobileEntity& target){
    float targetHealth=target.getHealth();
    targetHealth=target.receiveDamage(spellDamage);

    if(targetHealth<0){// If the target health is less than "0" after the attack
        target.setHealth(0);
    }else{
        target.setHealth(targetHealth);
    }
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