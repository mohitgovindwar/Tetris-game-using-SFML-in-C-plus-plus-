#include "tetris.hpp"
int WIDTH = 960, HEIGHT = 736;
int posY = 5, posX = 5;
const int r = 20, c = 10, cellSize = 32, cellThick = 1;
const int blockX = 5, blockY = 5, N = 5;
int num = 0;
int fig;
int score = 0;

bool found = false;
int CountHorizontal = 0;
int CountVertical = 0;
bool isZpressed = false;
int Count_check = 0;
bool rotateUp = true;
bool rotateDown = true;
bool rotateLeft = true;
bool rotateRight = true;
bool isAllowed = true;
bool isUpMoveAvailable = true;
bool isDownMoveAvailable = true;
bool isLeftMoveAvailable = true;
bool isRightMoveAvailable = true;
bool isAnObstacle = false;
bool isLastLineFull = false;
bool isQpressed = false;
bool isGameOver = false;
bool isFallenOnFirstLine = false;
bool clockRestart = false;

float timeMy;
float delay = 1.00;

// Test block
int test[blockY][blockX];

// Game Over
void gameOver(int field[][c]) {
    for (int i1 = posY, i2 = 0; i1 < posY+blockY; i1++, i2++) {
        for (int j1 = posX, j2 = 0; j1 < posX+blockX; j1++, j2++) {
            if (field[i1][j1] != 0 && test[i2][j2] != 0)
                isGameOver = true;
        }
    }
}

// Create figure
void getFigure() {
    int L_R[blockY][blockX] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 2, 0},
        {0, 2, 2, 2, 0},
        {0, 0, 0, 0, 0},
    };
    int L_L[blockY][blockX] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 0, 0, 0},
        {0, 2, 2, 2, 0},
        {0, 0, 0, 0, 0},
    };
    int Z_R[blockY][blockX] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 2, 2, 0},
        {0, 2, 2, 0, 0},
        {0, 0, 0, 0, 0},
    };
    int Z_L[blockY][blockX] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 2, 0, 0},
        {0, 0, 2, 2, 0},
        {0, 0, 0, 0, 0},
    };
    int T[blockY][blockX] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 2, 0, 0},
        {0, 2, 2, 2, 0},
        {0, 0, 0, 0, 0},
    };
    int O[blockY][blockX] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 2, 2, 0},
        {0, 0, 2, 2, 0},
        {0, 0, 0, 0, 0},
    };
    int I[blockY][blockX] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {2, 2, 2, 2, 0},
        {0, 0, 0, 0, 0},
    };

    fig = rand() % 7 + 1;

    switch (fig) {
        case 1:
            // L_L or L
            for (int y = 0; y < blockY; y++) {
                for (int x = 0; x < blockX; x++) {
                    test[y][x] = L_L[y][x];
                }
            }
            posY = -2, posX = 2;
            break;

        case 2:
            // L_R or J
            for (int y = 0; y < blockY; y++) {
                for (int x = 0; x < blockX; x++) {
                    test[y][x] = L_R[y][x];
                }
            }
            posY = -2, posX = 2;
            break;

        case 3:
            // Z_R or S
            for (int y = 0; y < blockY; y++) {
                for (int x = 0; x < blockX; x++) {
                    test[y][x] = Z_R[y][x];
                }
            }
            posY = -2, posX = 3;
            break;

        case 4:
            // Z_L or Z
            for (int y = 0; y < blockY; y++) {
                for (int x = 0; x < blockX; x++) {
                    test[y][x] = Z_L[y][x];
                }
            }
            posY = -2, posX = 3;
            break;

        case 5:
            // T
            for (int y = 0; y < blockY; y++) {
                for (int x = 0; x < blockX; x++) {
                    test[y][x] = T[y][x];
                }
            }
            posY = -2, posX = 2;
            break;

        case 6:
            // O
            for (int y = 0; y < blockY; y++) {
                for (int x = 0; x < blockX; x++) {
                    test[y][x] = O[y][x];
                }
            }
            posY = -2, posX = 2;
            break;

        case 7:
            // I
            for (int y = 0; y < blockY; y++) {
                for (int x = 0; x < blockX; x++) {
                    test[y][x] = I[y][x];
                }
            }
            posY = -3, posX = 3;
            break;
    }
}

// Falling on first line
void fallFirstLine (int field[][c]) {
    for (int i1 = posY, i2 = 0; i1 < posY+blockY; i1++, i2++) {
        for (int j1 = posX, j2 = 0; j1 < posX+blockX; j1++, j2++) {
            if (i1 == r - 1 && test[i2][j2] != 0) {
                isFallenOnFirstLine = true;
            }
        }
    }

    if (isFallenOnFirstLine) {
        for (int i1 = posY, i2 = 0; i1 < posY+blockY; i1++, i2++) {
            for (int j1 = posX, j2 = 0; j1 < posX+blockX; j1++, j2++) {
                if (test[i2][j2] != 0) {
                    field[i1][j1] = test[i2][j2];
                    score += 1;
                    clockRestart = true;
                }
            }
        }
    }

    isFallenOnFirstLine = false;

}

