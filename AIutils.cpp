#include <stdio.h>
#include <stdlib.h>
#include "game.h"

///returned pointer must be freed even if nb_move is 0 !
int* find_possible_moves(int* nb_move)//return pointer to an index of possible moves
{
    int nb=0;
    int i,row_nb=G.rownb;
    for(i=0;i<row_nb;i++)
            if(LinesFree(i+1))
                nb++;
    int* ptr=(int*) malloc(nb*sizeof(int));
    int a=0;
    if(nb)
    for(i=0;i<row_nb;i++)
            if(LinesFree(i+1))
                ptr[i-a]=i+1;
            else ++a;

    *nb_move=nb;
    return ptr;
}

///return next possible row to play after previous row
int nextmove(int prow)
{
    int i,row_nb=G.rownb;

        for(i=prow;i<row_nb;i++)
            if(LinesFree(i+1))
                return i+1;

    return 0;
}

choosemaxrow(int *rs,int nb_pmov)
{
    int *row_scores=rs;
    int i; int lmax=*row_scores; int imax=0; int occ=0;
                    for(i=0;i<nb_pmov;i++) ///Choose row with max score
                        if(row_scores[i]>lmax)
                        {
                            lmax=row_scores[i];
                            imax=i;
                            occ=0;
                        }
                        else if(row_scores[i]==lmax)
                            occ++;
                    if(occ) ///Choose randomly between max score rows
                        {
                        int a=rand()%(occ+1);
                        for(i=0;i<nb_pmov;i++)
                        if(row_scores[i]==lmax)
                        if(a)a--;
                        else return i;
                        }
                    return imax;
}


