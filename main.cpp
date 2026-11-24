
#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>

#include "Maze.h"

// FEATURE 1: INPUT
void handleInput(sf::RenderWindow& window)
{
    while (const std::optional<sf::Event> event = window.pollEvent())
    {
        // Close the game when the X button is clicked
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
    }
}

// FEATURE 1: UPDATE
void updateGame(Maze& maze, float deltaTime)
{
    // Future game logic will be called here:
    //
    // updatePlayer(deltaTime);
    // updateGhosts(deltaTime);
    // checkCollisions();
    // updateScore();
    // checkGameState();

    (void)maze;
    (void)deltaTime;
}

// FEATURE 1: DRAW
void drawGame(sf::RenderWindow& window, Maze& maze)
{
    window.clear(sf::Color::Black);

    // FEATURE 2: Draw the maze
    maze.draw(window);

    // Future drawing functions:
    //
    // drawPlayer(window);
    // drawGhosts(window);
    // drawScore(window);
    // drawLives(window);

    window.display();
}

int main()
{
    // Create the game window
    sf::RenderWindow window(
        sf::VideoMode({ 570, 680 }),
        "PacMan"
    );

    window.setFramerateLimit(60);

    // Load the maze
    Maze maze;

    if (!maze.loadFromFile("maze.txt"))
    {
        std::cout << "Could not load maze.txt\n";
        return 1;
    }

    sf::Clock clock;

    // MAIN GAME LOOP
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        // JOB 1: Read input
        handleInput(window);

        if (!window.isOpen())
            break;

        // JOB 2: Update game logic
        updateGame(maze, deltaTime);

        // JOB 3: Draw everything
        drawGame(window, maze);
    }

    return 0;
}
