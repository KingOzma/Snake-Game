#include <iostream>
#include <conio.h>
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, foodX, foodY, score;
int rearX[100], rearY[100];
int nRear;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height;
    foodX = rand() % width;
    foodY = rand() % height;
}

void Draw()
{
    system("cls");
    for(int i = 0; i < width+2; i++)
        cout << "#";

    cout << endl;

    for(int i = 0; i < height; i++)
    {
        for (int l = 0; l < width; l++)
        {
           if (l == 0) 
           cout << "#";
        if (i == y && l == x)
           cout << "O";
        else if (i == foodY && l == foodX)
           cout << "F";
        else
        {
            bool print = false;
            for (int m = 0; m < nRear; m++)
            {
                if(rearX[m] == l && rearY[m] == i)
                {
                    cout << "o";
                    print = true;
                }   
            }
               if (!print)
                    cout << " "; 
        }
           if (l == width-1)
           cout << "#";
        }
        cout << endl;
    }

    for(int i = 0; i < width+2; i++)
        cout << "#";

    cout << endl;
    cout << "Score:" << score << endl;
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
            case 'q':
                gameOver = true;
                break;
        }
    }
}

void Logic()
{
    int prevX = rearX[0];
    int prevY = rearY[0];
    int prev2X, prev2Y
    rearX[0] = x;
    rearY[0] = y;
    for (int i= 1; i< nRear; i++)
    {
        prev2X - rearX[i];
        prev2Y = rearY[i];
        rearX[i] = prev2X;
        rearY[i] = prev2Y;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch(dir)
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
    //if(x > width || x < 0 || y > height || y < 0)
        //gameOver = true;
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height- 1;

    for (int i = 0; i < nRear; i++)
    if (rearX[i] == x && rearY[i] == y)
        gameOver = true;

    if (x == foodX && y == foodY)
    {
        score += 10;
        foodX = rand() % width;
        foodY = rand() % height;
        nRear++;
    }
}
int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
    }
    return 0;
}