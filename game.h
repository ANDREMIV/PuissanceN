

typedef char TOKEN;

enum TOKENTYPE{
RED,
YELLOW,
EMPTY
};

struct player{
int isHuman;
enum TOKENTYPE arms;
char name[32];
int (*AI)(const struct Game G);
int P;/*nb move to predict for AI*/
};

struct Game{ ///Holds the necessary info to play a particular game
int rownb, linenb, N; //N token to align in order to win
int tokensIn; //Nb of tokens in the grid
TOKEN **Array_state; //the configuration of the tokens in the array
///ArrayState[row-1][line-1]
int playerturn; //0 -> player0 turn, 1 -> player1 turn
struct player players[2]; //player0 is players[0] and so on
};

int AddTokentoGrid(int row,TOKEN value, struct Game *G);
int AskPlayerRow();//return 0 means an error, otherwise it means the Row chosen
int LinesFree(int row, const struct Game G);
TOKEN lastwin(int last_row,const struct Game G); //return WINNER OR EMPTY
int remove_token_to_row(int row, struct Game *G);
int IsGridFull(const struct Game G);
int NextTurn(struct Game *G);
int copyGameState(const struct Game G,struct Game Gn);

extern struct Game G;
extern struct Game Gn;//game neglected
extern struct VideoHandle V;

