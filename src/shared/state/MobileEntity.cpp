#include "MobileEntity.h"

using namespace state;
using namespace std;

//Constructeur
/*MobileEntity::MobileEntity (float health = 0, int movementRange = 0, int attackRange = 0, float damage = 0, float armor = 0, float maxHealth = 100, int x = 0, int y = 0)
{
    this->health=health;
    this->movementRange=movementRange;
    this->attackRange=attackRange;
    this->damage=damage;
    this->armor=armor;
    this->maxHealth=maxHealth;
    this->x=x;
    this->y=y;
}*/



//Function
bool const MobileEntity::isStatic(){
    return false;
}

float MobileEntity::receiveDamage (float damage){
    health-=damage;
    return health;
}

void MobileEntity::move (Direction direction){ //A compléter avec Map
    if(direction==1)
    {

    }
    else if(direction==2)
    {

    }
    else if(direction==3)
    {

    }
    else if(direction==4)
    {

    }
}

//Getter
float MobileEntity::getHealth(){
    return health;
}

float MobileEntity::getMovementRange(){
    return movementRange;
}

float MobileEntity::getAttackRange(){
    return attackRange;
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


//Setters

void MobileEntity::setHealth(float health){
    this->health=health;
}

void MobileEntity::setMovementRange(int movementRange){
    this->movementRange=movementRange;
}

void MobileEntity::setAttackRange(int attackRange){
    this->attackRange=attackRange;
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

void MobileEntity::setEntityId(EntityId entityId){
    this->entityId=entityId;
}

void MobileEntity::setStatus(Status status){
    this->status=status;
}

void MobileEntity::setDirection(Direction direction){
    this->direction=direction;
}