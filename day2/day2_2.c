#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int calcMatchPoints(char opponentSign, char ownSign){
    int matchPoints = 0;
    if (ownSign == 'X'){
        //need to lose
        if(opponentSign == 'A'){
            matchPoints += 3;
        }
        else if(opponentSign == 'B'){
            matchPoints += 1;
        }
        else{
            matchPoints += 2;
        }
    }
    else if(ownSign == 'Y')
    {
        //need a draw
        if(opponentSign == 'A'){
            matchPoints += 1;
        }
        else if(opponentSign == 'B'){
            matchPoints += 2;
        }
        else{
            matchPoints += 3;
        }

        matchPoints += 3;
    }

    else if(ownSign == 'Z'){
        //need to win
        if(opponentSign == 'A'){
            matchPoints += 2;
        }
        else if(opponentSign == 'B'){
            matchPoints += 3;
        }
        else{
            matchPoints += 1;
        }

        matchPoints += 6;
    }

    return matchPoints;
}

int main(){
    FILE* fP = fopen("../../day2/input", "r");
    if(fP == NULL){
        perror("Error opening file!");
        exit(-1);
    }

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int totalScore = 0;
    while ((read = getline(&line, &len, fP)) != -1) {

        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);

        char opponentSign;
        char ownSign;
        sscanf(line,"%c %c\n", &opponentSign, &ownSign);
        totalScore += calcMatchPoints(opponentSign,ownSign);
    }

    printf("Total Score: %d\n",totalScore);

    return 0;
}

