//snake.cpp helper functions
#include <iostream>
#include <stdio.h>

#include <stdlib.h>  /* srand, rand */
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <stropts.h>
#include <stdio.h>

#include <time.h>       /* time */
#include <ctime>

#include "snake.hpp"


using namespace std;

#define BORDER_WIDTH 40//40
#define BORDER_HEIGHT 25//25

enum direction {UP=0, DOWN, LEFT, RIGHT};
direction dir = DOWN;
int x_pos=1, y_pos = 2;
int bytesWaiting;
int fruit_x, fruit_y;
char k;


///
/// http://www.flipcode.com/archives/_kbhit_for_Linux.shtml
/// Check KeyBoard Pressed Or Not
int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    //int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}



int random(int min, int max) //range : [min, max)
{
   static bool first = true;
   if (first) 
   {  
      srand( time(0) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}



void FruitPosition(){
    fruit_x = random(1, BORDER_HEIGHT-1);
    fruit_y = random(1, BORDER_WIDTH-1);
}

void PrintBorder()
{
    int i, j;
    for(i=0; i<=BORDER_HEIGHT; i++)
    {
        for(j=0; j<=BORDER_WIDTH; j++)
        {
            if( (i == 0) || (i == BORDER_HEIGHT) )
            {
                printf("#");
            }
            else if(j == 0)
            {
                printf("#");
            }else if(j == BORDER_WIDTH)
            {
                printf("#");
            }else
            {
                if(i==INIT_X_POS && j==INIT_Y_POS) {
                printf("*");
                }else
                {
                printf(" ");
                }

            }

            
        }
        printf("\n");

    }
}


void InitGame() 
{
    PrintBorder();

}

int CheckBoundary(int x, int y)
{
    if(x<=0 || x>= BORDER_HEIGHT)
    {
        return GAMEOVER;
    }
    else if(y<=0 || y>=BORDER_WIDTH)
    {
        return GAMEOVER;
    }

    return STILL_IN_GAME;
}

int PrintSnake(int x, int y)
{
    int i, j;
    int out_of_bound = CheckBoundary(x, y);
    if(out_of_bound)
    {
        return GAMEOVER;
    }

    for(i=0; i<=BORDER_HEIGHT; i++)
    {
        for(j=0; j<=BORDER_WIDTH; j++)
        {
            if( (i == 0) || (i == BORDER_HEIGHT) )
            {
                printf("#");
            }
            else if(j == 0)
            {
                printf("#");
            }else if(j == BORDER_WIDTH)
            {
                printf("#");
            }else
            {
                if(x==fruit_x && y==fruit_y)
                {
                    FruitPosition();
                }
                if(i==x && j==y) { //snake position
                    printf("*");
                }
                else if(i==fruit_x && j==fruit_y) {
                    printf("$");
                }
                else
                {
                    printf(" ");
                }



            }

            
        }
        printf("\n");
        

    }
    return STILL_IN_GAME;
}

int input(char c)
{
    switch(c)
    {
        case 'w':
            x_pos--;
            dir = UP;
            break;

        case 'a':
            y_pos--;
            dir = LEFT;
            break;

        case 's':
            x_pos++;
            dir = DOWN;
            break;

        case 'd':
            y_pos++;
            dir = RIGHT;
            break;
    }
}
void AutoMove()
{
        switch(dir)
    {
        case UP:
            x_pos--;
            break;

        case LEFT:
            y_pos--;
            break;

        case DOWN:
            x_pos++;
            break;

        case RIGHT:
            y_pos++;
            break;
    }
}

void Loop()
{
    int game_over;
    FruitPosition();
    for(;;)
    {
       
        if(_kbhit())   /// If keyboard hit
        {
            cin >> k; /// Character
            input(k);
        }else
        {
            AutoMove();
        }
        usleep(150000);
        printf("\n");
        game_over = PrintSnake(x_pos,y_pos);
        printf("x_pos: %d, y_pos: %d\nfruit_x: %d, fruit_y: %d\n", x_pos, y_pos, fruit_x, fruit_y);
        if(game_over) 
        {
            break;
        }
    }
    printf("\nYou Lose. Good Game\n");
}