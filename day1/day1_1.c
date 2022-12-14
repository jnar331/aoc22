#include <stdio.h>
#include <stdlib.h>

int main(){

    FILE* fP = fopen("../../day1/input", "r");
    if(fP == NULL){
        perror("Error opening file!");
        exit(-1);
    }

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int elfCalsMax = 0;
    int elfCals = 0;

    while ((read = getline(&line, &len, fP)) != -1) {

        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);

        if(line[0] != '\n'){
            int foodCals;
            sscanf(line, "%d\n", &foodCals);
            elfCals += foodCals;
        }
        else{
            if(elfCals > elfCalsMax){
                elfCalsMax = elfCals;
            }

            elfCals = 0;
        }
    }

    fclose(fP);
    printf("Elf with most calories has %d", elfCalsMax);
    
    return 0;
}