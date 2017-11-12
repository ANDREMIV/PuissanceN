#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "video.h"

int displayWinner();
int NextTurn();
int IsGridFull();

int main()
{
    initgame();
    initvideo();//video is init after game parameters have been established
    printgrid();

    while(1){
    if(IsGridFull())break;
    int row=AskPlayerRow();
    AddTokentoGrid(row,G.players[G.playerturn].arms);
    PrintLastToken(row);
    if(lastwin(row)!=TOKEN(EMPTY))
        {
            displayWinner();
            break;
        }
    NextTurn();
    }

    SDL_DestroyRenderer(V.renderer);
    SDL_DestroyWindow(V.window);
}
