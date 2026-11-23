#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 570, 680 }), "PacMan");
    window.setFramerateLimit(60);
    const float TILE = 30.f;

    sf::RectangleShape wallBlock({ TILE, TILE });
    wallBlock.setFillColor(sf::Color(33, 33, 222));

    sf::CircleShape pellet(3.f);
    pellet.setFillColor(sf::Color::White);
    

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        wallBlock.setPosition({ 0.f, 0.f });
        window.draw(wallBlock);
        window.display();
    }
}