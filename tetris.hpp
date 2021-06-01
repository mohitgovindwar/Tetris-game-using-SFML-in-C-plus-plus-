#ifndef tetris_hpp
#define tetris_hpp

#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
using namespace std;

class Board {
private:
    int r = 20, c = 10, cellSize = 32, cellThick = 1;
public:
    sf::RectangleShape shape;
    Board();
};

#endif
