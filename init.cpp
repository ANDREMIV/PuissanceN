#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "video.h"
#include "AI.h"
#include <SDL_render.h>
#include <string.h>

struct Game G;
extern int Argv;
extern char **Args;

void initgame()
{
    int i,j;
    srand(time(NULL));
    G.playerturn=rand()%2;
    G.rownb=strtol(Args[2],NULL,10);
    G.linenb=strtol(Args[3],NULL,10);
    G.N=strtol(Args[1],NULL,10);
    G.tokensIn=0;
    /*G.players[0].isHuman=rand()%2;
    G.players[1].isHuman=!G.players[0].isHuman;*/
    G.players[0].isHuman=strtol(Args[6],NULL,10);
    G.players[1].isHuman=strtol(Args[7],NULL,10);
    G.players[0].P=4;
    G.players[1].P=4;
    if(strtol(Args[8],NULL,10)) G.players[0].arms=RED; else G.players[0].arms=YELLOW;
    G.players[1].arms=(int)!G.players[0].arms;
    /*G.players[0].arms=rand()%2;
    G.players[1].arms=(int)!G.players[0].arms;*/
    G.Array_state= (TOKEN **) calloc(G.rownb,sizeof(TOKEN*));

    for(i=0;i<G.rownb;i++)
    G.Array_state[i]= (TOKEN *) calloc(G.linenb,sizeof(TOKEN));

    for(i=0;i<G.rownb;i++)
    for(j=0;j<G.linenb;j++)
    G.Array_state[i][j]=EMPTY;

    G.players[0].AI=&brutAI;
    G.players[1].AI=&brutAI;

    if(!G.players[0].isHuman)strcpy(G.players[0].name, "sentient machine");
    if(G.players[0].isHuman)strcpy(G.players[0].name, "human");
    if(!G.players[1].isHuman)strcpy(G.players[1].name, "sentient machine");
    if(G.players[1].isHuman)strcpy(G.players[1].name, "human");
}

struct VideoHandle V;

void initvideo()
{
V.xVscreen=strtol(Args[4],NULL,10);
V.yVscreen=strtol(Args[5],NULL,10);
V.xstep = V.xVscreen/(G.rownb)+0.0;
V.ystep = V.yVscreen/(G.linenb+0.0);

if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 3;
    }

if (SDL_CreateWindowAndRenderer(V.xVscreen, V.yVscreen, 0, &V.window, &V.renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        return 3;
    }
}

void printgrid()
{
    //Clear screen
    SDL_SetRenderDrawColor( V.renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( V.renderer);
    SDL_SetRenderDrawColor( V.renderer, 0x0, 0x0, 0x0, 0xFF );

    int i,j;

    for(i=0;i<=G.rownb;i++)
    SDL_RenderDrawLine(V.renderer,i*V.xstep,0,i*V.xstep,V.yVscreen);

    for(j=0;j<=G.linenb;j++)
    SDL_RenderDrawLine(V.renderer,0,j*V.ystep,V.xVscreen,j*V.ystep);
    SDL_RenderPresent(V.renderer);
}
