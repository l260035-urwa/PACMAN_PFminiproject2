
#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include <vector>

#include "Maze.h"
#include "Player.h"

// FEATURE 3: PLAYER INPUT
void handleInput(
    sf::RenderWindow& window,
    Player& player,
    const Maze& maze)
{
    while (const std::optional<sf::Event> event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        if (const auto* key = event->getIf<sf::Event::KeyPressed>())
        {
            switch (key->code)
            {
            case sf::Keyboard::Key::Up:
            case sf::Keyboard::Key::W:
                player.setDirection(1, maze);
                break;

            case sf::Keyboard::Key::Down:
            case sf::Keyboard::Key::S:
                player.setDirection(2, maze);
                break;

            case sf::Keyboard::Key::Left:
            case sf::Keyboard::Key::A:
                player.setDirection(3, maze);
                break;

            case sf::Keyboard::Key::Right:
            case sf::Keyboard::Key::D:
                player.setDirection(4, maze);
                break;

            default:
                break;
            }
        }
    }
}

// FEATURE 3: UPDATE PLAYER MOVEMENT
void updateGame(Player& player, const Maze& maze)
{
    player.update(maze);
}

// FEATURE 2 AND 3: DRAW GAME
void drawGame(
    sf::RenderWindow& window,
    Maze& maze,
    Player& player,
    const std::vector<sf::Vector2i>& ghostStarts)
{
    window.clear(sf::Color::Black);

    maze.draw(window);

    player.draw(window);

    // Draw four ghosts at their starting positions
    std::vector<sf::Color> ghostColors =
    {
        sf::Color::Red,
        sf::Color::Magenta,
        sf::Color::Cyan,
        sf::Color(255, 165, 0)
    };

    sf::CircleShape ghost(12.0f);

    for (std::size_t i = 0; i < ghostStarts.size(); i++)
    {
        ghost.setPosition(
            sf::Vector2f(
                ghostStarts[i].x * 30.0f + 3.0f,
                ghostStarts[i].y * 30.0f + 3.0f
            )
        );

        ghost.setFillColor(ghostColors[i % ghostColors.size()]);

        window.draw(ghost);
    }

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

    // Load maze from maze.txt
    Maze maze;

    if (!maze.loadFromFile("maze.txt"))
    {
        std::cerr << "ERROR: Could not load maze.txt. Game cannot start.\n";
        return 1;
    }

    // Create player at the P position
    Player player;

    player.setPosition(maze.getPlayerStart());

    // Load ghost starting positions
    std::vector<sf::Vector2i> ghostStarts =
        maze.getGhostStarts();

    sf::Clock clock;

    // MAIN GAME LOOP
    while (window.isOpen())
    {
        handleInput(window, player, maze);

        if (!window.isOpen())
            break;

        updateGame(player, maze);

        drawGame(window, maze, player, ghostStarts);
    }

    return 0;
}
