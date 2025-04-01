#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


#define SIZE 20
#define ALIVE 'X'
#define DEAD '.'
#define DELAY 200000 


void initializeGrid(int grid[SIZE][SIZE]);
void displayGrid(int grid[SIZE][SIZE]);
int countNeighbors(int grid[SIZE][SIZE], int x, int y);
void updateGrid(int grid[SIZE][SIZE], int newGrid[SIZE][SIZE]);
void copyGrid(int grid[SIZE][SIZE], int newGrid[SIZE][SIZE]);

int main() {
    srand(time(NULL)); 
    int grid[SIZE][SIZE];
    int newGrid[SIZE][SIZE];

    initializeGrid(grid);
    while (1) {
        displayGrid(grid);
        updateGrid(grid, newGrid);
        copyGrid(newGrid, grid);
        usleep(DELAY);
    }

    return 0;
}


void initializeGrid(int grid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = rand() % 2;
        }
    }
}


void displayGrid(int grid[SIZE][SIZE]) {
    printf("\033[H"); 
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", grid[i][j] ? ALIVE : DEAD);
        }
        printf("\n");
    }
}


int countNeighbors(int grid[SIZE][SIZE], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; 
            int nx = x + i, ny = y + j;
            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE) {
                count += grid[nx][ny];
            }
        }
    }
    return count;
}


void updateGrid(int grid[SIZE][SIZE], int newGrid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int neighbors = countNeighbors(grid, i, j);
            if (grid[i][j] == 1) {
                if (neighbors < 2 || neighbors > 3) newGrid[i][j] = 0;
                else newGrid[i][j] = 1;
            } else {
                if (neighbors == 3) newGrid[i][j] = 1;
                else newGrid[i][j] = 0;
            }
        }
    }
}


void copyGrid(int grid[SIZE][SIZE], int newGrid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = newGrid[i][j];
        }
    }
}