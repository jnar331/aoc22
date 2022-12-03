#include <stdio.h>
#include <stdlib.h>

int main(){

    int* pElfsCalArr = NULL;

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
    int elfIndex = 0;
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

            int elfCount = elfIndex + 1;
            pElfsCalArr = (int*)realloc(pElfsCalArr, elfCount * sizeof(int));
            pElfsCalArr[elfIndex] = elfCals;

            elfIndex++;
            elfCals = 0;
        }
    }


    fclose(fP);

    int secondElfCals = 0;
    for(int i = 0; i< elfIndex ; i++){
        if(pElfsCalArr[i] > secondElfCals && pElfsCalArr[i] < elfCalsMax){
            secondElfCals = pElfsCalArr[i];
        }
    }

    int thirdElfCals = 0;
    for(int i = 0; i< elfIndex ; i++){
        if(pElfsCalArr[i] > thirdElfCals && pElfsCalArr[i] < secondElfCals){
            thirdElfCals = pElfsCalArr[i];
        }
    }

    free(pElfsCalArr);

    printf("Elf with most calories has %d", elfCalsMax);
    printf("Total calories top three %d", elfCalsMax + secondElfCals + thirdElfCals);

    return 0;
}