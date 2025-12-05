#include "Day4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define NEWLINE_CHAR 10
#define LINE_LEN 140
#define IDX(r, c) ((r) * LINE_LEN + (c))

typedef int bool;
#define true 1
#define false 0

void printGrid(uint8_t *grid)
{
    for (int i = 0; i < LINE_LEN; i++)
    {
        for (int j = 0; j < LINE_LEN; j++)
        {
            printf("%d ", grid[IDX(i, j)]);
        }
        printf("\n");
    }
}

void scanLine(char *line, uint8_t *row)
{
    for (int cursor = 0; cursor < LINE_LEN; cursor++)
    {
        row[cursor] = (line[cursor] == '.') ? 0 : 1;
    }
}

void scan(char *fileName, uint8_t *grid)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    char buffer[LINE_LEN + 2]; // +2 for newline and null terminator
    int row = 0;
    while (row < LINE_LEN && fgets(buffer, sizeof(buffer), file) != NULL)
    {
        for (int c = 0; c < LINE_LEN; c++)
            grid[IDX(row, c)] = (buffer[c] == '.') ? 0 : 1;
        row++;
    }

    fclose(file);
}

int count(uint8_t *grid, int row, int col)
{
    int cnt = 0;
    for (int dr = -1; dr <= 1; dr++)
    {
        int rr = row + dr;
        if (rr < 0 || rr >= LINE_LEN)
            continue;
        for (int dc = -1; dc <= 1; dc++)
        {
            int cc = col + dc;
            if (cc < 0 || cc >= LINE_LEN)
                continue;
            if (dr == 0 && dc == 0)
                continue;
            cnt += grid[IDX(rr, cc)];
        }
    }
    return cnt;
}

int findValidIndexes(uint8_t *grid, int *validIndexes)
{
    int index = 0;
    for (int i = 0; i < LINE_LEN * LINE_LEN; i++)
    {
        if (grid[i] != 0)
            validIndexes[index++] = i;
    }
    return index;
}

long d4_execute()
{
    char *fileName = "input4.txt";
    uint8_t *grid = (uint8_t *)malloc(LINE_LEN * LINE_LEN * sizeof(uint8_t));
    scan(fileName, grid); // populate the grid
    // int -> max integer = 2147483647, so LINE_LEN * LINE_LEN = 19600 fits well within this limit
    // uint8_t -> max integer = 255, so we can use it to represent presence (1) or absence (0)
    int *validIndexes = (int *)malloc(LINE_LEN * LINE_LEN * sizeof(int));
    memset(validIndexes, -1, LINE_LEN * LINE_LEN * sizeof(int));
    int validCount = findValidIndexes(grid, validIndexes);

    int result = 0;
    int removedElements = 1;

    while (removedElements > 0)
    {
        removedElements = 0;
        for (int i = 0; i < validCount; i++)
        {
            if (validIndexes[i] == -1)
                continue; // skip already removed elements

            int idx = validIndexes[i];
            int row = idx / LINE_LEN;
            int col = idx % LINE_LEN;

            // requirement is to check for less than 4 neighbors
            if (count(grid, row, col) < 4)
            {
                removedElements += 1;
                grid[IDX(row, col)] = 0; // remove the element
                validIndexes[i] = -1;    // mark as removed
            }
        }

        result += removedElements;
    }

    free(grid);
    free(validIndexes);
    printf("Result: %d\n", result);
    bool debug = false;
    return 0;
}
