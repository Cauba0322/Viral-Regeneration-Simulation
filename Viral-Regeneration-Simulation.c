#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 30
#define VIRUS 'V'
#define DEAD '.'

void setupVirus(int virusRow, char grid[SIZE][SIZE]) {
    
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            grid[row][col] = DEAD;  //
        }
    }
    
    for (int col = 0; col < SIZE; col++) {
        grid[virusRow][col] = VIRUS;  
    }
}

void printGrid(char grid[SIZE][SIZE]) {
    
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            printf("%c ", grid[row][col]);
        }
        printf("\n");
    }
}

int countNeighbors(char grid[SIZE][SIZE], int row, int col) {
    
    int neighbors = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;  
            int nRow = row + i, nCol = col + j;
            if (nRow >= 0 && nRow < SIZE && nCol >= 0 && nCol < SIZE) {
                if (grid[nRow][nCol] == VIRUS) {
                    neighbors++;
                }
            }
        }
    }
    return neighbors;
}

void updateGrid(char grid[SIZE][SIZE], char newGrid[SIZE][SIZE]) {
    
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            int neighbors = countNeighbors(grid, row, col);

            if (grid[row][col] == VIRUS) {
                
                newGrid[row][col] = (neighbors < 2 || neighbors > 3) ? DEAD : VIRUS;
            } else {
              
                newGrid[row][col] = (neighbors == 3) ? VIRUS : DEAD;
            }
        }
    }
}

void copyGrid(char grid[SIZE][SIZE], char newGrid[SIZE][SIZE]) {
    
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            grid[row][col] = newGrid[row][col];
        }
    }
}

void clearScreen() {
   
    #ifdef _WIN32
        system("cls");
    #else
        printf("\033[H\033[J");
    #endif
}

int main() {
    char grid[SIZE][SIZE], newGrid[SIZE][SIZE];
    int virusRow;

    
    printf("Enter the row number (0-%d) where the virus should start: ", SIZE - 1);
    scanf("%d", &virusRow);

    
    if (virusRow < 0 || virusRow >= SIZE) {
        printf("Invalid row. Exiting...\n");
        return 1;
    }

    
    setupVirus(virusRow, grid);

    
    while (1) {
        clearScreen();  /

        printGrid(grid);  

        updateGrid(grid, newGrid);  
        copyGrid(grid, newGrid);    

        sleep(1);  
    }

    return 0;
}
