#include <stdio.h>
#include <stdlib.h>
#include "game.h"

///Features to be implemented
///When loosing, do loose in the longest time
///Manage menace and parity
///Do not place token on his own menace
///Arrange tokens to maximize combinations and anti-combinations

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

int brutAIV2(const struct Game G)
{
        return randomAI(G);
}

int brutAI(const struct Game G)
{
    int nbE=G.players[G.playerturn].P; /*nb stage*/
    if(nbE==0)//random AI
        return randomAI(G);
    int X=0; /*interruption flag of win*/ //allows to skip the checking of the other possibilities
    int C; /*choice of row*/ int rownb=G.rownb;
    {
        //prevents nbE to be superior than the number of tokens that can be put
        int i;
        int j=0;
        for(i=0; i<rownb; i++)
            j+=LinesFree(i+1,G);
        if(nbE>j)nbE=j;
    }

    int* mS = (int*) calloc(nbE,sizeof(int)); //max scores of a branch E
    int* LC = (int*) calloc(nbE,sizeof(int)); //last token chosen at stage E
    //LC[0] stores the first move
    int* AEF = (int*) calloc(nbE,sizeof(int)); //scores first time set flag ?
    int E=-1; //current stage, level
    int rowsFreeNb;
    int* rows0=find_possible_moves(&rowsFreeNb,G);//it stores the row of the ieme possible row
    int* scores0 = (int*) calloc(rowsFreeNb,sizeof(int));//it stores the score of the ieme possible row
    int* worstloss= (int*) calloc(rowsFreeNb,sizeof(int));
    int S0i=0; //index for scores0


Can_Place_token:

    if(E==nbE-1) //Are we at the top of the branch
    {
        mS[E]=0;//set score to 0 because if we managed to get here that means no win occurred
        AEF[E]=1; //notify score is set
        goto branch_end;
    }
    else
    {
        C=nextmove(LC[E+1],G);//next possible move for current stage directly after previous row
        if(C) //Still some move to play ?
        {
            //Y so add token and go up
            if((E+1)%2) //add token according to the right color
                AddTokentoGrid(C,G.players[!G.playerturn].arms,&G);
            else
                AddTokentoGrid(C,G.players[G.playerturn].arms,&G);
            //AddTokentoGrid(C,G.players[(G.playerturn+E)%2].arms,&G);

            E++;
            worstloss[S0i] = E > worstloss[S0i] ? E:worstloss[S0i];
            LC[E]=C;
            if(lastwin(C,G)!=EMPTY) //someone won
            {
                X=1; //to notify that someone won to the branch_end procedure
                mS[E]=1;
                AEF[E]=1;
                goto branch_end;
            }
            else //nobody won on the last move
            {
                goto Can_Place_token;
            }
        }
        else  //no more moves to play on that branch
        {
            if(E==-1)
                goto get_out; //no more moves to play at all
            else
                goto branch_end;
        }
    }

branch_end:
    remove_token_to_row(LC[E],&G);
    AEF[E]=0;
    E--;
    if(X)//a win occurred, no need to check other possibilities in the branch
    {
        X=0;//reset flag
        LC[E+1]=rownb; //allows to skip the checking of the other possibilities
    }
    if(E==-1)//So we have our score row
    {
        scores0[S0i]=mS[0]; //So save it externally because ms[0] will be used for next row
        S0i++;
    }
    else
    {
        if(AEF[E]) //this source branch already has a score
        {
            mS[E]=-mS[E] > mS[E+1] ? -mS[E] : mS[E+1];//so take the max of it
            mS[E]*=-1; //the best score from a previous branch is the worst for the parent
        }
        else //branch score not set
        {
            AEF[E]=1;// so tell it is now set
            mS[E]=-mS[E+1]; //set it
        }
    }
    if(E<=nbE-3)
        LC[E+2]=0; //reinit all possible moves for higher branches

    goto Can_Place_token;


get_out:


    /*int l; int lmax=0;
    for(l=0;l<rowsFreeNb;l++)
        if(scores0[lmax]<scores0[l])
        lmax=l;*/
    C=rows0[choosemaxrow(scores0,rowsFreeNb)];
    {

        int i;
        for(i=0; i<rownb; i++)
            if(rows0[i]==C)break;
        if(scores0[i]<0)//if forced win for the opponent then maximize time before loosing
        {
            int worstlossmax=worstloss[0];
            for(i=1; i<rowsFreeNb; i++)
                worstlossmax = worstloss[i] > worstlossmax ? worstloss[i]:worstlossmax;
            for(i=0; i<rowsFreeNb; i++)
            {
                scores0[i]-=worstlossmax;
                scores0[i]+=worstloss[i];
            }
        }
        else if(scores0[i]==0)//give more weight to central rows
            for(i=0; i<rowsFreeNb; i++)
                if ((scores0[i]==0)&&(rows0[i]>=G.N-1)&&(rows0[i]<=G.rownb-G.N+2))
                    scores0[i]++;
    }
    C=rows0[choosemaxrow(scores0,rowsFreeNb)];


    free(worstloss);
    free(mS);
    free(LC);
    free(scores0);
    free(AEF);
    free(rows0);
    return C;
}
