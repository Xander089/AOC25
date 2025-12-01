#include "Day1.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define _INVALID_LINE_ -100000
#define CIRCULAR_BUFFER_SIZE 100
#define INITIAL_POSITION 50

typedef struct Data{
    int currentPosition;
    int currentRotationAmount;
    int zeroCount;
} Data;

void updatePosition(Data *data){
       
    int prev = data->currentPosition;
    int amount = data->currentRotationAmount;
   
    //caso in cui devo scalare per multipli di 100
    if (amount != 0) {
        int wraps = amount / CIRCULAR_BUFFER_SIZE;
        amount %= CIRCULAR_BUFFER_SIZE;
        data->zeroCount += (wraps < 0) ? -wraps : wraps;
    }
   
    int sum = prev + amount;
   
    //se ruoto a sinistra e il numero da cui parto non è già zero --> incremento
    if(sum < 0 && prev != 0) data->zeroCount++;
   
    //se ruoto a destra e supero il max del buffer --> incremento
    if(sum > CIRCULAR_BUFFER_SIZE) data->zeroCount++;
   
   
    int newpos = sum % CIRCULAR_BUFFER_SIZE;
    if (newpos < 0) newpos += CIRCULAR_BUFFER_SIZE;
   
    //caso standard in cui atterro sullo zero --> incremento
    if (newpos == 0) data->zeroCount++;

    data->currentPosition = newpos;
   
}

int parseRotationAmount(
    char *line,
    size_t len,
    ssize_t num_chars_read){
   
    //trim della linea
    while (num_chars_read > 0 && (line[num_chars_read-1] == '\n' || line[num_chars_read-1] == '\r'))
        line[--num_chars_read] = '\0';

    if (num_chars_read == 0) return _INVALID_LINE_;
    char dir = line[0];
    if (dir != 'L' && dir != 'R') return _INVALID_LINE_;
    char *p = line + 1;
    char *end;
    long val = strtol(p, &end, 10); //string to long


    if (end == p) return _INVALID_LINE_; //riga senza digit numbers
   
    int amount = (int) val;
    return amount * (dir == 'R' ? 1 : -1);
}

int d1_execute()
{
    const char* fileName = "input1.txt";
    FILE* fp = fopen(fileName, "r");

    if (fp == NULL) return -1;
   
    char *line = NULL;
    size_t len = 0;
    ssize_t nread; // numero caratteri letti con getline

    Data *data = malloc(sizeof(Data));
    data->currentPosition = INITIAL_POSITION;
    data->currentRotationAmount = 0;
    data->zeroCount = 0;

    while ((nread = getline(&line, &len, fp)) != -1) {

        int amount = parseRotationAmount(line, len, nread);
        data->currentRotationAmount = amount;
        if(amount == _INVALID_LINE_)
            continue;

        updatePosition(data);

    }

    int result = data->zeroCount;
   
    free(line);
    free(data);
    fclose(fp);

    printf("Day 1 - Puzzle 2: %d\n", result);
    return result;
}

