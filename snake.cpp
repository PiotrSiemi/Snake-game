/*
 Simple terminal snake game written in CPP
 The player controls a snake that moves around the game area, eating fruits 
 to grow longer while avoiding collision with the snake's own tail.
 The game ends when the snake fills the entire game area or collides with itself.
 

 * Features:
 * - Snake movement controlled by arrow keys (UP, DOWN, LEFT, RIGHT)
 * - Randomly generated fruits for the snake to eat (+)
 * - End game message displayed upon completion
 
 * Libraries used:
 * - <iostream> for standard input/output
 * - <conio.h> for keyboard input (Windows-specific)
 * - <windows.h> for console manipulation (Windows-specific)

 * Methods:                                         
 *   - Setup(): Initialize game variables and display welcome messages.                         
 *   - Draw(): Draw the game screen with the snake and fruits.                                       
 *   - Input(): Handle user input to control the snake's movement.                                  
 *   - Logic(): Update the game logic, including snake movement and collision detection.                                      
 *   - Play(): Start the game loop.                 
 *   - fancyPrint(string message): Print a message with a typing  effect.                                                                          
 *   - endGameComunnicate(): Communicate the end  of the game to the player. 
 *                                                                                
 * Variables:                                       
 *   - x, y: Coordinates of the snake head.         
 *   - fruitX, fruitY: Coordinates of the fruit.    
 *   - score: Current score of the player.          
 *   - gameOver: Flag indicating if the game is over.     
 *                                            
 *   - gameWon: Flag indicating if the player won.  
 *   - maxTailLen: Maximum length of the snake's tail.                                            
 *   - tailLen: Current length of the snake's tail. 
 *   - tailX, tailY: Arrays storing the coordinates of the snake's tail segments.              
 *   - dir: Current direction of the snake.         
 *                                                   

****************************************************************************************************
 */




#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

#define width 40
#define height 40

enum Direction
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class SnakeGame
{
private:
    int x, y, fruitX, fruitY, score, gameOver, gameWon;
    int maxTailLen;
    int tailLen;
    int tailX[100];
    int tailY[100];
    Direction dir;

public:
    SnakeGame() : maxTailLen((width * height) - 1), dir(STOP) {}

    void Setup()
    {
        gameOver = 0;
        gameWon = 0;
        x = width / 2;
        y = height / 2;
        fruitX = rand() % width;
        fruitY = rand() % height;
        score = 0;
        tailLen = 0;
        memset(tailX, 0, sizeof(tailX));
        memset(tailY, 0, sizeof(tailY));

        string startMsg = "Welcome to the snake game!";
        fancyPrint(startMsg);
        system("cls");
        string rulesMsg = "Rules are simple, eat fruits marked as '+', don't eat your own tail and move by using:  ";
        fancyPrint(rulesMsg);
        string msg21 = "W - up", msg22 = "A - left", msg23 = "S - down", msg24 = "D - right";
        fancyPrint(msg21);
        fancyPrint(msg22);
        fancyPrint(msg23);
        fancyPrint(msg24);
        system("cls");
        string begin = "Game loading";
        fancyPrint(begin);
        Sleep(500);
        system("cls");
    }

    void Draw()
    {
        cout << "\033[0;0H";
        for (int i = 0; i < width + 2; ++i)
            cout << "X";
        for (int i = 0; i < height; ++i)
        {
            cout << "\nX";
            for (int j = 0; j < (width); ++j)
            {
                if (i == y && j == x)
                    cout << "O";
                else if (i == fruitY && j == fruitX)
                    cout << "+";
                else
                {
                    int flag = 0;
                    for (int k = 0; k < tailLen; ++k)
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << "o";
                            flag = 1;
                        }
                    }
                    if (!flag)
                        cout << " ";
                }
            }
            cout << "X";
        }

        cout << "\n";
        for (int i = 0; i < width + 2; ++i)
            cout << "X";
        cout << "\nFruits eaten: " << score;
    }

    void Input()
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 'a':
                dir = LEFT;
                break;

            case 'd':
                dir = RIGHT;
                break;

            case 'w':
                dir = UP;
                break;

            case 's':
                dir = DOWN;
                break;

            case 'z':
                gameOver = 1;
                break;
            }
        }
    }

    void Logic()
    {
        int prevX = tailX[0];
        int prevY = tailY[0];
        int tempX, tempY;
        tailX[0] = x;
        tailY[0] = y;
        for (int i = 1; i < tailLen; ++i)
        {

            tempX = tailX[i];
            tempY = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;

            prevX = tempX;
            prevY = tempY;
        }

        switch (dir)
        {
        case LEFT:
            x--;
            break;

        case RIGHT:
            x++;
            break;

        case UP:
            y--;
            break;

        case DOWN:
            y++;
            break;

        default:
            break;
        }

        if (x >= width)
            x = 0;
        else if (x < 0)
            x = width - 1;
        else if (y >= height)
            y = 0;
        else if (y < 0)
            y = height - 1;

        for (int k = 0; k < tailLen; ++k)
        {
            if (tailX[k] == x && tailY[k] == y)
                gameOver = 1;
        }
        if (x == fruitX && y == fruitY)
        {
            tailLen++;
            score++;
            fruitX = rand() % width;
            fruitY = rand() % height;
        }

        if (tailLen == maxTailLen)
        {
            gameOver = 1;
            gameWon = 1;
        }
    }

    void Play()
    {
        Setup();

        while (!gameOver)
        {
            Draw();
            Input();
            Logic();
            Sleep(10);
        }

        endGameComunnicate();
        Sleep(10000);
    }

    void fancyPrint(string message)
    {
        cout << "\n";
        for (int i = 0; i < message.length(); ++i)
        {
            cout << message[i] << "_";
            Sleep(100);
            cout << "\b \b";
        }
    }

    void endGameComunnicate()
    {
        if (gameWon && gameOver)
        {
            string msg4 = "Congratulations! You won with a maximum score of: ";
            fancyPrint(msg4);
            cout << score;
        }
        else
        {
            string msg3 = "Game is over with a score: ";
            fancyPrint(msg3);
            cout << score;
        }
    }
};

int main()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    SnakeGame game;
    game.Play();

    return 0;
}

