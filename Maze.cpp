
#include "Maze.h"

#include <fstream>
#include <iostream>
#include <string>

bool Maze::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open maze file: "
                  << filename << '\n';
        return false;
    }

    // Read maze dimensions
    if (!(file >> rows >> cols) || rows <= 0 || cols <= 0)
    {
        std::cerr << "Error: Invalid maze dimensions.\n";
        return false;
    }

    std::string line;
    std::getline(file, line);

    mazeLayout.clear();
    ghostStarts.clear();

    mazeLayout.resize(rows, std::vector<char>(cols));

    int playerCount = 0;
    int ghostCount = 0;

    // Read maze into a 2D character array
    for (int row = 0; row < rows; row++)
    {
        if (!std::getline(file, line))
        {
            std::cerr << "Error: Missing maze row.\n";
            mazeLayout.clear();
            return false;
        }

        if (static_cast<int>(line.size()) != cols)
        {
            std::cerr << "Error: Incorrect number of columns in row "
                      << row + 1 << ".\n";
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
            else if (symbol == '.' || symbol == 'O' || symbol == '-')
            {
                mazeLayout[row][col] = symbol;
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
                std::cerr << "Error: Invalid maze character.\n";
                mazeLayout.clear();
                return false;
            }
        }
    }

    if (playerCount != 1 || ghostCount != 4)
    {
        std::cerr << "Error: Maze must contain one player and four ghosts.\n";
        mazeLayout.clear();
        ghostStarts.clear();
        return false;
    }

    std::cout << "Maze loaded successfully!\n";

    return true;
}


// Draw walls, ordinary pellets and power pellets
void Maze::draw(sf::RenderWindow& window)
{
    sf::RectangleShape wall(sf::Vector2f(tileSize, tileSize));

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
                pellet.setPosition(sf::Vector2f(x + 11.0f, y + 11.0f));
                pellet.setFillColor(sf::Color::White);
                window.draw(pellet);
            }
            else if (cell == 'O')
            {
                powerPellet.setPosition(sf::Vector2f(x + 7.0f, y + 7.0f));
                powerPellet.setFillColor(sf::Color::Yellow);
                window.draw(powerPellet);
            }
        }
    }
}


// Return player starting position
sf::Vector2i Maze::getPlayerStart() const
{
    return playerStart;
}


// Return ghost starting positions
std::vector<sf::Vector2i> Maze::getGhostStarts() const
{
    return ghostStarts;
}


// Check whether a cell is a wall
bool Maze::isWall(int col, int row) const
{
    if (row < 0 || row >= rows || col < 0 || col >= cols)
    {
        return true;
    }

    return mazeLayout[row][col] == '#';
}
//FEAtURE 4
//for collecting pellets in the maze
char Maze::collectPellet(int col, int row) {
    //to check whether the position is within maze
    if (row < 0 || row >= rows || col < 0 || col >= cols)
        return '\0';
    char cell = mazeLayout[row][col];
    if (cell == '.' || cell == 'O')
    {
        mazeLayout[row][col] = '-';
        return cell;
    }
    return '\0';
}

//for counting pallets in the maze
int Maze::countPellets() const {
    int count = 0;
    for (int r = 0;r < rows;r++) {
        for (int c = 0;c < cols;c++) {
            if (mazeLayout[r][c] == 'O' || mazeLayout[r][c] == '.')
                count++;
        }
    }
    return count;
}

