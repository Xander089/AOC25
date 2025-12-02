#include "Day2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOT_INITIALIZED -1

typedef struct Range{
    long x;
    long y;
} Range;

long power(long base, long exp){
    long result = 1;
    for(int i = 0; i < exp; i++)
        result *= base;
    return result;
}

void reset(Range *range){
   
    if(range == NULL)
        return;
   
    range->x = NOT_INITIALIZED;
    range->y = NOT_INITIALIZED;
}

// get the count of digits of the largest number in the input string
size_t getMaxStrLen(FILE *fp){

    if(fp == NULL)
        return -1;
   
    int readChar;
    size_t str_len = 0, final_len = 0;
   
    while((readChar = fgetc(fp)) != EOF){
       
        if((char)readChar == ','){
            str_len = 0;
            continue;
        }

        if((char)readChar != '-')
            str_len++;
        else {
            if(str_len > final_len){
                final_len = str_len;
                continue;
            }
        }

    }

    fseek(fp, 0, SEEK_SET);
    return final_len;
}


int isSymmetric(char *s){
    if(s == NULL)
        return 0;

    size_t len = strlen(s);

    if(len == 0)
        return 0;

    if(len % 2 != 0)
        return 0;
   
    //divide the string in 2, and convert each half to long
    long firstHalf = strtol(s, NULL, 10)/power(10, len / 2);
    long secondHalf = strtol(s + len / 2, NULL, 10);

    return firstHalf == secondHalf;
}

int Symmetric(char *s, size_t len, size_t chunk){

    //if the length of s is not divisible by chunk, return false
    if(len % chunk != 0){
        return 0;
    }

    size_t str_cursor = 0;
    long value = -1;
    char *temp = malloc((chunk + 1) * sizeof(char));
    temp[chunk] = '\0';
    int result = 1;

    while(str_cursor <= (len - chunk)){

        //extract substring
        for(int i = 0; i < chunk; i++){
            temp[i] = s[str_cursor + i];
        }

        //at the first iteration, initialize value to compare with
        if(value == -1){
            value = strtol(temp, NULL, 10);        
        }
        else {
            //if the new value is different, return false
            if(value != strtol(temp, NULL, 10)){
                result = 0;
                break;
            }
        }

        str_cursor+= chunk;
    }

    free(temp);
    return result;

}

int isSymmetric2(char *s){
    
    if(s == NULL)
        return 0;

    size_t len = strlen(s);

    if(len == 0)
        return 0;

    size_t charToRead = 1;
    
    while(charToRead <= len / 2){
        
        if(Symmetric(s, len, charToRead))
            return 1;

        charToRead++;
    }
   
    return 0;
}


long process(Range *range1, size_t len){
   
    long index = range1->x;
    long res = 0;
    char *s = malloc(len + 1);
   
    while(index <= range1->y){
       
        //convert index to string
        size_t curr_len = snprintf(NULL, 0, "%ld", index);
        snprintf(s, curr_len + 1, "%ld", index);
    
        //if the sting is symmetric, add to result           
        if(isSymmetric2(s)){
            res+= index;
        }
        
        index++;
    }

    free(s);

    return res;
}

long d2_execute(){

    FILE *fp = fopen("input2.txt", "r");

    if (fp == NULL) return -1;
    const size_t max_len = getMaxStrLen(fp) + 1;
   
    char *str = malloc(max_len * sizeof(char));
   
    Range *range = malloc(sizeof(Range));
    reset(range);

    int readChar;
    size_t str_index = 0;

    long result = 0;
   
    //scan file char by char
    while((readChar = fgetc(fp)) != EOF){
       
        char c = (char)readChar;
       
        //when char is not a delimiter, populate the string
        if(c != '-' && c != ',')
        {
            if(str_index < max_len)
                str[str_index++] = (char)readChar;
        }
        else if(c == '-') { //initialize range.x
            str[str_index++] = '\0';
            str_index = 0;            
            range->x = strtol(str, NULL, 10);        
        }
        else if(c == ',') { //initialize range.y
            str[str_index++] = '\0';
            str_index = 0;            
            range->y = strtol(str, NULL, 10);
            
            //now that we have both x and y, process the range in search for symmetric numbers
            result+= process(range, max_len);
            reset(range);
        }

    }

    //process last range when EOF is reached
    str[str_index++] = '\0';
    range->y = strtol(str, NULL, 10);
    result+= process(range, max_len);
   
    printf("Day 2 - Puzzle 2: %ld\n", result);

    free(str);
    free(range);
    fclose(fp);
   
    return result;

};