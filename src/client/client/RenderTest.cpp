#include "../client.h"
#include "../render.h"
#include <fstream>
#include <iostream>
#include <sstream>


using namespace std;
using namespace client;
using namespace state;
using namespace render;

//Constructor
RenderTest::RenderTest(){

}

//run
void RenderTest::run(){

    cout << "Displaying a state of the game" << endl;

    // Creation of the state
    State state;
    
    // Initialize the state notably the players
    state.initPlayers();

    sf::RenderWindow window(sf::VideoMode(1950, 900), "Fire Emblem");

    // Creation of the display of the state
    StateLayer stateLayer(state,window);
    stateLayer.initTextureAreas(state);

    while (window.isOpen()){
        sf::Event event;

        // Close the window if the close button is pressed
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        // Draw all the display on the screen
        stateLayer.draw(state);
    }
}
