#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>


int main()
{
    sf::RenderWindow window(sf::VideoMode(1950, 900), "SFML works!");
    sf::Texture Map;
    Map.loadFromFile("rsc/Images/level1_completeMap.png");
    
    sf::Sprite mapSprite;
    mapSprite.setTexture(Map);

    sf::Texture perso;
    perso.setSmooth(true);
    perso.loadFromFile("rsc/Images/hero1.png", sf::IntRect(64, 128, 64, 64));
    sf::Sprite spritePerso;
    spritePerso.setTexture(perso, true);

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
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(mapSprite);
        window.draw(spritePerso);
        window.draw(line, 2, sf::Lines);
        window.draw(rectangle);
        window.draw(text);
        window.display();
    }

    return 0;
}


