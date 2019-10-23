#include "../state.h"

using namespace state;
using namespace std;

// Constructor

State::State(){
    round=1;
    level=1;
    EntityMap entityMap(1);
    Cursor cursor;
    endGame=false;
}

// Functions

/** Delete the player with the corresponding id
 * 
 * param :
 * player -> the player to delete from the player list
 */
void State::deletePlayer(Player& player){
    for(unsigned int i=0; i<playerList.size(); i++){
        if(playerList[i]->getId() == player.getId()){
            playerList.erase(playerList.begin() + i);
        }
    }
}

/** Initialize the players for level 1
 */
bool State::initPlayers(){
    shared_ptr<Player> ptrPlayer1(new Player(1));
    playerList.push_back(ptrPlayer1);

    shared_ptr<Player> ptrPlayer2(new Player(2));
    playerList.push_back(ptrPlayer2);

    return true;
}

// Getters

int State::getRound(){
    return round;
}

int State::getLevel(){
    return level;
}

EntityMap& State::getEntityMap(){
    return map;
}

vector<shared_ptr<Player>>& State::getPlayerList(){
    return playerList;
}

Cursor& State::getCursor(){
    return cursor;
}

bool State::getEndGame(){
    return endGame;
}

// Setters

void State::setRound(int round){
    this->round=round;
}

void State::setLevel(int level){
    this->level=level;
}

void State::setEndGame(bool endGame){
    this->endGame=endGame;
}

// Destructor

State::~State(){

}