#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int add(int first, int second){
    return first + second;
}

int subtract(int first, int second){
    return first - second;
}

int multiply(int first, int second){
    return first*second;
}

int divide(int first, int second){
    return first/second;
}

bool testDivide(int first, int second){
    return (first % second == 0);
}

struct Monkey{
    bool squareItem;
    int (*op)(int f,int s);
    bool (*test)(int f,int s);
    int opArg;
    int testArg;
    int items[128];
    size_t itemCount;
    int trueMonkeyIndex;
    int falseMonkeyIndex;
    int inspectionCount;
};

int main(){
    FILE* fP = fopen("../../day11/example", "r");
    if(fP == NULL){
        perror("Error opening file!");
        exit(-1);
    }

    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char* token;
   
    struct Monkey* monkeys = NULL;
    size_t monkeyCount = 0;
    struct Monkey* currentMonkey;

    while ((read = getline(&line, &len, fP)) != -1) {
        char start_items[128] = {0};
        char op;
        char opArg[10];
        int testArg;
        int trueMonkey;
        int falseMonkey;

        if(sscanf(line," Starting items: %[^\n]",&start_items) == 1){

            monkeyCount++;
            monkeys = realloc(monkeys,monkeyCount*sizeof(struct Monkey));
            currentMonkey = &monkeys[monkeyCount - 1];
            currentMonkey->test = &testDivide;
            currentMonkey->squareItem = false;
            currentMonkey->opArg = 0;
            currentMonkey->testArg = 0;
            currentMonkey->inspectionCount = 0;
            currentMonkey->itemCount = 0;

            memset(&currentMonkey->items[0],0,sizeof(currentMonkey->items));
            char seps[] = ", ";
            token = strtok (&start_items[0], seps);
            while (token != NULL)
            {
                int worryLvl = 0;
                sscanf (token, "%d", &worryLvl);
                currentMonkey->items[currentMonkey->itemCount++] = worryLvl;
                token = strtok (NULL, seps);
            }
            
        }

        else if(sscanf(line," Operation: new = old %c %s\n",&op,&opArg) == 2){

            if(op == '+'){
                currentMonkey->op = &add;
            }
            else if(op == '-'){
                currentMonkey->op = &subtract;
            }
            else if(op == '*'){
                currentMonkey->op = &multiply;
            }
            else if(op == '/'){
                currentMonkey->op = &divide;
            }

            int arg = 0;
            if(sscanf(&opArg,"%d",&arg) == 1){
                currentMonkey->opArg = arg;
            }
            else if(strcmp(opArg,"old") == 0){
                currentMonkey->squareItem = true;
            }
           
        }

        else if(sscanf(line," Test: divisible by %d\n",&testArg) == 1){
            currentMonkey->testArg = testArg;
        }
        
        else if(sscanf(line,"  If true: throw to monkey %d\n",&trueMonkey) == 1){
            currentMonkey->trueMonkeyIndex = trueMonkey;
        }

        else if(sscanf(line,"  If false: throw to monkey %d\n",&falseMonkey) == 1){
            currentMonkey->falseMonkeyIndex = falseMonkey;
        }
        
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);

    }

    for(int i = 0; i<20; i++){
        for(int j = 0; j<monkeyCount; j++){
            struct Monkey* monkey = &monkeys[j];
            if(monkey->itemCount == 0){
                continue;
            }

            while(monkey->itemCount > 0){
                int secondArg = monkey->opArg;
                if(monkey->squareItem){
                    secondArg = monkey->items[0];
                }

                int newWorryLvl = monkey->op(monkey->items[0],secondArg) / 3;
                monkey->inspectionCount++;
                bool ret = monkey->test(newWorryLvl,monkey->testArg);
                int throwMonkeyIndex;
                if(ret){
                    throwMonkeyIndex = monkey->trueMonkeyIndex;
                }
                else{
                    throwMonkeyIndex = monkey->falseMonkeyIndex;
                }

                int itemCapacity = sizeof(monkey->items) / sizeof(monkey->items[0]);
                struct Monkey* throwMonkey = &monkeys[throwMonkeyIndex];

                
                memmove(&monkey->items[0],&monkey->items[1],(itemCapacity - 1)*sizeof(monkey->items[0]));
                monkey->itemCount--;
                throwMonkey->items[throwMonkey->itemCount++] = newWorryLvl;
            }
            
            
        }
    }

    int first = 0;
    int second = 0;

    for( int i = 0; i < monkeyCount; i++ ) {
        printf("Monkey %d: %d\n",i,monkeys[i].inspectionCount);
        if(monkeys[i].inspectionCount > first) {
            second = first;
            first = monkeys[i].inspectionCount;
        }
        else if(monkeys[i].inspectionCount > second ) {
            second = monkeys[i].inspectionCount;
        }
    }

    int monkeyBusiness = first * second;
    printf("Monkey Business: %d\n",monkeyBusiness);
    free(monkeys);
    return 0;
}

