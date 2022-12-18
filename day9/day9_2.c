#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


struct Point{
    int x;
    int y;
};

struct VisitedPoints{
    struct Point* points;
    size_t amount;
};

void printRope(struct Point head, struct Point tail[], size_t tailSize){
    printf("Head: (%d,%d)\n",head.x,head.y);
    
    for(int i = 0; i<tailSize; i++){
        printf("Knot %d: (%d,%d)\n", i,tail[i].x,tail[i].y);
    }
}

int sign(int x) {
    return (x > 0) - (x < 0);
}


bool addToVisitedPoints(struct Point point, struct VisitedPoints* points){
    for(int i = 0; i<points->amount; i++){
        if(points->points[i].x == point.x && points->points[i].y == point.y){
            return false;
        }
    }

    points->points = (struct Point*)realloc(points->points,(points->amount + 1)*sizeof(struct Point));
    points->points[points->amount] = point;
    points->amount++;
    return true;
}

bool tailMoving(struct Point head, struct Point tail){
    return ((abs(head.x - tail.x) > 1) || (abs(head.y - tail.y) > 1));
}

void moveTail(struct Point newhead, struct Point* tail, struct Point* tailEnd, struct VisitedPoints* points){

    if(!tailMoving(newhead,*tail)){
        return;
    }

    int dx = newhead.x - tail->x;
    int dy = newhead.y - tail->y;

    if(dx > 1){
        
        tail->x = newhead.x - 1;
        tail->y += sign(dy);
    }
    else if(dx < -1){
        tail->x = newhead.x + 1;
        tail->y += sign(dy);
    }
    else if(dy > 1){ 
        tail->y = newhead.y - 1;
        tail->x += sign(dx);
    }

    else if(dy < -1){
        tail->y = newhead.y + 1;
        tail->x += sign(dx);
    }

    if(tail == tailEnd){
        addToVisitedPoints(*tail,points);
        return;
    }
    
    moveTail(*tail, tail + 1,tailEnd,points);

}


int main(){
    
    FILE* fP = fopen("../../day9/input", "r");
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

    struct Point head = {0,0};
    struct Point tail[9] = {0};

    struct VisitedPoints visitedPoints;
    visitedPoints.amount = 0;
    visitedPoints.points = malloc(sizeof(struct Point));
    visitedPoints.points[0] = head;
    visitedPoints.amount++;
    
    while ((read = getline(&line, &len, fP)) != -1) {
        int steps = 0;
        if(sscanf(line,"R %d\n",&steps) == 1){
          
            for(int i = 0; i<steps; i++){
                
                head.x++;
                moveTail(head,&tail[0],&tail[8],&visitedPoints);
                printRope(head,tail,9);
            }


        }
        else if(sscanf(line,"L %d\n",&steps) == 1){
            
            for(int i = 0; i<steps; i++){
                head.x--;
                moveTail(head,&tail[0],&tail[8],&visitedPoints);
                printRope(head,tail,9);
            }
        }

        else if(sscanf(line,"U %d\n",&steps) == 1){
            for(int i = 0; i<steps; i++){
                head.y++;
                moveTail(head,&tail[0],&tail[8],&visitedPoints);
                printRope(head,tail,9);
            }
        }
        else if(sscanf(line,"D %d\n",&steps) == 1){
            for(int i = 0; i<steps; i++){
                head.y--;
                moveTail(head,&tail[0],&tail[8],&visitedPoints);
                printRope(head,tail,9);
            }
        }

        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);

    }

    printf("coordinates:\n");
    for(int i = 0; i<visitedPoints.amount; i++){
        printf("(%d,%d)\n",visitedPoints.points[i].x,visitedPoints.points[i].y);
    }
    printf("Points visited: %d\n",visitedPoints.amount);
    free(visitedPoints.points);
    return 0;
}
