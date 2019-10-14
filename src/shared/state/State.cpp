#include "state.h"

using namespace state;
using namespace std;

int State::getRound(){
    return round;
}

int State::getLevel(){
    return level;
}

EntityMap State::getMap(){
    return map;
}

vector<shared_ptr<Player>> State::getPlayerList(){
    return playerList;
}

State::~State(){

}