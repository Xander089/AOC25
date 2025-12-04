#include "Day3.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#define LONG_LEN 12

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



long processLine2(char *line){

    if(line == NULL) return -1;
    size_t len = strlen(line);
    if(len == 0) return -1;
    
    int cursor = 0;
    int filled_char = 0;
    int num_to_find = 10;
    int candidate = 0;
    char s[LONG_LEN + 1];

    while(num_to_find >= 1  && filled_char < LONG_LEN){

        candidate = 0;
        num_to_find--;


        //trovo il primo num to find massimo
        for(int i = 0; i < len - LONG_LEN; i++){
            if(line[i] - '0' == num_to_find){
                candidate = i;
                s[filled_char++] = line[i] - '0';
                break;
            }
        }

        //se ho riempito la stringa --> la termino ed esco
        if(filled_char == LONG_LEN){
            s[LONG_LEN] = '\0'; // null terminating char
            break;
        }

        //controllo il resto di line in cerca del num to find e riempio s
        for(int j = candidate + 1; j < len - LONG_LEN; j++ ){
            if(line[j] - '0' == num_to_find){
                s[filled_char++] = line[j] - '0';
            }
        }

    }

    if(filled_char < LONG_LEN){
        
    }

    long result = strtol(s, NULL, 10);
    return result;

}

long d3_ecxecute()
{
    scanFile("input3.txt", processLine);
    return 0;
}
