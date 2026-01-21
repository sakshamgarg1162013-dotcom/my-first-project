#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 40
#define HEIGHT 20
#define MAX_SNAKE_LENGTH 100

typedef struct {
    int x, y;
} Point;

Point snake[MAX_SNAKE_LENGTH];
int snake_length = 5;
int direction = 0; // 0=RIGHT, 1=DOWN, 2=LEFT, 3=UP
Point food;

int game_over = 0;

void gotoxy(int x, int y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void draw_border() {
    for (int i = 0; i <= WIDTH; i++) {
        gotoxy(i, 0); printf("#");
        gotoxy(i, HEIGHT); printf("#");
    }
    for (int i = 0; i <= HEIGHT; i++) {
        gotoxy(0, i); printf("#");
        gotoxy(WIDTH, i); printf("#");
    }
}

void generate_food() {
    food.x = rand() % (WIDTH - 2) + 1;
    food.y = rand() % (HEIGHT - 2) + 1;
}

void init_game() {
    system("cls");
    srand(time(NULL));
    snake_length = 5;
    for (int i = 0; i < snake_length; i++) {
        snake[i].x = 10 - i;
        snake[i].y = 10;
    }
    generate_food();
    draw_border();
}

void draw_snake() {
    for (int i = 0; i < snake_length; i++) {
        gotoxy(snake[i].x, snake[i].y);
        printf(i == 0 ? "O" : "o");
    }
    gotoxy(food.x, food.y);
    printf("F");
}

void erase_tail() {
    gotoxy(snake[snake_length - 1].x, snake[snake_length - 1].y);
    printf(" ");
}

void move_snake() {
    // Move body
    for (int i = snake_length - 1; i > 0; i--)
        snake[i] = snake[i - 1];

    // Move head
    switch (direction) {
        case 0: snake[0].x++; break;
        case 1: snake[0].y++; break;
        case 2: snake[0].x--; break;
        case 3: snake[0].y--; break;
    }
}

void check_collision() {
    // Wall collision
    if (snake[0].x == 0 || snake[0].x == WIDTH ||
        snake[0].y == 0 || snake[0].y == HEIGHT)
        game_over = 1;

    // Self collision
    for (int i = 1; i < snake_length; i++)
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
            game_over = 1;

    // Food collision
    if (snake[0].x == food.x && snake[0].y == food.y) {
        snake_length++;
        generate_food();
    }
}

void input() {
    if (_kbhit()) {
        char ch = _getch();
        switch (ch) {
            case 'w': if (direction != 1) direction = 3; break;
            case 's': if (direction != 3) direction = 1; break;
            case 'a': if (direction != 0) direction = 2; break;
            case 'd': if (direction != 2) direction = 0; break;
            case 'x': game_over = 1; break;
        }
    }
}

int main() {
    init_game();

    while (!game_over) {
        erase_tail();
        input();
        move_snake();
        check_collision();
        draw_snake();
        Sleep(100); // adjust speed
    }

    gotoxy(0, HEIGHT + 2);
    printf("\nGame Over! Your score: %d\n", snake_length - 5);
    return 0;
}
