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

    const size_t crtRows = 6;
    const size_t crtCols = 40;

    char crt[crtRows * crtCols];
    memset(&crt,'.',sizeof(crt));
    printf("\n\n");

    for(int i = 0; i<crtRows; i++){
        int rowStart = i * crtCols;
        for(int j = 0; j<crtCols; j++){
            if(xValues[rowStart + j] - 1 == j || xValues[rowStart + j] == j || xValues[rowStart + j] + 1 == j){
                crt[rowStart + j] = '#';
            }
            printf("%c",crt[rowStart + j]);
        }
        printf("\n");
    }

    return 0;
}

