#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>

const char *pink = "\033[1;35m";
const char *yellow = "\033[1;33m";
const char *green = "\033[1;32m";
const char *blue = "\033[1;34m";
const char *aqua = "\033[1;36m";
const char *red = "\033[1;31m";
const char *color_end = "\033[0m";

typedef struct {
    char text[300];
    char options[4][100];
    char correct_option;
    int timeout;
    int prize_money;
}question;

int read_questions(char*file_name,question **questions);
void print_formatted_questions(question questions);
void play_game(question *questions,int no_of_questions);
int use_lifeline(question *questions , int *lifeline);


int main(){
    srand(time(NULL));
    printf("\t\t%sChalo khelte hai kaun banega crorepati%s\n",pink,color_end);
    question *questions;
    int no_of_questions = read_questions("questions.txt", &questions);
    play_game(questions,no_of_questions);
}

void timeout_handler(){

}

void play_game(question *questions, int no_of_questions) {
    int money_won = 0;
    int lifeline[] = {1, 1};

    for (int i = 0; i < no_of_questions; i++) {
        print_formatted_questions(questions[i]);
        char ch = '\0';
        int timeout = questions[i].timeout;
        time_t start_time = time(NULL);
        while (1) {
            if (_kbhit()) {
                ch = _getch();
                break;
            }
            if (difftime(time(NULL), start_time) >= timeout) {
                break;
            }
        }

        if (ch == '\0') {
            printf("%s\nTime's up!%s", red, color_end);
            break;
        }

        printf("%c", ch);
        ch = toupper(ch);

        if (ch == 'L') {
            int value = use_lifeline(&questions[i], lifeline);
            if (value != 2) {
                i--; 
            }
            continue;
        }

        if (ch == questions[i].correct_option) {
            printf("%s\nCorrect!%s", green, color_end);
            money_won = questions[i].prize_money;
            printf("%s\nYou have won Rs..%d.%s", blue, money_won, color_end);
        } else {
            printf("%s\nWrong! The correct answer was %c.%s", red, questions[i].correct_option, color_end);
            break;
        }
    }

    printf("%s\n\nGame over. Your total winnings are Rs..%d.%s", blue, money_won, color_end);
}


int use_lifeline(question *questions , int *lifeline){
    printf("\n\n%sAvailable Lifelines:%s", pink, color_end);
  if (lifeline[0]) printf("\n%s1. Fifty-Fifty (50/50)%s", pink, color_end);
  if (lifeline[1]) printf("\n%s2. Skip the Question%s", pink, color_end);
  printf("\n%sChoose a lifeline or 0 to return: %s", pink, color_end);

  char ch = _getch();
  printf("%c",ch);

  switch (ch){
  case '1':
    if(lifeline[0]){
        lifeline[0]=0;
        int removed =0;
        while(removed<2){
            int num = rand()%4;
            if(num + 'A' !=questions->correct_option && questions->options[num][0] != '\0'){
                questions->options[num][0] = '\0';
                removed ++;
            }
        }
        return 1;
    }
    break;
  case '2':
    if(lifeline[1]){
        lifeline[1]=0;
        return 2;
    }
    break;
  default:
    printf("\n%sreturning to the question%s", pink, color_end);
    return 0;
    break;
  }
  return 0;
}

void print_formatted_questions(question questions){
    printf("\n\n%s%s%s",yellow,questions.text,color_end);

    for(int i= 0;i<4;i++){
        if(questions.options[i][0]!='\0'){
            printf("%s%c. %s%s",aqua, ('A' + i),questions.options[i],color_end);
        }
        
    }

    printf("\n%shurry you have only %d seconds to answer%s",yellow,questions.timeout,color_end);
    printf("%s\nenter your answer(A, B, C, D) or L for lifeline : %s",green,color_end);

    
}

int read_questions(char*file_name,question **questions){
    FILE *file = fopen(file_name,"r");
    if(file==NULL){
        printf("\nfile is unable to open");
        exit(0);
    }

    char str[300];
    int no_of_lines=0;
    while(fgets(str,300,file)){
        no_of_lines++;
    }
    int no_of_questions = no_of_lines/8;
    *questions = (question *) malloc(no_of_questions*sizeof(question));
    rewind(file);
    
    for(int i =0; i<no_of_questions;i++){
        fgets((*questions)[i].text,300,file);
        for(int j=0;j<4;j++){
            fgets((*questions)[i].options[j],100,file);
        }
        char option[10];
        fgets(option,10,file);
        (*questions)[i].correct_option = option[0];

        char timeout[10];
        fgets(timeout,10,file);
        (*questions)[i].timeout = atoi(timeout);

        char prize_money[10];
        fgets(prize_money,10,file);
        (*questions)[i].prize_money = atoi(prize_money);
    }
    fclose(file);
    return no_of_questions;
}