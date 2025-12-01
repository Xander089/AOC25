#include <stdio.h>
#include <string.h>

#define _INVALID_LINE_ -100000
#define CIRCULAR_BUFFER_SIZE 100
#define INITIAL_POSITION 50

typedef struct Data{
    int currentPosition;
    int currentRotationAmount;
    int zeroCount;
} Data;


int d1_execute();
int parseRotation(char *line, size_t len, ssize_t num_chars_read);
void applyRotation(Data *data);