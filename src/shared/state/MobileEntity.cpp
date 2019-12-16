#include "../state.h"
#include <iostream>
#include <tgmath.h>

using namespace state;
using namespace std;

// Constructors

MobileEntity::MobileEntity():Position(0,6)
{
    health=100;
    movementRange=1;
    movementLeft=1;
    damage=30;
    attackRange=1;
    armor=10;
    maxHealth=100;
    status=AVAILABLE;
    direction=DOWN;
}

MobileEntity::MobileEntity (int x, int y, int playerId, float health, int movementRange, int movementLeft, float damage, int attackRange, float armor, float maxHealth, Status status, Direction direction):Position(x,y)
{
    this->playerId=playerId;
    this->health=health;
    this->movementRange=movementRange;
    this->movementLeft=movementLeft;
    this->damage=damage;
    this->attackRange=attackRange;
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
    health=roundf(health-(damage-damage/armor));

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
void MobileEntity::attack (MobileEntity& target){
    target.receiveDamage(damage);
}

/** Move the unit and verify that it doesn't go over the boundaries of the map
 * 
 * param : 
 * state -> game actual state containing the map
 * direction -> direction of the movement
 */
void MobileEntity::move (State& state, Direction direction){
    int mapWidth=state.getEntityMap().getWidth();
    int mapHeight=state.getEntityMap().getHeight();

    switch(direction){
        case UP: 
            if(x>0){
                x--;
                this->direction=direction;
                break;
            }else{
                x=0;
                break;
            }
        case RIGHT:
            if(y<mapWidth-1){
                y++;
                this->direction=direction;
                break;
            }else{
                y=mapWidth-1;
                break;
            }
        case DOWN:
            if(x<mapHeight-1){
                x++;
                this->direction=direction;
                break;
            }else{
                x=mapHeight-1;
                break;
            }
        case LEFT:
            if(y>0){
                y--;
                this->direction=direction;
                break;
            }else{
                y=0;
                break;
            }
        default:
            break;
    }
}

/** Create the list of allowed position to move for a mobileEntity
 * 
 */ 
vector<Position> MobileEntity::allowedMove(State& state){
    vector<Position> listAllowedMove;
    Position currentPosition;

    for(int i=x-1;i<=x+1;i++){
        for(int j=y-1;j<=y+1;j++){
            // Test the border
            if(i>=0 && j>=0 && i<state.getEntityMap().getWidth() && j<state.getEntityMap().getHeight()){
                // Test the nearby cases (within 1 range) if it's open and not an obstacle
                if((abs(i-x)+abs(j-y))<=1 && !state.isOccupied(i,j) && state.getEntityMap().getMapArray()[j][i]->isSpace()){
                    currentPosition.setX(i);
                    currentPosition.setY(j);
                    listAllowedMove.push_back(currentPosition);
                }
            }
        }
    }

    return listAllowedMove;
}

/**Create the list of allowed position to attack for a mobileEntity
 * 
 */
vector<Position> MobileEntity::allowedAttack(State& state){
    vector<Position> listAllowedAttack;
    Position currentPosition;

    for(int i=x-attackRange;i<=x+attackRange;i++){
        for(int j=x-attackRange;j<=y+attackRange;j++){
            // Test the border
            if(i>=0 && j>=0 && i<state.getEntityMap().getWidth() && j<state.getEntityMap().getHeight()){
                // Test in the attack range and unit presence
                if(state.isOccupied(i,j)){
                    // Test if unit is an enemy
                    if(playerId != state.getMobileEntity(i,j)->getPlayerId()){
                        currentPosition.setX(i);
                        currentPosition.setY(j);
                        listAllowedAttack.push_back(currentPosition);
                    }
                }
            }
        }
    }

    return listAllowedAttack;
}

// Getters

int MobileEntity::getPlayerId(){
    return playerId;
}

float MobileEntity::getHealth(){
    return health;
}

int MobileEntity::getMovementRange(){
    return movementRange;
}

int MobileEntity::getMovementLeft(){
    return movementLeft;
}

float MobileEntity::getDamage(){
    return damage;
}

int MobileEntity::getAttackRange(){
    return attackRange;
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

void MobileEntity::setPlayerId(int playerId){
    this->playerId=playerId;
}

void MobileEntity::setHealth(float health){
    this->health=health;
}

void MobileEntity::setMovementRange(int movementRange){
    this->movementRange=movementRange;
}

void MobileEntity::setMovementLeft(int movementLeft){
    this->movementLeft=movementLeft;
}

void MobileEntity::setDamage(float damage){
    this->damage=damage;
}

void MobileEntity::setAttackRange(int attackRange){
    this->attackRange=attackRange;
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