#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string.h>

#include </home/ensea/plt/src/client/render.h>
#include </home/ensea/plt/src/shared/engine.h>


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
                    cout << "Press a key to launch a command.\n" << endl;
                    booting = false;
                }
                // Close the window if the close button is pressed
				while (window.pollEvent(event)){
					if (event.type == sf::Event::Closed){
						window.close();
					} else if(event.type==sf::Event::KeyPressed && engine.getState().getRound()==1){
    
                        Position destination1(5,6);
                        Move deplacement1(*engine.getState().getMobileEntity(6,6), destination1);
                        unique_ptr<Command> ptr_deplacement1 (new Move(deplacement1));
                        engine.addCommand(0, move(ptr_deplacement1));
                        
                        
                        Position destination2(4,6);
                        Move deplacement2(*engine.getState().getMobileEntity(6,6), destination2);
                        unique_ptr<Command> ptr_deplacement2 (new Move(deplacement2));
                        engine.addCommand(1, move(ptr_deplacement2));


                        // Mage attack Troll
                        Attack attack(*engine.getState().getPlayerList()[0]->getMobileEntityList()[1], *engine.getState().getPlayerList()[1]->getMobileEntityList()[0]);
                        unique_ptr<Command> ptr_attack (new Attack(attack));
                        engine.addCommand(2, move(ptr_attack));

                        /*Position destination3(26,10);
                        Move deplacement3(*engine.getState().getMobileEntity(25,10), destination3);
                        unique_ptr<Command> ptr_deplacement3 (new Move(deplacement3));
                        engine.addCommand(2, move(ptr_deplacement3));*/
                        engine.getState().setRound(2);
                        engine.update();
                        engine.checkRoundEnd();

                    }else if(event.type==sf::Event::KeyPressed && engine.getState().getRound()==2){
                        engine.checkRoundStart();
                        cout<<"round 2"<<endl;

                        Position destination3(4,5);
                        Move deplacement3(*engine.getState().getMobileEntity(4,4), destination3);
                        unique_ptr<Command> ptr_deplacement3 (new Move(deplacement3));
                        engine.addCommand(0, move(ptr_deplacement3));

                        engine.getState().setRound(3);
                        engine.update();
                        engine.checkRoundEnd();

                    }else if(event.type==sf::Event::KeyPressed && engine.getState().getRound()==3){
                        engine.checkRoundStart();
                        cout<<"round 3"<<endl;

                        Position destination(3,4);
                        Move deplacement(*engine.getState().getMobileEntity(2,4), destination);
                        unique_ptr<Command> ptr_deplacement (new Move(deplacement));
                        engine.addCommand(0, move(ptr_deplacement));

                        Position destination2(3,5);
                        Move deplacement2(*engine.getState().getMobileEntity(4,5), destination2);
                        unique_ptr<Command> ptr_deplacement2 (new Move(deplacement2));
                        engine.addCommand(1, move(ptr_deplacement2));

                        // Troll attack knight
                        cout<<"Attaque: 3 coups critique"<<endl;
                        Attack attack(*engine.getState().getPlayerList()[0]->getMobileEntityList()[1], *engine.getState().getPlayerList()[1]->getMobileEntityList()[0]);
                        unique_ptr<Command> ptr_attack (new Attack(attack));
                        engine.addCommand(2, move(ptr_attack));

                        Attack attack2(*engine.getState().getPlayerList()[0]->getMobileEntityList()[1], *engine.getState().getPlayerList()[1]->getMobileEntityList()[0]);
                        unique_ptr<Command> ptr_attack2 (new Attack(attack2));
                        engine.addCommand(3, move(ptr_attack2));

                        Attack attack3(*engine.getState().getPlayerList()[0]->getMobileEntityList()[1], *engine.getState().getPlayerList()[1]->getMobileEntityList()[0]);
                        unique_ptr<Command> ptr_attack3 (new Attack(attack3));
                        engine.addCommand(4, move(ptr_attack3));

                        engine.getState().setRound(4);
                        engine.update();
                        cout<<"Troll a attaqué knight!!"<<endl;
                        engine.checkRoundEnd();
                        cout<<"\t--FIN--"<<endl;
                        window.close();


                    }
				}
			}
        }
    }
    return 0;
}


