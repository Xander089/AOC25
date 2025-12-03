#include "Day3.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


typedef struct NumContainer {
    int x;
    int y;
    size_t pos;
} NumContainer;


void scanFile(char *fileName, long (*procLine)(char *)) {

    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) return;
   
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    long result = 0;
    int index = 0;
    while ((nread = getline(&line, &len, fp)) != -1) {
       
        long temp = procLine(line);
        result+= temp;
    }

    printf("%ld\n", result);


    free(line);
    fclose(fp);

}


long processLine(char *line){
   
    NumContainer nc;
    nc.x  = 0;
    nc.y = 0;
    nc.pos = 0;

    size_t len = strlen(line);

    //find the first largest number and its position
    for(int j = 0; j < len - 2; j++){
       
        int num = line[j] - '0';

        if(num > nc.x){
            nc.x = num;
            nc.pos = j;
        }
       
    }

    //find the second largest number after the position of the first largest number
    for(int j = nc.pos + 1; j < len - 1; j++){
        int num = line[j] - '0';
        if(num > nc.y){
            nc.y = num;
        }
    }

    return (long)nc.x * 10 + (long)nc.y;
}


long d3_ecxecute()
{
    scanFile("input3.txt", processLine);
    return 0;
}
