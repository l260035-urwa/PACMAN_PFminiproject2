
#include "Maze.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool Maze::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open maze file: "
            << filename << '\n';
        return false;
    }

    // Read maze dimensions from the first line.
    if (!(file >> rows >> cols) || rows <= 0 || cols <= 0)
    {
        std::cerr << "Error: Invalid maze dimensions.\n";
        return false;
    }

    // Remove the remaining newline after reading dimensions.
    std::string line;
    std::getline(file, line);

    mazeLayout.clear();
    ghostStarts.clear();

    mazeLayout.resize(rows, std::vector<char>(cols));

    int playerCount = 0;
    int ghostCount = 0;

    // Read the maze one row at a time.
    for (int row = 0; row < rows; row++)
    {
        if (!std::getline(file, line))
        {
            std::cerr << "Error: Maze file has fewer rows than expected.\n";
            mazeLayout.clear();
            return false;
        }

        if (static_cast<int>(line.size()) != cols)
        {
            std::cerr << "Error: Maze row " << row + 1
                << " does not contain " << cols << " columns.\n";
            mazeLayout.clear();
            return false;
        }

        for (int col = 0; col < cols; col++)
        {
            char symbol = line[col];

            if (symbol == '#')
            {
                mazeLayout[row][col] = '#';
            }
            else if (symbol == '.')
            {
                mazeLayout[row][col] = '.';
            }
            else if (symbol == 'O')
            {
                mazeLayout[row][col] = 'O';
            }
            else if (symbol == '-')
            {
                mazeLayout[row][col] = '-';
            }
            else if (symbol == 'P')
            {
                playerStart = sf::Vector2i(col, row);
                playerCount++;
                mazeLayout[row][col] = '-';
            }
            else if (symbol == 'G')
            {
                ghostStarts.push_back(sf::Vector2i(col, row));
                ghostCount++;
                mazeLayout[row][col] = '-';
            }
            else
            {
                std::cerr << "Error: Invalid symbol in maze file.\n";
                mazeLayout.clear();
                return false;
            }
        }
    }

    // Check that the maze has one player and four ghosts.
    if (playerCount != 1)
    {
        std::cerr << "Error: Maze must contain exactly one P.\n";
        mazeLayout.clear();
        return false;
    }

    if (ghostCount != 4)
    {
        std::cerr << "Error: Maze must contain exactly four G symbols.\n";
        mazeLayout.clear();
        ghostStarts.clear();
        return false;
    }

    std::cout << "Maze loaded successfully!\n";

    return true;
}


void Maze::draw(sf::RenderWindow& window)
{
    sf::RectangleShape wall(
        sf::Vector2f(tileSize, tileSize)
    );

    sf::CircleShape pellet(4.0f);
    sf::CircleShape powerPellet(8.0f);

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            float x = col * tileSize;
            float y = row * tileSize;

            char cell = mazeLayout[row][col];

            if (cell == '#')
            {
                wall.setPosition(sf::Vector2f(x, y));
                wall.setFillColor(sf::Color::Blue);
                window.draw(wall);
            }
            else if (cell == '.')
            {
                pellet.setPosition(
                    sf::Vector2f(x + 11.0f, y + 11.0f)
                );

                pellet.setFillColor(sf::Color::White);
                window.draw(pellet);
            }
            else if (cell == 'O')
            {
                powerPellet.setPosition(
                    sf::Vector2f(x + 7.0f, y + 7.0f)
                );

                powerPellet.setFillColor(sf::Color::Yellow);
                window.draw(powerPellet);
            }
        }
    }
}


sf::Vector2i Maze::getPlayerStart() const
{
    return playerStart;
}


std::vector<sf::Vector2i> Maze::getGhostStarts() const
{
    return ghostStarts;
}
