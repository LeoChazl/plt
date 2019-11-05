#include "../engine.h"
#include "../state.h"
#include <iostream> 
#include <unistd.h>
#include <stdlib.h>

using namespace engine;
using namespace state;
using namespace std;


Attack::Attack (state::MobileEntity& attacker, state::MobileEntity& target): attacker(attacker),target(target)
{
}


void Attack::execute (state::State& state){
    bool attackIsPossible=false;
    std::vector<state::Position> listeCoordAtt=attacker.allowedAttack(state);

    if(attacker.getStatus()!=WAITING &&attacker.getStatus()!=DEAD){


    }else if(attacker.getStatus()==WAITING){
        cout<<"Ce personnage ne peut plus attaquer-->raison: Son tour d'actions est terminé "<<endl;
    }
}
