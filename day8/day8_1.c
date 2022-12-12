#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Tree{
    char height;
    bool marked;
};


int main(){
    
    FILE* fP = fopen("../../day8/input", "r");
    if(fP == NULL){
        perror("Error opening file!");
        exit(-1);
    }

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int rows = 0;
    int cols = 0;
    int visibleTrees = 0;
    struct Tree* trees = NULL;
    struct Tree* treeRow;
    while ((read = getline(&line, &len, fP)) != -1) {

        
        cols = read - 1;
        trees = realloc(trees,(rows+1) * cols * sizeof(struct Tree));
        treeRow = trees + rows * cols;

        for(int i = 0; i<cols; i++){
            treeRow[i].height = line[i];
            treeRow[i].marked = false;
        }

        rows++;
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);

    }

    for(int i = 0; i<rows; i++){
        int maxTreeHeightLeft = 0;
        struct Tree* row = trees + i * cols;
        for(int j = 0; j<cols; j++){
           if(i != 0 && i != rows-1){
                if(row[j].height > maxTreeHeightLeft){
                    maxTreeHeightLeft = row[j].height;
                    if(!row[j].marked){
                        visibleTrees++;
                        row[j].marked = true;
                    }
                    
                }
           }
        }

        int maxTreeHeightRight = 0;
        for(int j = cols - 1; j>=0; j--){
            if(i != 0 && i != rows-1){
                if(row[j].height > maxTreeHeightRight){
                    maxTreeHeightRight = row[j].height;
                    if(!row[j].marked){
                        visibleTrees++;
                        row[j].marked = true;
                    }
                    
                }
           }
        }
    }

    for(int i = 0; i<cols; i++){
        int maxTreeHeightTop = 0;
        struct Tree* col = trees + i;
        for(int j= 0; j<rows; j++){
            struct Tree* curTree = col + j*cols;
            if(curTree->height > maxTreeHeightTop){
                maxTreeHeightTop = curTree->height;
                if(!curTree->marked){
                    visibleTrees++;
                    curTree->marked = true;
                }
            }
        }

        int maxTreeHeightBottom = 0;
        for(int j= rows -1; j>=0; j--){
            struct Tree* curTree = col + j*cols;
            if(curTree->height > maxTreeHeightBottom){
                maxTreeHeightBottom = curTree->height;
                if(!curTree->marked){
                    visibleTrees++;
                    curTree->marked = true;
                }
            }
        }
    }

    free(trees);
    printf("Trees visible: %d", visibleTrees);
    return 0;
}