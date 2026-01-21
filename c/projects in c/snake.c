#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define HEIGHT 20
#define WIDTH 60

enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STOP
};

enum direction dir;

int score = 0;
int fruit_x, fruit_y;
int head_x, head_y;

void draw();
void setup();
void game_play();
void input();
void gotoXY(int x, int y);
void hideCursor();

int main() {
    srand(time(NULL));
    setup();
    hideCursor();  // Hide blinking console cursor
    while (1) {
        draw();
        input();
        game_play();
        int speed = 150 - score;
        if (speed < 50) speed = 50;

        Sleep(speed);
    }
    return 0;
}

void game_play() {
    switch (dir) {
        case UP: head_y--; break;
        case DOWN: head_y++; break;
        case LEFT: head_x--; break;
        case RIGHT: head_x++; break;
        default: break;
    }
    if (head_x < 0) head_x = WIDTH - 1;
    if (head_x >= WIDTH) head_x = 0;
    if (head_y < 0) head_y = HEIGHT - 1;
    if (head_y >= HEIGHT) head_y = 0;
    if (head_x == fruit_x && head_y == fruit_y) {
        score += 10;
        fruit_x = rand() % WIDTH;
        fruit_y = rand() % HEIGHT;
    }
}

void input() {
    if (_kbhit()) {
        char ch = _getch();
        switch (ch) {
            case 'a': if (dir != RIGHT) dir = LEFT; break;
            case 'd': if (dir != LEFT) dir = RIGHT; break;
            case 'w': if (dir != DOWN) dir = UP; break;
            case 's': if (dir != UP) dir = DOWN; break;
            case 'x': exit(0); break;
        }
    }
}

void draw() {
    gotoXY(0, 0);  // Move cursor to top-left, avoids flickering

    printf("\t\tWelcome to the Snake Game\n");
    
    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        printf("#");
        for (int j = 0; j < WIDTH; j++) {
            if (i == head_y && j == head_x)
                printf("O");
            else if (i == fruit_y && j == fruit_x)
                printf("F");
            else
                printf(" ");
        }
        printf("#\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\nScore: %d\n", score);
}

void setup() {
    head_x = WIDTH / 2;
    head_y = HEIGHT / 2;
    fruit_x = rand() % WIDTH;
    fruit_y = rand() % HEIGHT;
    dir = STOP;
}

void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
