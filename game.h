

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
int (*AI)();
};

struct Game{ ///Holds the necessary info to play a particular game
int rownb, linenb, N; //N token to align in order to win
int tokensIn; //Nb of tokens in the grid
TOKEN **Array_state; //the configuration of the tokens in the array
///ArrayState[row-1][line-1]
int playerturn; //0 -> player0 turn, 1 -> player1 turn
struct player players[2]; //player0 is players[0] and so on
};

int AddTokentoGrid(int row,TOKEN value);
int AskPlayerRow();//return 0 means an error, otherwise it means the Row chosen
int LinesFree(int choice);
TOKEN lastwin(int last_row); //return WINNER OR EMPTY
int remove_token_to_row(int row);

extern struct Game G;
extern struct VideoHandle V;

