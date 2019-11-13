#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include "../../src/shared/engine.h"
#include "../../src/client/render.h"


#include <vector>
#include <unistd.h>


#include <fstream>
#include <iostream>
#include <sstream>

#define WINVER 0x0500



using namespace std;
using namespace state;
using namespace render;
using namespace engine;

namespace sf {
  class RenderWindow;
}


BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
    sf::RenderWindow window(sf::VideoMode(1950, 900), "Fire Emblem");
    sf::View view = window.getDefaultView();
    window.setView(view);
    sf::Event event;


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
   BOOST_CHECK_EQUAL(engine.checkRoundEnd(),false);
   engine.ScreenRefresh();
   engine.checkRoundStart();

    BOOST_CHECK_EQUAL(engine.getState().verifyIsSelected(),false);

    //Move the cursor without selecting a Unit
    event.type=sf::Event::KeyPressed;
    event.key.code=sf::Keyboard::Left;
    event.KeyPressed;
    window.pollEvent(event);
    stateLayer.inputManager(event, engine.getState());
    engine.ScreenRefresh();
    event.KeyReleased;
    usleep(100);

/********************************************************************/
    BOOST_CHECK_EQUAL(engine.getState().verifyIsSelected(),false);

    //Move the cursor without selecting a Unit
    event.type=sf::Event::KeyPressed;
    event.key.code=sf::Keyboard::Key::Left;
    event.KeyPressed;
    window.pollEvent(event);
    stateLayer.inputManager(event, engine.getState());
    engine.ScreenRefresh();
    event.KeyReleased;
    usleep(100);

    sf::Event event2;
    event2.type=sf::Event::KeyPressed;
    event2.key.code=sf::Keyboard::Key::Right;
    event2.KeyPressed;
    window.pollEvent(event);
    stateLayer.inputManager(event2, engine.getState());
    engine.ScreenRefresh();
    event2.KeyReleased;
    usleep(100);

    event.type=sf::Event::KeyPressed;
    event.key.code=sf::Keyboard::Key::Right;
    event.KeyPressed;
    window.pollEvent(event);
    stateLayer.inputManager(event, engine.getState());
    engine.ScreenRefresh();
    event.KeyReleased;
    usleep(100);

    event.type=sf::Event::KeyPressed;
    event.key.code=sf::Keyboard::Key::Up;
    event.KeyPressed;
    window.pollEvent(event);
    stateLayer.inputManager(event, engine.getState());
    engine.ScreenRefresh();
    event.KeyReleased;
    usleep(100);

    event.type=sf::Event::KeyPressed;
    event.key.code=sf::Keyboard::Key::Down;
    event.KeyPressed;
    window.pollEvent(event);
    stateLayer.inputManager(event, engine.getState());
    engine.ScreenRefresh();
    event.KeyReleased;
    usleep(100);

    //Select a Unit to move
    event.type=sf::Event::KeyPressed;
    event.key.code=sf::Keyboard::Key::Return;
    event.KeyPressed;
    window.pollEvent(event);
    stateLayer.inputManager(event, engine.getState());
    engine.ScreenRefresh();
    event.KeyReleased;
    usleep(100);

    //MOve the unit
    event.type=sf::Event::KeyPressed;
    event.key.code=sf::Keyboard::Key::Left;
    event.KeyPressed;
    stateLayer.inputManager(event, engine.getState());
    engine.ScreenRefresh();
    event.KeyReleased;
    usleep(100);

    event.type=sf::Event::KeyPressed;
    event.key.code=sf::Keyboard::Key::Right;
    event.KeyPressed;
    stateLayer.inputManager(event, engine.getState());
    engine.ScreenRefresh();
    event.KeyReleased;
    usleep(100);

    event.type=sf::Event::KeyPressed;
    event.key.code=sf::Keyboard::Key::Right;
    event.KeyPressed;
    stateLayer.inputManager(event, engine.getState());
    engine.ScreenRefresh();
    event.KeyReleased;
    usleep(100);

    event.type=sf::Event::KeyPressed;
    event.key.code=sf::Keyboard::Key::Up;
    event.KeyPressed;
    stateLayer.inputManager(event, engine.getState());
    engine.ScreenRefresh();
    event.KeyReleased;
    usleep(100);

    event.type=sf::Event::KeyPressed;
    event.key.code=sf::Keyboard::Key::Down;
    event.KeyPressed;
    stateLayer.inputManager(event, engine.getState());
    engine.ScreenRefresh();
    event.KeyReleased;
    usleep(100);

    //End round for the unit
    event.type=sf::Event::KeyPressed;
    event.key.code=sf::Keyboard::Key::E;
    event.KeyPressed;
    stateLayer.inputManager(event, engine.getState());
    engine.ScreenRefresh();
    event.KeyReleased;
    usleep(100);


    //Attack --> move the cursor to choose the target
    event.type=sf::Event::KeyPressed;
    event.key.code=sf::Keyboard::Key::A;
    event.KeyPressed;
    stateLayer.inputManager(event, engine.getState());
    engine.ScreenRefresh();
    event.KeyReleased;
    usleep(100);

    event.type=sf::Event::KeyPressed;
    event.key.code=sf::Keyboard::Key::Left;
    event.KeyPressed;
    stateLayer.inputManager(event, engine.getState());
    engine.ScreenRefresh();
    event.KeyReleased;
    usleep(100);

    event.type=sf::Event::KeyPressed;
    event.key.code=sf::Keyboard::Key::Right;
    event.KeyPressed;
    stateLayer.inputManager(event, engine.getState());
    engine.ScreenRefresh();
    event.KeyReleased;
    usleep(100);

    event.type=sf::Event::KeyPressed;
    event.key.code=sf::Keyboard::Key::Right;
    event.KeyPressed;
    stateLayer.inputManager(event, engine.getState());
    engine.ScreenRefresh();
    event.KeyReleased;
    usleep(100);

    event.type=sf::Event::KeyPressed;
    event.key.code=sf::Keyboard::Key::Up;
    event.KeyPressed;
    stateLayer.inputManager(event, engine.getState());
    engine.ScreenRefresh();
    event.KeyReleased;
    usleep(100);

    event.type=sf::Event::KeyPressed;
    event.key.code=sf::Keyboard::Key::Down;
    event.KeyPressed;
    stateLayer.inputManager(event, engine.getState());
    engine.ScreenRefresh();
    event.KeyReleased;
    usleep(100);

    //Select target
    event.type=sf::Event::KeyPressed;
    event.key.code=sf::Keyboard::Key::Return;
    event.KeyPressed;
    stateLayer.inputManager(event, engine.getState());
    engine.ScreenRefresh();
    event.KeyReleased;
    usleep(100);

    //Cancel the Attack
    event.type=sf::Event::KeyPressed;
    event.key.code=sf::Keyboard::Key::Z;
    event.KeyPressed;
    stateLayer.inputManager(event, engine.getState());
    engine.ScreenRefresh();
    event.KeyReleased;
    usleep(100);



}
