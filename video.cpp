#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "game.h"
#include "video.h"
#include <SDL_render.h>


PrintLastToken(int row)
{
if(G.players[G.playerturn].arms==RED)
SDL_SetRenderDrawColor( V.renderer, 0xFF, 0x00, 0x00, 0xFF ); //red
else
SDL_SetRenderDrawColor( V.renderer, 0xFF, 0xFF, 0x00, 0xFF ); //yellow


#define NICERADIUS 4/10
int line=LinesFree(row)+1;

double precision;
if(V.xstep>V.ystep)precision=1.0/2/V.xstep;else precision=1.0/2/V.ystep;

for(double i = 0.0; i < 360; i+= precision)
        SDL_RenderDrawLine(V.renderer,V.xstep*(row-1/2.0),V.ystep*(line-1/2.0),
        V.xstep*(row-1/2.0+cos(i)*NICERADIUS),V.ystep*(line-1/2.0+sin(i)*NICERADIUS));
SDL_RenderPresent(V.renderer);

}
