#include "SDL.h"

///SDL ORIENTATION
/*
X : 0 -- - - -- >
Y: 0
   |
   |
   v
*/

struct VideoHandle{
    SDL_Window *window;
    SDL_Renderer *renderer;
int xVscreen, yVscreen;
double xstep, ystep;
};

void initgame();
int initvideo();
void printgrid();
int PrintLastToken(int row);