// Falling
void fall(int field[][c]) {
    if (isDownMoveAvailable == true) {
        int field_test[r][c];
        for (int y = 0; y < r; y++) {
            for (int x = 0; x < c; x++) {
                field_test[y][x] = field[y][x];
            }
        }
        int figure_test[blockX][blockY];
        for (int y = 0; y < blockY; y++) {
            for (int x = 0; x < blockX; x++) {
                figure_test[y][x] = test[y][x];
            }
        }
        for (int i1 = posY+1, i2 = 0; i1 < posY+blockY+1; i1++, i2++) {
            for (int j1 = posX, j2 = 0; j1 < posX+blockX; j1++, j2++) {
                if (field_test[i1][j1] != 0 && figure_test[i2][j2] != 0)
                    isAnObstacle = true;
            }
        }

        if (found == false) {
            for (int y = blockY - 1; y >= 0; y--) {
                if (test[y][0] == 0 && test[y][1] == 0 && test[y][2] == 0 &&
                    test[y][3] == 0 && test[y][4] == 0) {
                    CountVertical++;
                    Count_check = CountVertical;
                }
                if (test[y][0] != 0 || test[y][1] != 0 || test[y][2] != 0 ||
                    test[y][3] != 0 || test[y][4] != 0) {
                    found = true;
                    break;
                }
            }
        }
        if (posY < r - blockY + CountVertical) {
            if (isAnObstacle == false) {
                posY += 1;
                isDownMoveAvailable = false;
            }
            else {
                for (int i1 = posY, i2 = 0; i1 < posY+blockY; i1++, i2++) {
                    for (int j1 = posX, j2 = 0; j1 < posX+blockX; j1++, j2++) {
                        if (test[i2][j2] != 0) {
                            field[i1][j1] = test[i2][j2];
                            score += 1;
                        }
                    }
                }
                getFigure();
                gameOver(field);
            }
        }
    }
    CountVertical = 0;
    found = false;
    isDownMoveAvailable = true;
    isAnObstacle = false;
}

// Line to destroy
void lastLine(int field[][c]) {

    int num = 0;
    for (int y = 0; y < r; y++) {
        if (field[y][0] != 0 &&
            field[y][0] == field[y][1] && field[y][1] == field[y][2] &&
            field[y][2] == field[y][3] && field[y][3] == field[y][4] &&
            field[y][4] == field[y][5] && field[y][5] == field[y][6] &&
            field[y][6] == field[y][7] && field[y][7] == field[y][8] &&
            field[y][8] == field[y][9]) {
            num = y;

            score += 10;
        }
    }

    if (num >= 0) {
        for (int numPrev = num - 1, numLast = num; numPrev >= 0; numPrev--, numLast--)
            for (int xP = 0, xL = 0; xP < c; xP++, xL++)
                field[numLast][xL] = field[numPrev][xP];
    }
}

// Rotate
void rotate(int matrixOrigin[][N], int field[][c]) {
    int matrixMinorDiagonal[N][N] = {
        {0, 0, 0, 0, 1},
        {0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0},
    };

    int transMatrix[N][N];

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            transMatrix[x][y] = matrixOrigin[y][x];
        }
    }

    int result[N][N];

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            num = 0;
            for (int i = 0; i < N; i++) {
                num += transMatrix[y][i] * matrixMinorDiagonal[i][x];
            }
            result[y][x] = num;
        }
    }

    ////////////////////////////////////////
    // Test to see if figure can rotate
    int field_test[r+1][c+1];
    for (int y = 0; y < r+1; y++) {
        for (int x = 0; x < c+1; x++) {
            field_test[y][x] = field[y][x];
        }
    }
    for (int i1 = posY, i2 = 0; i1 < posY+blockY; i1++, i2++) {
        for (int j1 = posX, j2 = 0; j1 < posX+blockX; j1++, j2++) {

            if (field_test[i1][j1] != 0 && result[i2][j2] != 0) isAllowed = false;

            field_test[i1][j1] = result[i2][j2];
            if (field_test[i1][j1] != 0) {
                if (j1 < 0 || j1 > c - 1) {
                    isAllowed = false;
                }
                if (i1 < 0 || i1 > r - 1) {
                    isAllowed = false;
                }
            }
        }
    }
    if (isAllowed == true) {
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < N; x++) {
                matrixOrigin[y][x] = result[y][x];
            }
        }
    }
}

