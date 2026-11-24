
#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Maze
{
private:
    int rows = 0;
    int cols = 0;

    std::vector<std::vector<char>> mazeLayout;

    float tileSize = 30.0f;

    sf::Vector2i playerStart;
    std::vector<sf::Vector2i> ghostStarts;

public:
    bool loadFromFile(const std::string& filename);

    void draw(sf::RenderWindow& window);

    sf::Vector2i getPlayerStart() const;

    std::vector<sf::Vector2i> getGhostStarts() const;
};
