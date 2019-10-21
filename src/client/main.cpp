#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 800), "Game test");
    sf::Texture Map;
    Map.loadFromFile("rsc/Images/level1_completeMap.png");
    
    sf::Sprite mapSprite;
    mapSprite.setTexture(Map);
    
    sf::Texture perso;
    perso.setSmooth(true);
    perso.loadFromFile("rsc/Images/hero1.png", sf::IntRect(64, 128, 64, 64));
    sf::Sprite spritePerso;
    spritePerso.setTexture(perso, true);
    spritePerso.setScale(0.5,0.5);

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
        window.display();
    }

    return 0;
}


