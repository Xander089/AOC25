#include "Day4.h"
#include <stdio.h>
#include <stdlib.h>

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

long d4_execute()
{
    char *fileName = "input4.txt";

    int **grid = (int **)malloc(LINE_LEN * sizeof(int *));
    for (int i = 0; i < LINE_LEN; i++)
    {
        grid[i] = (int *)malloc(LINE_LEN * sizeof(int));
    }

    // populate the grid
    scan(fileName, grid);

    int result = 0;
    int removedElements = 1;
    while (removedElements > 0)
    {
        removedElements = 0;
        for (int i = 0; i < LINE_LEN; i++)
            for (int j = 0; j < LINE_LEN; j++)
            {
                // skip the already removed elements
                if (grid[i][j] == 0)
                    continue;

                // requirement is to check for less than 4 neighbors
                if (count(grid, i, j) < 4)
                {
                    removedElements += 1;
                    grid[i][j] = 0; // remove the element
                }
            }

        result += removedElements;
    }

    printf("Result: %d\n", result);

    // de allocate the grid
    for (int i = 0; i < LINE_LEN; i++)
    {
        free(grid[i]);
    }
    free(grid);

    return 0;
}
