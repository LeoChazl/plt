#include "../state.h"

using namespace state;
using namespace std;

// Constructors

MobileEntity::MobileEntity():Position(6,6)
{
    health=100;
    movementRange=1;
    damage=30;
    armor=10;
    maxHealth=100;
    status=AVAILABLE;
    direction=DOWN;
}

MobileEntity::MobileEntity (int x, int y,float health, int movementRange, float damage, float armor, float maxHealth, Status status, Direction direction):Position(x,y)
{
    this->health=health;
    this->movementRange=movementRange;
    this->damage=damage;
    this->armor=armor;
    this->maxHealth=maxHealth;
    this->status=status;
    this->direction=direction;
}

// Functions

/** Unit takes damage
 * 
 * param :
 * damage -> damage value of the attacking unit
 * 
 * return : new health value
 */
float MobileEntity::receiveDamage (float damage){
    //Damage dealt = damage - reduction from armor
    //health-=damage - (damage/armor);
    health=health-(damage-damage/armor);

    // If health is less than "0" after the attack
    if(health<0){
        health=0;
    }
    return health;
}

/** Unit deals an attack
 * 
 * param :
 * target -> target unit who'll take the damage
 */
void MobileEntity::physicalAttack (MobileEntity& target){
    target.receiveDamage(damage);
}

/** Move the unit and verify that it doesn't go over the boundaries of the map
 * 
 * param : 
 * state -> game actual state containing the map
 * direction -> direction of the movement
 */
void MobileEntity::move (State& state, Direction direction){
    int mapWidth=state.getMap().getWidth();
    int mapHeight=state.getMap().getHeight();

    switch(direction){
        case UP: 
            if(x>0){
                x--;
                this->direction=direction;
            }else
                x=0;
        case RIGHT:
            if(y<mapWidth){
                y++;
                this->direction=direction;
            }else
                y=mapWidth;
        case DOWN:
            if(x<mapHeight){
                x++;
                this->direction=direction;
            }else
                x=mapHeight;
        case LEFT:
            if(y>0){
                y--;
                this->direction=direction;
            }else
                y=0;
    }
}

// Getters

float MobileEntity::getHealth(){
    return health;
}

float MobileEntity::getMovementRange(){
    return movementRange;
}

float MobileEntity::getDamage(){
    return damage;
}

float MobileEntity::getArmor(){
    return armor;
}

float MobileEntity::getMaxHealth(){
    return maxHealth;
}

Status MobileEntity::getStatus(){
    return status;
}

Direction MobileEntity::getDirection(){
    return direction;
}


// Setters

void MobileEntity::setHealth(float health){
    this->health=health;
}

void MobileEntity::setMovementRange(int movementRange){
    this->movementRange=movementRange;
}

void MobileEntity::setDamage(float damage){
    this->damage=damage;
}

void MobileEntity::setArmor(float armor){
    this->armor=armor;
}

void MobileEntity::setMaxHealth(float maxHealth){
    this->maxHealth=maxHealth;
}

void MobileEntity::setStatus(Status status){
    this->status=status;
}

void MobileEntity::setDirection(Direction direction){
    this->direction=direction;
}