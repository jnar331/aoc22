#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int letterToNumber(char letter){
    int num = -1;
    if (letter >= 'A' && letter <= 'Z')
        num = 27 + (letter - 'A');
    else if (letter >= 'a' && letter <= 'z')
        num = 1 + (letter - 'a');

    return num;
}

int main(){
    FILE* fP = fopen("../../day3/input", "r");
    if(fP == NULL){
        perror("Error opening file!");
        exit(-1);
    }

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int totalErrorSum = 0;
    int rucksackIndex = 0;
    while ((read = getline(&line, &len, fP)) != -1) {

        ssize_t half = (read/2);
        for(int i = 0; i<half; i++){
            for(int j = half; j < read - 1; j++){
                if(line[i] == line[j]){
                    
                    printf("Found wrong item '%c' in rucksack number %d\n",line[i],rucksackIndex + 1);
                    totalErrorSum += letterToNumber(line[i]);
                    goto search_finished;
                }
            }
        }

    search_finished:
        rucksackIndex++;
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
    }

    printf("\nTotal Error Sum: %d\n", totalErrorSum);
    return 0;
}