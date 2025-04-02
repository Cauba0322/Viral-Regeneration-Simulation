#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  

#define SIZE 20  
#define VIRUS 'X'  
#define DEAD '.'  

char grid[SIZE][SIZE], newGrid[SIZE][SIZE];  

int countNeighbors(int row, int col) {  
    int count = 0;  
    for (int i = -1; i <= 1; i++) {  
        for (int j = -1; j <= 1; j++) {  
            if (i == 0 && j == 0) continue;  
            int nRow = row + i, nCol = col + j;  
            if (nRow >= 0 && nRow < SIZE && nCol >= 0 && nCol < SIZE) {  
                count += (grid[nRow][nCol] == VIRUS);  
            }  
        }  
    }  
    return count;  
}  


void updateGrid() {  
    for (int row = 0; row < SIZE; row++) {  
        for (int col = 0; col < SIZE; col++) {  
            int neighbors = countNeighbors(row, col);  
            if (grid[row][col] == VIRUS) {  
                newGrid[row][col] = (neighbors < 2 || neighbors > 3) ? DEAD : VIRUS;  
            } else {  
                newGrid[row][col] = (neighbors == 3) ? VIRUS : DEAD;  
            }  
        }  
    }  


    for (int row = 0; row < SIZE; row++)  
        for (int col = 0; col < SIZE; col++)  
            grid[row][col] = newGrid[row][col];  
}  


void displayGrid() {  
    printf("\033[H\033[J");  
    for (int row = 0; row < SIZE; row++) {  
        for (int col = 0; col < SIZE; col++) {  
            printf("%c ", grid[row][col]);  
        }  
        printf("\n");  
    }  
}  


void initializeVirus(int virusRow) {  
    for (int row = 0; row < SIZE; row++)  
        for (int col = 0; col < SIZE; col++)  
            grid[row][col] = DEAD;  

    for (int col = 0; col < SIZE; col++)  
        grid[virusRow][col] = VIRUS;  
}  


int main() {  
    int virusRow;  
    printf("Enter the row number (0-%d) where the virus should start: ", SIZE - 1);  
    scanf("%d", &virusRow);  
    

    if (virusRow < 0 || virusRow >= SIZE) {  
        printf("Invalid row. Exiting...\n");  
        return 1;  
    }  
    

    initializeVirus(virusRow);  
    

    while (1) {  
        displayGrid();  
        updateGrid();  
        usleep(200000);  
    }  


    return 0;  
}
