#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string.h>

#include "render.h"
#include "../shared/engine.h"


using namespace sf;
using namespace std;
using namespace state;
using namespace render;
using namespace engine;

int main(int argc, char* argv[])
{
    if(argc>1){
        if(strcmp(argv[1],"test")==0){
            sf::RenderWindow window(sf::VideoMode(1950, 900), "SFML works!");
            sf::Texture Map;
            Map.loadFromFile("rsc/Images/level1_completeMap.png");
            
            sf::Sprite mapSprite;
            mapSprite.setTexture(Map);

            sf::Texture perso;
            perso.setSmooth(false);
            perso.loadFromFile("rsc/Images/hero1.png", sf::IntRect(64, 128, 64, 64));
            sf::Sprite spritePerso;
            spritePerso.setTexture(perso, true);
            spritePerso.setScale(0.5,0.5);

            sf::RectangleShape rectangle(sf::Vector2f(350, 800));
            rectangle.setPosition(sf::Vector2f(1600,0));

            
            sf::Text text;
            sf::Font font;

            font.loadFromFile("rsc/Font/Game_Played.otf");
            // choix de la chaîne de caractères à afficher
            text.setString("Hello world");

            // choix de la taille des caractères
            text.setFont(font);
            text.setCharacterSize(24); // exprimée en pixels, pas en points !
            text.setPosition(sf::Vector2f(1600,0));
            //text.setColor(sf::Color::Red);
            text.setFillColor(sf::Color::Blue);




            /**********************************/
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(0, 10)),
                sf::Vertex(sf::Vector2f(0, 150)),
                sf::Vertex(sf::Vector2f(10, 150))

            };

            /**********************************/

            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    switch(event.type){                    
                        case sf::Event::Closed:
                            window.close();
                            break;
                        case Event::KeyPressed:
                            switch(event.key.code){
                                case Keyboard::Down:
                                    if(spritePerso.getPosition().y+32<Map.getSize().y)
                                    spritePerso.move(0,32);
                                    break;
                                case Keyboard::Up:
                                    if(spritePerso.getPosition().y>0)
                                    spritePerso.move(0,-32);
                                    break;
                                case Keyboard::Left:
                                    if(spritePerso.getPosition().x>0)                        
                                    spritePerso.move(-32,0);
                                    break;
                                case Keyboard::Right:
                                    if(spritePerso.getPosition().x+32<Map.getSize().x)
                                    spritePerso.move(32,0);
                                    break;
                                default:
                                    break;
                            }
                        default:
                            break;
                    }
                }

                window.clear();
                window.draw(mapSprite);
                window.draw(spritePerso);
                window.draw(line, 2, sf::Lines);
                window.draw(rectangle);
                window.draw(text);
                window.display();
            }
        }

        else if(strcmp(argv[1],"render")==0){
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
                stateLayer.draw();
			}
        }

        else if(strcmp(argv[1],"engine")==0){
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
                    cout << "Press a key to execute a round.\n" << endl;
                    booting = false;
                }
                // Close the window if the close button is pressed
				while (window.pollEvent(event)){
					if (event.type == sf::Event::Closed){
						window.close();
					}/* else if(event.type==sf::Event::KeyPressed && engine.getState().getRound()==1){
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


                    }*/
                    stateLayer.inputManager(event, engine.getState());
				}
			}
        }
    }
    return 0;
}


