#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "video.h"
#include <SDL_events.h>

AddTokentoGrid(int row,TOKEN value, struct Game *G)
//it is assumed that the row is not full
{
int i,row_nb=G->rownb,line_nb=G->linenb;
for(i=0;i<line_nb&&G->Array_state[row-1][i]!=EMPTY;i++);
G->Array_state[row-1][i]=value;
}

remove_token_to_row(int row, struct Game *G)
{
int i,line_nb=G->linenb;
for(i=0;i<line_nb&&G->Array_state[row-1][i]!=EMPTY;i++);
if(i>0)i--;
G->Array_state[row-1][i]=EMPTY;
}

//return number of tokens we could put onto the row
int LinesFree(int row, const struct Game G)
{
    int i,line_nb=G.linenb;
    for(i=0;i<line_nb&&G.Array_state[row-1][i]!=EMPTY;i++);
    return line_nb-i;
}

int AskPlayerRow()
{
    if(G.players[G.playerturn].isHuman)
    {
    int row;

    while(1)
    {
    printf("\n\nYour turn, which row shall you play ?\n");

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
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        row = e.button.x/V.xstep+1;
        e.type=SDL_FIRSTEVENT;
        break;
    }
    e.type=SDL_FIRSTEVENT;
    SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
}

    if(LinesFree(row,G))
    break;
    printf("\n\nRow is full !");
    }
    return row;
    }
    else
    return G.players[G.playerturn].AI(G);
}

TOKEN lastwin(int last_row,const struct Game G) //return WINNER OR EMPTY
{/// CAREFULL EMPTY IS NOT ZERO
    //checks if the global grid contain a win
    int i,j,k,row_nb=G.rownb,line_nb=G.linenb
    ,nb_to_win=G.N;

    //last token and init i and j
    for(j=0;j<line_nb&&G.Array_state[last_row-1][j]!=TOKEN(EMPTY);j++);
    if(--j<0)return EMPTY;
    TOKEN t=G.Array_state[last_row-1][j];
    i=last_row-1;
    ///NOW i is row-1 and j is line-1

            int nb;
            nb=1;
            ///CHECK UP (not needed)
            /*for(k=1;k<nb_to_win&&j+k<line_nb&&G->Array_state[i][j+k]==t;k++);
            nb+=--k;
            if(nb>=nb_to_win)return t;*/
            ///CHECK DOWN
            for(k=1;k<nb_to_win&&j-k>=0&&G.Array_state[i][j-k]==t;k++);
            nb+=--k;
            if(nb>=nb_to_win)return t;

            nb=1;
            ///CHECK RIGHT UP
            for(k=1;k<nb_to_win&&j+k<line_nb&&i+k<row_nb&&G.Array_state[i+k][j+k]==t;k++);
            nb+=--k;
            if(nb>=nb_to_win)return t;
            ///CHECK LEFT DOWN
            for(k=1;k<nb_to_win&&j-k>=0&&i-k>=0&&G.Array_state[i-k][j-k]==t;k++);
            nb+=--k;
            if(nb>=nb_to_win)return t;

            nb=1;
            ///CHECK RIGHT
            for(k=1;k<nb_to_win&&i+k<row_nb&&G.Array_state[i+k][j]==t;k++);
            nb+=--k;
            if(nb>=nb_to_win)return t;
            ///CHECK LEFT
            for(k=1;k<nb_to_win&&i-k>=0&&G.Array_state[i-k][j]==t;k++);
            nb+=--k;
            if(nb>=nb_to_win)return t;

            nb=1;
            ///CHECK RIGHT DOWN
            for(k=1;k<nb_to_win&&j-k>=0&&i+k<row_nb&&G.Array_state[i+k][j-k]==t;k++);
            nb+=--k;
            if(nb>=nb_to_win)return t;
            ///CHECK LEFT UP
            for(k=1;k<nb_to_win&&j+k<line_nb&&i-k>=0&&G.Array_state[i-k][j+k]==t;k++);
            nb+=--k;
            if(nb>=nb_to_win)return t;

    return EMPTY;
}

NextTurn(struct Game *G)
{
G->playerturn=!G->playerturn;
G->tokensIn++;
}

IsGridFull(const struct Game G)
{
    if(G.tokensIn==G.linenb*G.rownb)
    return 1;
    else return 0;
}
