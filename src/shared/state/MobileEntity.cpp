#include "MobileEntity.h"
#include "EntityMap.h"

using namespace state;
using namespace std;

//Constructeur
MobileEntity::MobileEntity(){
    health=100;
    movementRange=1;
    attackRange=1;
    damage=10;
    armor=1;
    maxHealth=100;
    x=0;
    y=0;
}

MobileEntity::MobileEntity (float health, int movementRange, int attackRange,float damage, float armor, float maxHealth, EntityId entityId, Status status, Direction direction){
    this->health=health;
    this->movementRange=movementRange;
    this->attackRange=attackRange;
    this->damage=damage;
    this->armor=armor;
    this->maxHealth=maxHealth;
    this->entityId=entityId;
    this->status=status;
    this->direction=direction;
}


//Function
bool const MobileEntity::isStatic(){
    return false;
}

float MobileEntity::receiveDamage (float damage){
    health-=damage;
    return health;
}

void MobileEntity::physicalAttack (std::shared_ptr<MobileEntity> target){
    float targetHealth=target->getHealth();
    targetHealth-=damage;

    if((target->getMaxHealth())<0){// If the target Health is left than "0" after the attack
        target->setHealth(0);
    }else{
        target->setHealth(targetHealth);
    }
}


void MobileEntity::move (Direction direction){ //A compléter avec Map
    
    int mapWidth=25;
    int mapHeight=25;

    //UP
    if((direction==1)&(x>=0))
    {
        x--;
    }else{
        x=0;
    }
    
    //RIGHT
    if((direction==2)&(y<=mapWidth))
    {
        y++;
    }else{
        y=mapHeight;
    }
    
    //DOWN
    if((direction==3)&(x<=mapHeight))
    {
        x++;
    }else{
        x=mapHeight;
    }

    //LEFT
    if((direction==4)&(x>=0))
    {
        y--;
    }else{
        y=0;
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