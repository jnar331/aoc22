#include <stdio.h>
#include <stdlib.h>

int main(){

    FILE* fP = fopen("/home/jnar/projects/aoc22/day1/input", "r");
    if(fP == NULL){
        perror("Error opening file!");
        exit(-1);
    }

    
    printf("Hello World!");
    return 0;
}