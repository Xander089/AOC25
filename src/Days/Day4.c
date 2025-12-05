#include "Day4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEWLINE_CHAR 10
#define LINE_LEN 140

void printGrid(int **grid)
{
    for (int i = 0; i < LINE_LEN; i++)
    {
        for (int j = 0; j < LINE_LEN; j++)
        {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

void scanLine(char *line, int *row)
{
    int cursor = 0;
    while (cursor < LINE_LEN)
    {
        int numchar = line[cursor] == '.' ? 0 : 1;
        row[cursor] = numchar;
        cursor++;
    }
}

void scan(char *fileName, int **grid)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    char buffer[LINE_LEN + 2]; // +2 for newline and null terminator
    int row = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        scanLine(buffer, grid[row++]);
    }

    fclose(file);
}

int count(int **grid, int row, int col)
{
    int leftTop = row == 0 && col == 0;
    int rightTop = row == 0 && col == LINE_LEN - 1;
    int leftBottom = row == LINE_LEN - 1 && col == 0;
    int rightBottom = row == LINE_LEN - 1 && col == LINE_LEN - 1;

    int topRow = (row == 0) && !(leftTop || rightTop);
    int bottomRow = (row == LINE_LEN - 1) && !(leftBottom || rightBottom);
    int leftCol = (col == 0) && !(leftTop || leftBottom);
    int rightCol = (col == LINE_LEN - 1) && !(rightTop || rightBottom);

    if (leftTop)
    {
        return grid[row][col + 1] + grid[row + 1][col] + grid[row + 1][col + 1];
    }
    if (rightTop)
    {
        return grid[row][col - 1] + grid[row + 1][col] + grid[row + 1][col - 1];
    }
    if (leftBottom)
    {
        return grid[row - 1][col] + grid[row][col + 1] + grid[row - 1][col + 1];
    }
    if (rightBottom)
    {
        return grid[row - 1][col] + grid[row][col - 1] + grid[row - 1][col - 1];
    }
    if (topRow)
    {
        return grid[row][col - 1] + grid[row][col + 1] + grid[row + 1][col - 1] + grid[row + 1][col] + grid[row + 1][col + 1];
    }
    if (bottomRow)
    {
        return grid[row - 1][col - 1] + grid[row - 1][col] + grid[row - 1][col + 1] + grid[row][col - 1] + grid[row][col + 1];
    }
    if (leftCol)
    {
        return grid[row - 1][col] + grid[row - 1][col + 1] + grid[row][col + 1] + grid[row + 1][col] + grid[row + 1][col + 1];
    }
    if (rightCol)
    {
        return grid[row - 1][col - 1] + grid[row - 1][col] + grid[row][col - 1] + grid[row + 1][col - 1] + grid[row + 1][col];
    }
    return grid[row - 1][col - 1] + grid[row - 1][col] + grid[row - 1][col + 1] + grid[row][col - 1] + grid[row][col + 1] + grid[row + 1][col - 1] + grid[row + 1][col] + grid[row + 1][col + 1];
}

int **crateGrid(int size)
{
    int **grid = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        grid[i] = (int *)malloc(size * sizeof(int));
    }
    return grid;
}

void freeGrid(int **grid)
{
    for (int i = 0; i < LINE_LEN; i++)
    {
        free(grid[i]);
    }
    free(grid);
}

int firstScan(int **grid, int *validIndexes)
{
    int index = 0;
    for (int i = 0; i < LINE_LEN; i++)
        for (int j = 0; j < LINE_LEN; j++)
        {
            if (grid[i][j] != 0)
                validIndexes[index++] = i * LINE_LEN + j;
        }
    return index;
}

long d4_execute()
{
    char *fileName = "input4.txt";
    int **grid = crateGrid(LINE_LEN);

    scan(fileName, grid); // populate the grid

    int *validIndexes = (int *)malloc(LINE_LEN * LINE_LEN * sizeof(int));
    memset(validIndexes, -1, LINE_LEN * LINE_LEN * sizeof(int));
    int validCount = firstScan(grid, validIndexes);
    int result = 0;
    int removedElements = 1;
    int lastValid = -1;
    while (removedElements > 0)
    {
        removedElements = 0;
        for (int i = 0; i < validCount; i++)
        {
            if (validIndexes[i] == -1)
                continue; // skip already removed elements

            int row = validIndexes[i] / LINE_LEN;
            int col = validIndexes[i] % LINE_LEN;

            // requirement is to check for less than 4 neighbors
            if (count(grid, row, col) < 4)
            {
                removedElements += 1;
                grid[row][col] = 0;   // remove the element
                validIndexes[i] = -1; // mark as removed
            }
            else
            {
                lastValid = i;
            }
        }

        validCount = lastValid + 1;
        result += removedElements;
    }

    freeGrid(grid);
    free(validIndexes);
    printf("Result: %d\n", result);

    return 0;
}
