#include <stdio.h>
#include <stdlib.h>

int main(){

    FILE* fP = fopen("../../day6/input", "r");
    if(fP == NULL){
        perror("Error opening file!");
        exit(-1);
    }

    char ch;
    char chars[14];
    int charCount = 0;
    while ((ch = fgetc(fP)) != EOF)
    {   
        charCount++;
        int start = ftell(fP);
        chars[0] = ch;
        for(int i = 1; i<sizeof(chars); i++){
            chars[i] = fgetc(fP);
        }

        for(int i = 0; i<sizeof(chars); i++){
            if(i != sizeof(chars) - 1){
                for(int j = i+1; j<sizeof(chars); j++){
                    if(chars[i] == chars[j]){
                        printf("Same :(%d,%d)\n",i,j);
                        goto next;
                    }
                    printf("Not same : (%d,%d)\n",i,j);
                }
            } 
            
        }

        goto exit;

        next:
        fseek(fP,start,SEEK_SET);
    }

    exit:
    printf("Chars before marker: %d\n", ftell(fP));
    fclose(fP);
    
    return 0;
}