#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

void winner(int x , int choice){

    if(choice==1){
        printf("\ncomputer choice : paper");
    }
    else if(choice==2){
        printf("\ncomputer choice : rock");
    }
    else if(choice==3){
        printf("\ncomputer choice : scissors");
    }

    if(x==choice){
        printf("\nTie breaker.We both chose the same option");
    }
    else if((x == 1 && choice == 2) || 
         (x == 2 && choice == 3) || 
         (x == 3 && choice == 1)) { 
    printf("\nYou win!");
    }
    else{
        printf("\nComputer win. Better luck next time");
    }
}



void user_choice(int choice){

    
    printf("\nenter your choice : ");
    char ch = toupper(_getch());
    printf("%c",ch);
    
    if(ch=='P' || ch=='R' || ch == 'S'){
        int x;
        switch (ch){
            case 'P':
                x =1;
                printf("\n\nyour choice : paper");
            break;
            case 'R':
                x =2;
                printf("\n\nyour choice : rock");
            break;
            case 'S':
                x =3;
                printf("\n\nyour choice : scissors");
            break;
        }
    winner(x,choice);
    }
    else if(ch=='E'){
        return;
    }
    else{
        printf("\n\nInvalid choice");
        user_choice(choice);
    }
    
}

int main(){

    srand(time(NULL));
    printf("\n\n\nwelcome to the game of rock, paper and scissors");
    printf("\n\nenter 'R' for rock, 'P' for paper, 'S' for scissors and 'E for exit the game");
    int choice = rand()%3 + 1;
    user_choice(choice);

}