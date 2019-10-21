#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1800, 900), "Game test");
    sf::Texture Map;
    Map.loadFromFile("rsc/Images/level1_completeMap.png");
    
    sf::Sprite mapSprite;
    mapSprite.setTexture(Map);
    mapSprite.setScale(1.125,1.125);

    sf::Texture perso;
    perso.setSmooth(true);
    perso.loadFromFile("rsc/Images/hero1.png", sf::IntRect(64, 128, 64, 64));
    sf::Sprite spritePerso;
    spritePerso.setTexture(perso, true);
    spritePerso.setScale(1.125,1.125);
    spritePerso.setScale(1,1);

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
                            if(spritePerso.getPosition().y+64<=Map.getSize().y){
                                spritePerso.move(0,32);
                            }
                            break;
                        case Keyboard::Up:
                            spritePerso.move(0,-32);
                            break;
                        case Keyboard::Left:
                            spritePerso.move(-32,0);
                            break;
                        case Keyboard::Right:
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
        window.display();
    }

    return 0;
}


