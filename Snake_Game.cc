#include <iostream>
#include <vector>
#include <unistd.h>
#include <string>
#include <termios.h>
#include <fcntl.h>
#include <cstdlib>
#include <ctime>

/* Function Prototypes */
std::vector<std::vector<std::string> > renderBox(int width, int height);
void displayCanvas(std::vector<std::vector<std::string> > &matrixBox);
void clearScreen();
void setup();
int kbhit();
void logic();
void input();

/* Global Constants */
const int width = 20;
const int height = 20;

/* Global Variables */
int x_position, y_position;
int fruit_x_position, fruit_y_position;
int score;
int nTail = 0;
std::vector<int> tailX, tailY;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;
bool gameOver;

int main() {
    std::vector<std::vector<std::string> > matrixBox = renderBox(width, height);
    setup();

    while (!gameOver) {
        displayCanvas(matrixBox);
        input();
        logic();
        usleep(100000); // Slow down the game loop
    }

    std::cout << "Game Over! Final Score: " << score << std::endl;
    return 0;
}

void setup() {
    gameOver = false;
    dir = STOP;
    x_position = width / 2;
    y_position = height / 2;

    srand(static_cast<unsigned>(time(0)));
    fruit_x_position = rand() % (width - 2) + 1;
    fruit_y_position = rand() % (height - 2) + 1;
    score = 0;

    tailX.clear();
    tailY.clear();
}

void input() {
    if (kbhit()) {
        char input;
        std::cin >> input;
        switch (input) {
            case 'w':
                if (dir != DOWN) dir = UP;
                break;
            case 's':
                if (dir != UP) dir = DOWN;
                break;
            case 'a':
                if (dir != RIGHT) dir = LEFT;
                break;
            case 'd':
                if (dir != LEFT) dir = RIGHT;
                break;
            case 'x':
                gameOver = true; // Quit the game
                break;
        }
    }
}

void logic() {
    // Move the tail
    int prevX = x_position, prevY = y_position;
    int prev2X, prev2Y;

    if (!tailX.empty()) {
        prevX = tailX[0];
        prevY = tailY[0];
        tailX[0] = x_position;
        tailY[0] = y_position;

        for (int i = 1; i < nTail; ++i) {
            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }
    }

    // Move the snake's head
    switch (dir) {
        case UP:    y_position--; break;
        case DOWN:  y_position++; break;
        case LEFT:  x_position--; break;
        case RIGHT: x_position++; break;
        default:    break;
    }

    // Check for collisions with the walls
    if (x_position < 0 || x_position >= width || y_position < 0 || y_position >= height)
        gameOver = true;

    // Check for collisions with the tail
    for (int i = 0; i < nTail; ++i) {
        if (tailX[i] == x_position && tailY[i] == y_position)
            gameOver = true;
    }

    // Check if the snake eats the fruit
    if (x_position == fruit_x_position && y_position == fruit_y_position) {
        score += 10;
        fruit_x_position = rand() % (width - 2) + 1;
        fruit_y_position = rand() % (height - 2) + 1;
        nTail++;
        tailX.push_back(0);
        tailY.push_back(0);
    }
}

std::vector<std::vector<std::string> > renderBox(int width, int height) {
    std::vector<std::vector<std::string> > matrixBox(height, std::vector<std::string>(width, "#"));

    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            matrixBox[i][j] = " ";
        }
    }

    return matrixBox;
}

void displayCanvas(std::vector<std::vector<std::string> > &matrixBox) {
    // Clear the entire canvas
    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            matrixBox[i][j] = " ";
        }
    }

    // Render the fruit
    matrixBox[fruit_y_position][fruit_x_position] = "F";

    // Render the snake's head
    matrixBox[y_position][x_position] = "O";

    // Render the tail
    for (int i = 0; i < nTail; ++i) {
        matrixBox[tailY[i]][tailX[i]] = "o";
    }

    // Display the updated canvas
    clearScreen();
    for (const auto &row : matrixBox) {
        for (const auto &cell : row) {
            std::cout << cell;
        }
        std::cout << std::endl;
    }
}


void clearScreen() {
    std::cout << "\033[2J\033[H";
}

int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}
