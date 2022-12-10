#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Directory{
    int fileSizeSum;
    struct Directory* parent;
    struct Directory* childs;
    size_t dirCount;
    char name[20];
};

int getDirSize(struct Directory* dir){
    int dirSize = dir->fileSizeSum;
    if(dir->dirCount != 0){
        for(int i = 0; i<dir->dirCount; i++){
            dirSize += getDirSize(&dir->childs[i]);
        }
    }

    return dirSize;
}

void getTotalSum(struct Directory* rootDir, int* totalSum){
    
    if(getDirSize(rootDir) <= 100000){
        *totalSum += getDirSize(rootDir);
        printf("Adding %d\n",getDirSize(rootDir));
    }
    for(int i = 0; i<rootDir->dirCount; i++){
        getTotalSum(&rootDir->childs[i],totalSum);
    }
}

int main(){

    
    FILE* fP = fopen("../../day7/input", "r");
    if(fP == NULL){
        perror("Error opening file!");
        exit(-1);
    }

    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    
    struct Directory* root = (struct Directory*)malloc(sizeof(struct Directory));
    struct Directory* curDir = NULL;
    while ((read = getline(&line, &len, fP)) != -1) {

        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
        char dirName[20];
        char fileName[20];
        int fileSize = 0;
        if(strcmp(line,"$ cd ..\n") == 0){
            if (curDir->parent != NULL)
            {
                curDir = curDir->parent;
            }
        }

        else if(sscanf(line,"$ cd %s",&dirName) == 1){
            if(curDir == NULL){
                curDir = root;
                curDir->parent = NULL;
                memcpy(&curDir->name,&dirName,sizeof(dirName));
            }
            
            else{
                for(int i = 0; i<curDir->dirCount; i++){
                    if(strcmp(curDir->childs[i].name,dirName) == 0){
                        curDir = &curDir->childs[i];
                    }
                }
            }
        }
        
        else if(strcmp(line,"$ ls\n") == 0){
            continue;
        }

        else if(sscanf(line, "dir %s\n",&dirName) == 1){
            curDir->dirCount++;
            curDir->childs = (struct Directory*)realloc(curDir->childs,curDir->dirCount * sizeof(struct Directory));
            curDir->childs[curDir->dirCount - 1].fileSizeSum = 0;
            memcpy(&curDir->childs[curDir->dirCount - 1].name, &dirName, sizeof(dirName));
            curDir->childs[curDir->dirCount - 1].parent = curDir;
            
        }

        else if(sscanf(line,"%d %s",&fileSize,&fileName) == 2){
            printf("Current Sum: %d\n",curDir->fileSizeSum);
            printf("Added file size: %d\n",fileSize);
            curDir->fileSizeSum += fileSize;
        }
    }

    //iterate through tree
    int totalSum = 0;
    curDir = root;
    getTotalSum(curDir,&totalSum);
    for(int i=0; i<curDir->dirCount; i++){
        printf("Dir Name: %s Dir Sum: %d\n",curDir->childs[i].name, curDir->childs[i].fileSizeSum);
    }
    printf("Total Sum: %d\n",totalSum);


    fclose(fP);
    
    return 0;
}