// Move
void update(int field[][c]) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if (isLeftMoveAvailable == true) {

            int field_test[r][c];
            for (int y = 0; y < r; y++) {
                for (int x = 0; x < c; x++) {
                    field_test[y][x] = field[y][x];
                }
            }
            int figure_test[blockX][blockY];
            for (int y = 0; y < blockY; y++) {
                for (int x = 0; x < blockX; x++) {
                    figure_test[y][x] = test[y][x];
                }
            }
            for (int i1 = posY, i2 = 0; i1 < posY+blockY; i1++, i2++) {
                for (int j1 = posX-1, j2 = 0; j1 < posX+blockX-1; j1++, j2++) {
                    if (field_test[i1][j1] != 0 && figure_test[i2][j2] != 0)
                        isAnObstacle = true;
                }
            }

            if (found == false) {
                for (int x = 0; x < blockX; x++) {
                    if (test[0][x] == 0 && test[1][x] == 0 && test[2][x] == 0 &&
                        test[3][x] == 0 && test[4][x] == 0) {
                        CountHorizontal++;
                        Count_check = CountHorizontal;
                    }
                    if (test[0][x] != 0 || test[1][x] != 0 || test[2][x] != 0 ||
                        test[3][x] != 0 || test[4][x] != 0) {
                        found = true;
                        break;
                    }
                }
            }
            if (posX > 0 - CountHorizontal) {
                if (isAnObstacle == false) {
                    posX -= 1;
                    isLeftMoveAvailable = false;
                }
            }
        }
    }
    else {
        CountHorizontal = 0;
        found = false;
        isLeftMoveAvailable = true;
        isAnObstacle = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if (isRightMoveAvailable == true) {

            int field_test[r][c];
            for (int y = 0; y < r; y++) {
                for (int x = 0; x < c; x++) {
                    field_test[y][x] = field[y][x];
                }
            }
            int figure_test[blockX][blockY];
            for (int y = 0; y < blockY; y++) {
                for (int x = 0; x < blockX; x++) {
                    figure_test[y][x] = test[y][x];
                }
            }
            for (int i1 = posY, i2 = 0; i1 < posY+blockY; i1++, i2++) {
                for (int j1 = posX+1, j2 = 0; j1 < posX+blockX+1; j1++, j2++) {
                    if (field_test[i1][j1] != 0 && figure_test[i2][j2] != 0)
                        isAnObstacle = true;
                }
            }

            if (found == false) {
                for (int x = blockX - 1; x >= 0; x--) {
                    if (test[0][x] == 0 && test[1][x] == 0 && test[2][x] == 0 &&
                        test[3][x] == 0 && test[4][x] == 0) {
                        CountHorizontal++;
                        Count_check = CountHorizontal;
                    }
                    if (test[0][x] != 0 || test[1][x] != 0 || test[2][x] != 0 ||
                        test[3][x] != 0 || test[4][x] != 0) {
                        found = true;
                        break;
                    }
                }
            }
            if (posX < c - blockX + CountHorizontal) {
                if (isAnObstacle == false) {
                    posX += 1;
                    isRightMoveAvailable = false;
                }
            }
        }
    }
    else {
        CountHorizontal = 0;
        found = false;
        isRightMoveAvailable = true;
        isAnObstacle = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if (isDownMoveAvailable == true) {

            int field_test[r][c];
            for (int y = 0; y < r; y++) {
                for (int x = 0; x < c; x++) {
                    field_test[y][x] = field[y][x];
                }
            }
            int figure_test[blockX][blockY];
            for (int y = 0; y < blockY; y++) {
                for (int x = 0; x < blockX; x++) {
                    figure_test[y][x] = test[y][x];
                }
            }
            for (int i1 = posY+1, i2 = 0; i1 < posY+blockY+1; i1++, i2++) {
                for (int j1 = posX, j2 = 0; j1 < posX+blockX; j1++, j2++) {
                    if (field_test[i1][j1] != 0 && figure_test[i2][j2] != 0)
                        isAnObstacle = true;
                }
            }

            if (found == false) {
                for (int y = blockY - 1; y >= 0; y--) {
                    if (test[y][0] == 0 && test[y][1] == 0 && test[y][2] == 0 &&
                        test[y][3] == 0 && test[y][4] == 0) {
                        CountVertical++;
                        Count_check = CountVertical;
                    }
                    if (test[y][0] != 0 || test[y][1] != 0 || test[y][2] != 0 ||
                        test[y][3] != 0 || test[y][4] != 0) {
                        found = true;
                        break;
                    }
                }
            }
            if (posY < r - blockY + CountVertical) {
                if (isAnObstacle == false) {
                    posY += 1;
                    isDownMoveAvailable = false;
                }
            }
        }
    }
    else {
        CountVertical = 0;
        found = false;
        isDownMoveAvailable = true;
        isAnObstacle = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && fig != 6) {
        if (!isZpressed) {
            isAllowed = true;
            rotate(test, field);
            isZpressed = true;
        }
    }
    else
        isZpressed = false;
}

