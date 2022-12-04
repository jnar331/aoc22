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

struct Line{
    char letters[64];
    size_t lineLength;
};

int main(){
    FILE* fP = fopen("../../day3/input", "r");
    if(fP == NULL){
        perror("Error opening file!");
        exit(-1);
    }

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    struct Line firstLine;
    struct Line secondLine;
    struct Line thirdLine;

    int lineCounter = 0;
    int totalBadgeCount = 0;

    while ((read = getline(&line, &len, fP)) != -1) {
        
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);

        lineCounter++;

        size_t lineLength = read - 1;
        if(lineCounter == 1){
            firstLine.lineLength = lineLength;
            memcpy(&firstLine.letters,line, lineLength);
        }
        else if(lineCounter == 2){
            secondLine.lineLength = lineLength;
            memcpy(&secondLine.letters,line, lineLength);
        }

        else if(lineCounter == 3){
            thirdLine.lineLength = lineLength;
            memcpy(&thirdLine.letters,line, lineLength);
            for(int i = 0; i < firstLine.lineLength; i++){
                for (int j = 0; j < secondLine.lineLength; j++)
                {
                    if(firstLine.letters[i] == secondLine.letters[j]){
                        for(int k = 0; k < thirdLine.lineLength; k++){
                            if(secondLine.letters[j] == thirdLine.letters[k]){
                                totalBadgeCount += letterToNumber(thirdLine.letters[k]);
                                printf("Badge found: '%c'\n",thirdLine.letters[k]);
                                goto badge_found;
                            }
                        }
                    }
                }
                
            }
            badge_found:
            lineCounter = 0;
        }
 
    }

    printf("Total Badge Sum: %d\n",totalBadgeCount);
    return 0;
}