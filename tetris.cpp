#include "tetris.hpp"

Board::Board () {
    shape.setSize(sf::Vector2f(cellSize, cellSize));
    shape.setFillColor(sf::Color::White);
    shape.setOutlineThickness(cellThick);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOrigin(cellSize/2, cellSize/2);
}
