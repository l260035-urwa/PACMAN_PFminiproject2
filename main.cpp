
#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include <vector>

#include "Maze.h"

const float TILE_SIZE = 30.0f;

// FEATURE 1: INPUT
void handleInput(sf::RenderWindow& window)
{
    while (const std::optional<sf::Event> event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
    }
}

// FEATURE 1: UPDATE
void updateGame(Maze& maze, float deltaTime)
{
    // Future game logic:
    // updatePlayer(deltaTime);
    // updateGhosts(deltaTime);
    // checkCollisions();
    // updateScore();

    (void)maze;
    (void)deltaTime;
}

// FEATURE 2: DRAW PLAYER
void drawPlayer(sf::RenderWindow& window, sf::Vector2i playerStart)
{
    sf::CircleShape player(12.0f);

    player.setFillColor(sf::Color::Yellow);

    float x = playerStart.x * TILE_SIZE + 3.0f;
    float y = playerStart.y * TILE_SIZE + 3.0f;

    player.setPosition(sf::Vector2f(x, y));

    window.draw(player);
}

// FEATURE 2: DRAW GHOSTS
void drawGhosts(
    sf::RenderWindow& window,
    const std::vector<sf::Vector2i>& ghostStarts)
{
    sf::CircleShape ghost(12.0f);

    std::vector<sf::Color> ghostColors =
    {
        sf::Color::Red,
        sf::Color::Magenta,
        sf::Color::Cyan,
        sf::Color(255, 165, 0)
    };

    for (std::size_t i = 0; i < ghostStarts.size(); i++)
    {
        float x = ghostStarts[i].x * TILE_SIZE + 3.0f;
        float y = ghostStarts[i].y * TILE_SIZE + 3.0f;

        ghost.setPosition(sf::Vector2f(x, y));
        ghost.setFillColor(ghostColors[i % ghostColors.size()]);

        window.draw(ghost);
    }
}

// FEATURE 1 & 2: DRAW EVERYTHING
void drawGame(
    sf::RenderWindow& window,
    Maze& maze,
    sf::Vector2i playerStart,
    const std::vector<sf::Vector2i>& ghostStarts)
{
    window.clear(sf::Color::Black);

    // Draw maze first
    maze.draw(window);

    // Draw player and ghosts over the maze
    drawPlayer(window, playerStart);
    drawGhosts(window, ghostStarts);

    window.display();
}

int main()
{
    // Create game window
    sf::RenderWindow window(
        sf::VideoMode({ 570, 680 }),
        "PacMan"
    );

    window.setFramerateLimit(60);

    // Load maze from external text file
    Maze maze;

    if (!maze.loadFromFile("maze.txt"))
    {
        std::cerr << "ERROR: Could not load maze.txt. Game cannot start.\n";
        return 1;
    }

    // Get starting positions from maze.txt
    sf::Vector2i playerStart = maze.getPlayerStart();

    std::vector<sf::Vector2i> ghostStarts =
        maze.getGhostStarts();

    std::cout << "Player starting position loaded.\n";
    std::cout << "Ghost starting positions loaded: "
        << ghostStarts.size() << '\n';

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
        drawGame(window, maze, playerStart, ghostStarts);
    }

    return 0;
}
