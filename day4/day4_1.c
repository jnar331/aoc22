#include <stdio.h>
#include <stdlib.h>

struct Sections{
    int start;
    int end;
};

int main(){
    FILE* fP = fopen("../../day4/input", "r");
    if(fP == NULL){
        perror("Error opening file!");
        exit(-1);
    }

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    struct Sections firstElf;
    struct Sections secondElf;
    int overlappingPairs = 0;
    while ((read = getline(&line, &len, fP)) != -1) {

        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
        sscanf(line, "%d-%d,%d-%d\n", &firstElf.start,&firstElf.end,&secondElf.start,&secondElf.end);
        if((firstElf.start <= secondElf.start && firstElf.end >= secondElf.end) || (secondElf.start <= firstElf.start && secondElf.end >= firstElf.end)){
            overlappingPairs++;
        }
    }

    fclose(fP);
    printf("Count of overlapping pairs: %d\n", overlappingPairs);

    return 0;
}