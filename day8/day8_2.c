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
    int maxScore = 0;
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

    for(int i = 1; i<rows - 1; i++){
        int maxTreeHeightLeft = 0;
        struct Tree* row = trees + i * cols;
        for(int j = 1; j<cols-1; j++){
           struct Tree* middle = row + j;
           struct Tree* left = middle - 1;
           int leftTrees = 0;
           struct Tree* right = middle + 1;
           int rightTrees = 0;
           struct Tree* top = middle - cols;
           int topTrees = 0;
           struct Tree* bottom = middle + cols;
           int bottomTrees = 0;
           
           for(int lIndex = j; lIndex>=1; lIndex--){
                leftTrees++;
                if(left->height < middle->height){
                    left--;
                }
                else{
                    break;
                }
           }

           for(int rIndex = j; rIndex<cols-1; rIndex++){
                rightTrees++;
                if(right->height < middle->height){
                    right++;
                    
                }
                else{
                    break;
                }
           }

           for(int tIndex = i; tIndex>=1; tIndex--){
                topTrees++;
                if(top->height < middle->height){
                    top -= cols;
                    
                }
                else{
                    break;
                }
           }

           for(int bIndex = i; bIndex<rows-1; bIndex++){
                bottomTrees++;
                if(bottom->height < middle->height){
                    bottom += cols;
                    
                }
                else{
                    break;
                }
           }

            int treeScore = leftTrees * rightTrees * topTrees * bottomTrees;
            printf("(%d,%d) %c:  %d\n",i,j,middle->height, treeScore);
            if(treeScore > maxScore){
                maxScore = treeScore;
            }
           
        }

    }

    free(trees);
    printf("Max Score: %d", maxScore);
    return 0;
}