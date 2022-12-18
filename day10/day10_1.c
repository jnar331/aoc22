#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE* fP = fopen("../../day10/input", "r");
    if(fP == NULL){
        perror("Error opening file!");
        exit(-1);
    }

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int regVal = 1;
    int xValues[500] = {0};
    int cycleCount = 0;

    while ((read = getline(&line, &len, fP)) != -1) {
        int val = 0;
        if(sscanf(line,"addx %d\n",&val) == 1){

            xValues[cycleCount] = regVal;
            cycleCount++;
            xValues[cycleCount] = regVal;
            regVal += val;
            cycleCount++;
            

        }
        else if(strcmp("noop\n",line) == 0){
            xValues[cycleCount] = regVal;
            cycleCount++;
        }
        
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);

    }

    int signalStrSum = 0;
    for(int i = 20; i<= 220; i += 40){
        int sigStrength = i*xValues[i - 1];
        printf("Signal Strength at %d cycle: %d\n",i,sigStrength);
        signalStrSum += sigStrength;
    }

    printf("Signal Strength Sum: %d\n",signalStrSum);

    return 0;
}

