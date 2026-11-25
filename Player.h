
#pragma once

#include <SFML/Graphics.hpp>
#include "Maze.h"

class Player
{
private:
    sf::Vector2i position;

    int direction = 0;

    int frameCounter = 0;

    int framesPerMove = 8;

    float tileSize = 30.0f;

    sf::CircleShape shape;

public:
    Player();

    void setPosition(sf::Vector2i startPosition);

    void setDirection(int newDirection, const Maze& maze);

    void update(const Maze& maze);

    void draw(sf::RenderWindow& window);

    sf::Vector2i getPosition() const;

    int getDirection() const;
};
