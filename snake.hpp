//snake.hpp
#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#define INIT_X_POS 1
#define INIT_Y_POS 2
#define GAMEOVER 1
#define STILL_IN_GAME 0

extern int x_pos, y_pos;


void PrintBorder();
void InitGame();
void Loop();
void Delay();


#endif