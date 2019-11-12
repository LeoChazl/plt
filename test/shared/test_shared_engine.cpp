#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include "../../src/shared/engine.h"
#include "../../src/client/render.h"


#include <vector>
#include <unistd.h>


#include <fstream>
#include <iostream>
#include <sstream>


using namespace std;
using namespace state;
using namespace render;
using namespace engine;

namespace sf {
  class RenderWindow;
}


BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
    /*sf::RenderWindow window(sf::VideoMode(1950, 900), "Fire Emblem");
    sf::View view = window.getDefaultView();
    window.setView(view);


    //Implement Engine Constructor
    Engine engine;
    State s;
    //BOOST_CHECK_EQUAL(engine.getState(), s);
    engine.getState().initPlayers();

    StateLayer stateLayer(engine.getState(),window);
    stateLayer.initTextureAreas(engine.getState());

    StateLayer* ptr_stateLayer=&stateLayer;
    engine.getState().registerObserver(ptr_stateLayer);


    // Mage moves
    Position destination1(engine.getState().getPlayerList()[0]->getMobileEntityList()[0]->getX()+1,engine.getState().getPlayerList()[0]->getMobileEntityList()[0]->getY());
    Move deplacement1(*engine.getState().getPlayerList()[0]->getMobileEntityList()[0], destination1);
    unique_ptr<Command> ptr_deplacement1 (new Move(deplacement1));
    engine.addCommand(0, move(ptr_deplacement1));

    
    // Mage moves
    Position destination2(engine.getState().getPlayerList()[0]->getMobileEntityList()[0]->getX()+2,engine.getState().getPlayerList()[0]->getMobileEntityList()[0]->getY());
    Move deplacement2(*engine.getState().getPlayerList()[0]->getMobileEntityList()[0], destination2);
    unique_ptr<Command> ptr_deplacement2 (new Move(deplacement2));
    engine.addCommand(1, move(ptr_deplacement2));

    // Mage attacks Troll
    Position destination3(engine.getState().getPlayerList()[0]->getMobileEntityList()[0]->getX()+3,engine.getState().getPlayerList()[0]->getMobileEntityList()[0]->getY());
    Move deplacement3(*engine.getState().getPlayerList()[0]->getMobileEntityList()[0], destination3);
    unique_ptr<Command> ptr_deplacement3 (new Move(deplacement3));
    engine.addCommand(2, move(ptr_deplacement3));

    Position destination4(engine.getState().getPlayerList()[0]->getMobileEntityList()[0]->getX()+3,engine.getState().getPlayerList()[0]->getMobileEntityList()[0]->getY()+1);
    Move deplacement4(*engine.getState().getPlayerList()[0]->getMobileEntityList()[0], destination4);
    unique_ptr<Command> ptr_deplacement4 (new Move(deplacement4));
    engine.addCommand(3, move(ptr_deplacement4));


    // Mage attack Troll
    Attack attack(*engine.getState().getPlayerList()[0]->getMobileEntityList()[1], *engine.getState().getPlayerList()[1]->getMobileEntityList()[0]);
    unique_ptr<Command> ptr_attack (new Attack(attack));
    engine.addCommand(4, move(ptr_attack));

    engine.update();
    engine.checkRoundEnd();*/

}
