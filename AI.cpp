#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int* find_possible_moves(int* nb_move,const struct Game G);
int nextmove(int prow,const struct Game G);
int choosemaxrow(int *rs,int nb_pmov);


int randomAI(const struct Game G)
{

    int row_nb=G.rownb;
    int choice;
    while(1)
    {
        choice=rand()%row_nb+1;
        if(LinesFree(choice,G))return choice;
    }

}

int brutAI(const struct Game G)
{
    int nbE=G.players[G.playerturn].P; /*nb stage*/ int X=0; /*interruption flag of win*/
    int C; /*choice of row*/ int rownb=G.rownb;
    { //prevents nbE to be superior than the number of tokens that can be put
        int i;int j=0;
        for(i=0;i<rownb;i++)
            j+=LinesFree(i+1,G);
        if(nbE>j)nbE=j;
    }

    int* mS = (int*) calloc(nbE,sizeof(int)); //max scores of a branch E
    int* LC = (int*) calloc(nbE,sizeof(int)); //last token chosen at stage E
    int* AEF = (int*) calloc(nbE,sizeof(int)); //scores first time set flag ?
    int E=-1; //current stage, level
    int rowsFreeNb;
    int* rows0=find_possible_moves(&rowsFreeNb,G);

    int* scores0 = (int*) calloc(rowsFreeNb,sizeof(int));
    int S0i=0; //index for scores0

    //int G=0; ///debug
    begin:

       /* if(LC[0]==2&&LC[1]==6){

            G=1;
        }*/


    if(E==nbE-1) //Are we at the top of the branch
    {
      mS[E]=0;
      AEF[E]=1;
      goto branch_end;
    }
    else
    {
        C=nextmove(LC[E+1],G);
        if(C) //Still some move to play ?
        {
            //Y so add token and go up
            if((E+1)%2) //add token according to the right color
            AddTokentoGrid(C,G.players[!G.playerturn].arms,&G);
            else
            AddTokentoGrid(C,G.players[G.playerturn].arms,&G);


            /*if(G&&LC[0]==2&&LC[1]==6){display_Ggrid();///debug
             {
                 int l;
                 for(l=0;l<nbE;l++)
                    printf("\n%d)\t%d\n", l,mS[l]);
             }
             system("pause");
             G=0;

            }*/


            E++;
            LC[E]=C;
            if(lastwin(C,G)!=EMPTY) //someone won
            {
                X=1;
                mS[E]=1;
                AEF[E]=1;
                goto branch_end;
            }
            else //nobody won on the last move
            {
                goto begin;
            }
        }
        else{ //no more moves to play on that branch
            if(E==-1)
                goto get_out; //no more moves to play at all
            else
                goto branch_end;
        }
    }

    branch_end:
    remove_token_to_row(LC[E],&G);
    //display_Ggrid();Sleep(40);
    AEF[E]=0;
    E--;
    if(X)
    {
        X=0;
        LC[E+1]=rownb;
    }
    if(E==-1)
    {
        scores0[S0i]=mS[0];
        S0i++;
    }else{
    if(AEF[E])
    {
        mS[E]=-mS[E] > mS[E+1] ? -mS[E] : mS[E+1];
        mS[E]*=-1;
        }
    else
    {
        AEF[E]=1;
        mS[E]=-mS[E+1];
    }
    }
    if(E<=nbE-3)
    {
        LC[E+2]=0;
        AEF[E+2]=0;
    }
    goto begin;


    get_out:

        {
            int l; int lmax=0;
            for(l=0;l<rowsFreeNb;l++)
                if(scores0[lmax]<scores0[l])
                lmax=l;
               /* for(l=0;l<rowsFreeNb;l++)
                    printf("\n%d)\t%d\n", l,scores0[l]);
                system("pause");*/
                //C=rows0[lmax];
                C=rows0[choosemaxrow(scores0,rowsFreeNb)];
        }

        return C;

}
