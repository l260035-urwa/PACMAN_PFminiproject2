
#include "Maze.h"
#include <fstream>
#include <iostream>

bool Maze::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cout << "Could not open maze file!\n";
        return false;
    }

    mazeLayout.clear();

    std::string line;

    while (std::getline(file, line))
    {
        mazeLayout.push_back(line);
    }

    file.close();

    return true;
}

void Maze::draw(sf::RenderWindow& window)
{
    sf::RectangleShape wall(
        sf::Vector2f(tileSize, tileSize)
    );

    sf::CircleShape pellet(4.0f);

    for (int row = 0; row < mazeLayout.size(); row++)
    {
        for (int col = 0; col < mazeLayout[row].size(); col++)
        {
            float x = col * tileSize;
            float y = row * tileSize;

            if (mazeLayout[row][col] == '#')
            {
                wall.setPosition(sf::Vector2f(x, y));
                wall.setFillColor(sf::Color::Blue);
                window.draw(wall);
            }
            else if (mazeLayout[row][col] == '.')
            {
                pellet.setPosition(sf::Vector2f(x + 11, y + 11));
                pellet.setFillColor(sf::Color::White);
                window.draw(pellet);
            }
        }
    }
}
