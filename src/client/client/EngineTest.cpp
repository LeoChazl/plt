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

    Engine* ptr_engine=&engine;
    stateLayer.registerRenderObserver(ptr_engine);

    bool booting = true;


    while (window.isOpen()){
        sf::Event event;

        if(booting){
            // Draw all the display on the screen
            stateLayer.draw(engine.getState());
            cout << "Start of the game.\n" << endl;
            booting = false;
        }
        // Close the window if the close button is pressed
        while (1){
            if(engine.checkGameEnd()==true){
                window.close();
                cout<<"Game END"<<endl;
                break;
            }

            if(!engine.getState().getEndGame() && engine.checkRoundEnd()){
                engine.checkRoundStart();
                StateEvent stateEvent(ALLCHANGE);
                engine.getState().notifyObservers(stateEvent, engine.getState());
            }

            window.pollEvent(event);
            if (event.type == sf::Event::Closed){
                window.close();
            }
            
            stateLayer.inputManager(event, engine.getState());
            engine.screenRefresh();
            usleep(50000);
        }
    }
}