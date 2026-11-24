
#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Maze
{
private:
    std::vector<std::string> mazeLayout;
    float tileSize = 30.0f;

public:
    bool loadFromFile(const std::string& filename);
    void draw(sf::RenderWindow& window);
};

