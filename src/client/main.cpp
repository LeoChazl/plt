#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string.h>

#include </home/ensea/plt/src/client/render.h>

using namespace sf;
using namespace std;
using namespace state;
using namespace render;

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
            cout << "Affichage d'un état du jeu" << endl;
            sf::RenderWindow window(sf::VideoMode(1950, 900), "SFML works!");
            //State state;
            //StateLayer stateLayer(window,state);
            //stateLayer.draw(window);


            
        }
    }
    return 0;
}


