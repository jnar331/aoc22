#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int calcMatchPoints(char opponentSign, char ownSign){
    int matchPoints = 0;
    if (ownSign == 'X'){
        //you play rock
        matchPoints += 1;
    }
    else if(ownSign == 'Y')
    {
        //you play paper
        matchPoints += 2;
    }

    else if(ownSign == 'Z'){
        //you play scissors
        matchPoints += 3;
    }

    bool draw = (ownSign == 'X' && opponentSign == 'A') || (ownSign == 'Y' && opponentSign == 'B') || (ownSign == 'Z' && opponentSign == 'C');
    if(draw){
        matchPoints += 3;
    }

    bool won = (ownSign == 'X' && opponentSign == 'C') || (ownSign == 'Z' && opponentSign == 'B') || (ownSign == 'Y' && opponentSign == 'A');
    if(won){
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

