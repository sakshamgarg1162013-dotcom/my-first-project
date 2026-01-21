#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int player ;
    int computer ;
    int draw ;
}Score;


int difficulty;
Score score = {.player = 0, .computer = 0, .draw = 0};

void input_difficulty();
void clear_screen();
void print_board(char board[3][3]);
int check_win(char board[3][3],char player);
int check_draw(char board[3][3]);
void play_game();
void player_move(char board[3][3]);
void computer_move(char board[3][3]);
int valid_move(char board[3][3],int row,int col);

int main(){
    srand(time(NULL));
    int choice;
    input_difficulty();
    do{
        play_game();
        printf("\ndo you want to play again?(1 for yes and 0 for no) : ");
        scanf("%d",&choice);
    }while(choice==1);
    printf("bye bye thanks for playing");
    
}
void play_game(){
    char board[3][3] = {
        {' ' , ' ' , ' '},
        {' ' , ' ' , ' '},
        {' ' , ' ' , ' '}
    };

    char current_player= rand()%2==0 ? 'X' : 'O';
    print_board(board);

    while(1){
        
        if(current_player=='X'){
        player_move(board);
        print_board(board);
        if (check_win(board,'X')){
            score.player++;
            print_board(board);
            printf("\ncongratulation you have won");
            break;
        }
        current_player='O';
    }    
        else{
        computer_move(board);
        print_board(board);
            if(check_win(board,'O')){
                score.computer++;
                print_board(board);
                printf("i won. try again");
                break;
            }
            current_player = 'X';
        }
        
        if(check_draw(board)){
            score.draw++;
            printf("\nit's a draw");
            break;
        }
        
    }
}

int valid_move(char board[3][3],int row,int col){
    return !(row<0 || row>2 || col<0 || col>2 || board[row][col]!= ' ');
}

void player_move(char board[3][3]){
    int count =0 ,x ,y;
    for(int i = 0; i<3 ;i++){
        for(int j =0;j<3;j++){
            if(board[i][j]==' '){
                count++;
                x=i;
                y=j;
            }
        }
    }

    if(count==1){
        board[x][y]='X';
        return;
    }


    int row, col;
    do{
        printf("\nplayer X's turn");
        printf("\nenter row and column(1-3) for X: ");
        scanf("%d",&row);
        scanf("%d",&col);

        row--;col--;
    }while(!valid_move(board, row, col));
    board[row][col]= 'X';
}

void computer_move(char board[3][3]){

    for(int i = 0; i < 3; i++){
        for(int j = 0;j < 3;j++){
           if(board[i][j]== ' '){
            board[i][j]= 'O';
            if(check_win(board,'O')){
                return;
            }
           board[i][j]= ' ';
           }
          
        }
    }

    for(int i =0;i<3;i++){
        for(int j =0;j<3;j++){
           if(board[i][j]==' '){
            board[i][j]= 'X';
            if(check_win(board,'X')){
             board[i][j]= 'O';
             return;
           }
           board[i][j]= ' ';
           }   
        }
    }

    if(difficulty==2){
        if(board[1][1]==' '){
            board[1][1]='O';
            return;
        }

        int corner[4][2] = {
            {0,0},
            {0,2},
            {2,0},
            {2,2}
        };
        for(int i =0;i<4;i++){
            if(board[corner[i][0]][corner[0][i]] == ' '){
                board[corner[i][0]][corner[0][i]] = 'O';
                return;
            }
        }



    }

    for(int i =0;i<3;i++){
        for(int j =0;j<3;j++){
           if(board[i][j]==' '){
            board[i][j]='O';
            return;
           }
        }
    }
}

int check_win(char board[3][3],char player){
    for(int i =0;i<3;i++){
        if(board[i][0]==player && board[i][1]==player && board[i][2]==player){
            return 1;
        }
        if(board[0][i]==player && board[1][i]==player && board[2][i]==player){
            return 1;
        }
        if((board[0][0]==player && board[1][1]==player && board[2][2]==player) || (board[0][2]==player && board[1][1]==player && board[2][0]==player)){
            return 1;
        }
    }
    return 0;
}

int check_draw(char board[3][3]){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]==' ')return 0;
        }
    }
    return 1;
}

void print_board(char board[3][3]){
    clear_screen();
    printf("\nscore - player x: %d , computer: %d , draw: %d",score.player,score.computer,score.draw);
    printf("\ntictactoe\n");

    for(int i=0;i<3;i++){
        printf("\n");
        for(int j=0;j<3;j++){
            printf(" %c ", board[i][j]);
            if(j<2){
                printf("|");
            }
        }
        if(i<2){
            printf("\n---+---+---");
        }
        
    }
    
}

void input_difficulty(){
    while(1){
    printf("\nselect difficulty level");
    printf("\n1.human");
    printf("\n2.god(impossible to win)");
    printf("\nenter your choice : ");
    scanf("%d",&difficulty);
    if(difficulty!=1 && difficulty!=2){
        printf("invalid choice\n");
    }
    else{
        break;
    }
    }
}

void clear_screen(){
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}