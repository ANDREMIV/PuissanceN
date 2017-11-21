#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "video.h"


int displayWinner();

int Argv; char** Args;

/*prgm N nbrow nbline xscreen yscreen*/

int main(int argv, char** args)
{
    Argv = argv;
    Args=args;
    initgame();
    initvideo();//video is init after game parameters have been established
    printgrid();

    while(1){
    if(IsGridFull(G))break;
    int row=AskPlayerRow();
    AddTokentoGrid(row,G.players[G.playerturn].arms,&G);
    SDL_Delay(10);
    PrintLastToken(row);
    if(lastwin(row,G)!=TOKEN(EMPTY))
        {
            displayWinner();
            break;
        }
    NextTurn(&G);
    }




    SDL_Event e;

    while (1)
        {
        SDL_PollEvent(&e);
    if (e.type == SDL_KEYDOWN)
    {
        if(e.key.keysym.sym==SDLK_ESCAPE)
        {atexit(SDL_Quit);exit(0);}


    }
    if (e.type == SDL_QUIT)
    {
        atexit(SDL_Quit);exit(0);
    }
}
    SDL_DestroyRenderer(V.renderer);
    SDL_DestroyWindow(V.window);

    return 0;
}
