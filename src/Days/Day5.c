#include "Day5.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define NEWLINE_CHAR '\n'
#define RANGE_COUNT 192

long d5_power(long base, long exp)
{
    long result = 1;
    for (long i = 0; i < exp; i++)
    {
        result *= base;
    }
    return result;
}

void printRanges(long *ranges)
{
    for (int i = 0; i < RANGE_COUNT * 2; i++)
    {
        printf("%ld ", ranges[i]);
        printf("\n");
    }
}

int populateRanges(FILE *file, long *ranges)
{
    int rangesIndex = 0;
    char s[256];
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        size_t len = strlen(buffer);

        if (len == 1) // empty line
            break;

        int index = 0, str_cursor = 0;

        while (buffer[index] != '-')
            s[str_cursor++] = buffer[index++];

        s[str_cursor] = '\0';
        ranges[rangesIndex++] = strtol(s, NULL, 10);
        index++; // skip '-'
        str_cursor = 0;
        while (buffer[index] != NEWLINE_CHAR)
            s[str_cursor++] = buffer[index++];

        s[str_cursor] = '\0';
        ranges[rangesIndex++] = strtol(s, NULL, 10);
    }

    return rangesIndex;
}

int checkRange(FILE *file, long *ranges, int rangesIndex)
{
    int result = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        size_t len = strlen(buffer);
        int index = 0, str_cursor = 0;
        long num = strtol(buffer, NULL, 10);

        for (int i = 0; i < rangesIndex - 1; i += 2)
        {
            if (num >= ranges[i] && num <= ranges[i + 1])
            {
                result++;
                break;
            }
        }
    }

    return result;
}

void d5_scan(char *fileName)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    long *ranges = malloc(RANGE_COUNT * 2 * sizeof(long));
    memset(ranges, 0, RANGE_COUNT * 2 * sizeof(long));
    int rangesIndex = populateRanges(file, ranges);
    int result = checkRange(file, ranges, rangesIndex);

    printf("Result: %d\n", result);
    fclose(file);
    free(ranges);

    return;
}

long d5_ecxecute()
{
    char *fileName = "input5.txt";
    d5_scan(fileName);
    return 0;
}
