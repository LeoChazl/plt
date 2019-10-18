#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>


int main()
{
    sf::RenderWindow window(sf::VideoMode(1800, 900), "SFML works!");
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
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(mapSprite);
        window.draw(spritePerso);
        window.display();
    }

    return 0;
}