void check_rotate() {
    if (posY > 0 - 2 && posY < r - blockY + 2 &&
        posX > 0 - 2 && posX < c - blockX + 2) {
        rotateUp = true;
        rotateDown = true;
        rotateRight = true;
        rotateLeft = true;
    }
    else {
        rotateUp = false;
        rotateDown = false;
        rotateRight = false;
        rotateLeft = false;
    }
}

int main()
{
    srand(time(0));
    rand();

    // Clock
    sf::Clock clock;

    // Text
    sf::Font f;
    f.loadFromFile("Keyboard.ttf");
    sf::Text text;
    text.setFont(f);
    text.setCharacterSize(27);
    text.setFillColor(sf::Color::White);
    text.setPosition(64, 64);

    sf::Text text_test1;
    text_test1.setFont(f);
    text_test1.setCharacterSize(27);
    text_test1.setFillColor(sf::Color::White);
    text_test1.setPosition(64, 64+32);

    sf::Text text_test2;
    text_test2.setFont(f);
    text_test2.setCharacterSize(27);
    text_test2.setFillColor(sf::Color::White);
    text_test2.setPosition(64, 64+64);

    // Cells
    Board cells[r][c];
    for (int y = 0; y < r; y++) {
        for (int x = 0; x < c; x++) {
            cells[y][x].shape.setPosition(352+(x*(cellSize+cellThick)-cellSize/2),
                                          96+(y*(cellSize+cellThick)));
        }
    }

    // Field
    int landed[r][c];
    for (int y = 0; y < r; y++) {
        for (int x = 0; x < c; x++) {
            landed[y][x] = 0;
        }
    }

    getFigure();

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Tetris");
    window.setFramerateLimit(60);

    // Circle
    int radius = 1;
    sf::CircleShape circle;
    circle.setRadius(radius);
    circle.setOrigin(radius, radius);
    circle.setFillColor(sf::Color::Green);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape) {
                window.close();
            }

            // Restart
            if (isGameOver == true) {
                if (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Enter) {
                    isGameOver = false;
                    for (int y = 0; y < r; y++) {
                        for (int x = 0; x < c; x++) {
                            landed[y][x] = 0;
                        }
                    }
                    getFigure();
                    score = 0;
                    timeMy = 0;
                    clock.restart();
                }
            }
        }

        // Clear screen
        window.clear(sf::Color(0,0,80,100));

        // Movement
        if (!isGameOver)
            update(landed);

        lastLine(landed);

        if (isGameOver == false) {
            timeMy = clock.getElapsedTime().asSeconds();
        }

        if (timeMy > delay) {
            fallFirstLine(landed);
            fall(landed);
            timeMy = 0;
            clock.restart();
        }

        if (clockRestart) {
            timeMy = 0;
            clock.restart();
            clockRestart = false;
            getFigure();
        }

        // Draw cells
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                window.draw(cells[i][j].shape);
            }
        }

        // Mouse position
        int mX = sf::Mouse::getPosition(window).x;
        int mY = sf::Mouse::getPosition(window).y;

        // Draw circle
        circle.setPosition(mX, mY);
        window.draw(circle);

        // Cells change color when intersecting circle
        for (int y = 0; y < r; y++) {
            for (int x = 0; x < c; x++) {
                if (circle.getGlobalBounds().intersects(cells[y][x].shape.getGlobalBounds())) {
                    cells[y][x].shape.setFillColor(sf::Color::Yellow);
                    // Draw text
                    //text.setString("M " + to_string(landed[y][x]));
                    window.draw(text);
                }
                else
                    cells[y][x].shape.setFillColor(sf::Color::White);
            }
        }

        // Color test block in field
        for (int i1 = posY, i2 = 0; i1 < posY+blockY; i1++, i2++) {
            for (int j1 = posX, j2 = 0; j1 < posX+blockX; j1++, j2++) {

                if (test[i2][j2] != 0)
                    cells[i1][j1].shape.setFillColor(sf::Color::Green);
            }
        }

        // Fill with green color if cell != 0
        for (int y = 0; y < r; y++) {
            for (int x = 0; x < c; x++) {
                if (landed[y][x] != 0) {
                    cells[y][x].shape.setFillColor(sf::Color::Red);
                }
            }
        }

        text_test1.setString("Score " + to_string(score));
        window.draw(text_test1);

        if (isGameOver) {
            text_test2.setString("\nGame Over\n\nEnter \nor \nEscape");
            window.draw(text_test2);
        }

        window.display();
    }
    return EXIT_SUCCESS;
}
