#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool hasStack(char* line, size_t lineLength){
    for(int i = 0; i<lineLength; i++){
        if(line[i] == '[' && line[i+2] == ']'){
            return true;
        } 
    }
    return false;
}

struct Line{
    char* line;
    size_t length;
};

struct Stack{
    char* line;
    size_t elements;
    size_t capacity;
};

int main(){
    FILE* fP = fopen("../../day5/input", "r");
    if(fP == NULL){
        perror("Error opening file!");
        exit(-1);
    }



    char * line = NULL;
    struct Line rows[100];
    struct Stack* stacks = NULL;

    size_t len = 0;
    ssize_t read;
    int rowCount = 0;
    int cols = 0;
    int startElementPosition = 1;
    const int stackWidth = 4;
    while ((read = getline(&line, &len, fP)) != -1) {

        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);

        if(hasStack(line,read)){

            struct Line stackLine;
            stackLine.line = (char*)malloc(read);
            memcpy(stackLine.line,line,read);
            stackLine.length = read;
            rows[rowCount] = stackLine;
            rowCount++;
        }
        else{
            break;
        }
        
    }

    for(int i = 0; i<rowCount; i++){
        printf("Line: %s",rows[i].line);
    }

    for(int i = rowCount - 1; i>=0; i--){
        int colCount = 0;
        for(int j = startElementPosition; j < rows[i].length; j+=stackWidth){
            if(i == rowCount - 1){
                stacks = (struct Stack*)realloc(stacks,(colCount + 1) * sizeof(struct Stack));
            }
            
            int elementIndex = (rowCount - 1) - i;
            size_t newStacksize = (elementIndex + 1)*sizeof(char);
            stacks[colCount].line = (char*)realloc(stacks[colCount].line, newStacksize);
            stacks[colCount].capacity = newStacksize;
            stacks[colCount].line[elementIndex] = rows[i].line[j];
            if(rows[i].line[j] != ' '){
                stacks[colCount].elements = newStacksize;
            }
            colCount++;
        }

        cols = colCount;
    }

    while ((read = getline(&line, &len, fP)) != -1) {

        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
        int amount;
        int stackFrom;
        int stackTo;
        if(sscanf(line, "move %d from %d to %d\n",&amount,&stackFrom,&stackTo) != 3){
            continue;
        };

        printf("%d,%d,%d\n",amount,stackFrom,stackTo);

        if((stacks[stackTo-1].elements + amount) > stacks[stackTo - 1].capacity){
            stacks[stackTo - 1].line = (char*)realloc(stacks[stackTo - 1].line, 2*stacks[stackTo - 1].capacity);
            stacks[stackTo - 1].capacity = 2*stacks[stackTo - 1].capacity;
        }

        
        memcpy(stacks[stackTo - 1].line + stacks[stackTo - 1].elements , stacks[stackFrom - 1].line + (stacks[stackFrom - 1].elements - amount),amount * sizeof(char));
        
        stacks[stackTo - 1].elements += amount;
        stacks[stackFrom - 1].elements -= amount;
        
        printf("Stack From: %s\n", stacks[stackFrom - 1].line);
        printf("Stack To: %s\n", stacks[stackTo - 1].line);
    }


    printf("Top Elements: ");
    for(int i=0; i<9; i++){
        printf("%c",stacks[i].line[stacks[i].elements - 1]);
    }
    printf("\nRows: %d",rowCount);
    
    for(int i=0; i<cols; i++){
        free(stacks[i].line);
    }

    free(stacks);
    fclose(fP);
    return 0;
}