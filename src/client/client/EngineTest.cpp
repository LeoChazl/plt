#include "../client.h"
#include "../render.h"
#include "../../shared/engine.h"
#include <unistd.h>


#include <fstream>
#include <iostream>
#include <sstream>


using namespace std;
using namespace client;
using namespace state;
using namespace render;
using namespace engine;

EngineTest::EngineTest(){

}

void EngineTest::run(){
    cout<<"---- ENGINE TEST ----"<<endl;

    //Initialize the window
    sf::RenderWindow window(sf::VideoMode(1950, 900), "Fire Emblem");

    /**************************/
    //sf::View view2(sf::Vector2f(350, 300), sf::Vector2f(800, 400));
    //window.setView(view2);
    // la vue de jeu (toute la fenêtre)
    // création d'une vue faisant la moitié de la vue par défaut
    sf::View view = window.getDefaultView();
    //view.zoom(0.5f);
    window.setView(view);

    // réactivation de la vue par défaut
    //window.setView(window.getDefaultView());
    /*sf::View gameView(sf::Vector2f(400, 300), sf::Vector2f(800, 400));
    gameView.setViewport(sf::FloatRect(0, 0, 1, 1));
    window.setView(gameView);*/

    // la mini-carte (dans un coin en haut à droite)
    /*sf::View minimapView(sf::Vector2f(975, 450), sf::Vector2f(1950, 900));
    minimapView.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
    window.setView(minimapView);*/


    /************************/


    Engine engine;
    engine.getState().initPlayers();

    StateLayer stateLayer(engine.getState(),window);
    stateLayer.initTextureAreas(engine.getState());

    StateLayer* ptr_stateLayer=&stateLayer;
    engine.getState().registerObserver(ptr_stateLayer);

    bool booting = true;


    while (window.isOpen()){
        sf::Event event;


        if(booting){
            // Draw all the display on the screen
            stateLayer.draw();
            cout << "Start of the simulation/commands test.\n" << endl;
            cout << "Pres a key to execute a round.\n" << endl;
            booting = false;
        }
        // Close the window if the close button is pressed
        while (1){
                window.pollEvent(event);
                if (event.type == sf::Event::Closed){
                    window.close();
                }else if(event.type==sf::Event::KeyPressed && engine.getState().getRound()==1){
                    cout << "\t\t--- Round 1 ---\n" << endl;

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
                    engine.checkRoundEnd();

                }else if(event.type==sf::Event::KeyPressed && engine.getState().getRound()==2){
                    engine.checkRoundStart();

                    // Troll moves
                    Position destination3(4,5);
                    Move deplacement3(*engine.getState().getMobileEntity(4,4), destination3);
                    unique_ptr<Command> ptr_deplacement3 (new Move(deplacement3));
                    engine.addCommand(0, move(ptr_deplacement3));

                    engine.update();
                    engine.checkRoundEnd();

                }else if(event.type==sf::Event::KeyPressed && engine.getState().getRound()==3){
                    engine.checkRoundStart();

                    // Knight moves
                    Position destination(3,4);
                    Move deplacement(*engine.getState().getMobileEntity(2,4), destination);
                    unique_ptr<Command> ptr_deplacement (new Move(deplacement));
                    engine.addCommand(0, move(ptr_deplacement));

                    // Troll moves
                    Position destination2(3,5);
                    Move deplacement2(*engine.getState().getMobileEntity(4,5), destination2);
                    unique_ptr<Command> ptr_deplacement2 (new Move(deplacement2));
                    engine.addCommand(1, move(ptr_deplacement2));

                    // Knight attacks troll until he dies
                    Attack attack(*engine.getState().getPlayerList()[0]->getMobileEntityList()[1], *engine.getState().getPlayerList()[1]->getMobileEntityList()[0]);
                    unique_ptr<Command> ptr_attack (new Attack(attack));
                    engine.addCommand(2, move(ptr_attack));

                    Attack attack2(*engine.getState().getPlayerList()[0]->getMobileEntityList()[1], *engine.getState().getPlayerList()[1]->getMobileEntityList()[0]);
                    unique_ptr<Command> ptr_attack2 (new Attack(attack2));
                    engine.addCommand(3, move(ptr_attack2));

                    Attack attack3(*engine.getState().getPlayerList()[0]->getMobileEntityList()[1], *engine.getState().getPlayerList()[1]->getMobileEntityList()[0]);
                    unique_ptr<Command> ptr_attack3 (new Attack(attack3));
                    engine.addCommand(4, move(ptr_attack3));

                    engine.update();
                    engine.checkRoundEnd();
                    cout<<"\t\t-- End of the simulation. --"<<endl;
                    window.close();

                }
                //stateLayer.inputManager(event, engine.getState());
            engine.ScreenRefresh();
            usleep(5);
        }
    }
}