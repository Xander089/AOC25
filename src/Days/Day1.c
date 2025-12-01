#include "Day1.h"
#include <stdlib.h>

int d1_execute()
{
    const char* fileName = "input1.txt";
    FILE* fp = fopen(fileName, "r");

    if (fp == NULL) return -1;
   
    char *line = NULL;
    size_t len = 0;
    ssize_t nread; // number of characters read with getline

    Data *data = malloc(sizeof(Data));
    data->currentPosition = INITIAL_POSITION;
    data->currentRotationAmount = 0;
    data->zeroCount = 0;

    while ((nread = getline(&line, &len, fp)) != -1) {

        int amount = parseRotation(line, len, nread);
        data->currentRotationAmount = amount;
        if(amount == _INVALID_LINE_)
            continue;

        applyRotation(data);

    }

    int result = data->zeroCount;
   
    free(line);
    free(data);
    fclose(fp);

    printf("Day 1 - Puzzle 2: %d\n", result);
    return result;
}

void applyRotation(Data *data){
       
    int prev = data->currentPosition;
    int amount = data->currentRotationAmount;
   
    //case 1: we rotate more than a full circle
    //increase zeroCount N times where N is the number of full circles done
    if (amount != 0) {
        int wraps = amount / CIRCULAR_BUFFER_SIZE;
        amount %= CIRCULAR_BUFFER_SIZE;
        data->zeroCount += (wraps < 0) ? -wraps : wraps;
    }
   
    int sum = prev + amount;
   
    //case 2: we rotate to the left but the starting number is not already zero
    if(sum < 0 && prev != 0) 
        data->zeroCount++;
   
    //case 3: we rotate to the right and exceed the max size
    if(sum > CIRCULAR_BUFFER_SIZE) 
        data->zeroCount++;
   
    int newpos = sum % CIRCULAR_BUFFER_SIZE;
    if (newpos < 0) 
        newpos += CIRCULAR_BUFFER_SIZE;
   
    //case 4: standard case where we land on zero
    if (newpos == 0) 
        data->zeroCount++;

    data->currentPosition = newpos; 
}

int parseRotation(
    char *line,
    size_t len,
    ssize_t num_chars_read){
   
    //remove trailing characters like \n or \r
    while (num_chars_read > 0 && (line[num_chars_read-1] == '\n' || line[num_chars_read-1] == '\r'))
        line[--num_chars_read] = '\0';

    if (num_chars_read == 0) return _INVALID_LINE_;
    char dir = line[0];
    if (dir != 'L' && dir != 'R') return _INVALID_LINE_;
    char *p = line + 1;
    char *end;
    long val = strtol(p, &end, 10); //string to long


    if (end == p) return _INVALID_LINE_; //line without digit numbers
   
    int amount = (int) val;
    return amount * (dir == 'R' ? 1 : -1);
}