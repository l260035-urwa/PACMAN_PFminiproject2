
#include "Player.h"

Player::Player()
{
    shape.setRadius(12.0f);
    shape.setFillColor(sf::Color::Yellow);
}

void Player::setPosition(sf::Vector2i startPosition)
{
    position = startPosition;
}

void Player::setDirection(int newDirection, const Maze& maze)
{
    if (newDirection < 1 || newDirection > 4)
        return;

    sf::Vector2i nextPosition = position;

    if (newDirection == 1)
        nextPosition.y--;
    else if (newDirection == 2)
        nextPosition.y++;
    else if (newDirection == 3)
        nextPosition.x--;
    else if (newDirection == 4)
        nextPosition.x++;

    if (!maze.isWall(nextPosition.x, nextPosition.y))
    {
        direction = newDirection;
    }
}

void Player::update(const Maze& maze)
{
    frameCounter++;

    if (frameCounter < framesPerMove)
        return;

    frameCounter = 0;

    sf::Vector2i nextPosition = position;

    if (direction == 1)
        nextPosition.y--;
    else if (direction == 2)
        nextPosition.y++;
    else if (direction == 3)
        nextPosition.x--;
    else if (direction == 4)
        nextPosition.x++;

    if (!maze.isWall(nextPosition.x, nextPosition.y))
    {
        position = nextPosition;
    }
    else
    {
        direction = 0;
    }
}

void Player::draw(sf::RenderWindow& window)
{
    shape.setPosition(
        sf::Vector2f(position.x * 30.0f + 3.0f,
            position.y * 30.0f + 3.0f)
    );

    window.draw(shape);
}

sf::Vector2i Player::getPosition() const
{
    return position;
}

int Player::getDirection() const
{
    return direction;
}
