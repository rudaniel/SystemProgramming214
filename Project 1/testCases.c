#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mymalloc.h"
#include <time.h>


int main(int argc, char**argv){
srand(time(0));
    //Test Case 1
    clock_t begin = clock();
    
    for (int i =0; i<=50; i++)
    {
        for (int i =0; i<=120; i++){
            char* a = malloc(1);
            free(a);
        }
    }   

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Total Time Taken for Test Case 1:  %f\n", time_spent); //CPU time used in seconds.
    printf("Average Time Taken for Test Case 1:  %f\n", time_spent/50);

    //Test Case 2

    clock_t begin2 = clock();
    
    char *array[120];

    for (int i =0; i<50; i++){
        for (int i =0; i<120; i++){
            char* a = malloc(1);
            array[i] = a;
        }

        for (int i =0; i<120; i++){
            free(array[i]);
        }
    }
   

    clock_t end2 = clock();
    double time_spent2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;

    printf("Total Time Taken for Test Case 2:  %f\n", time_spent2); //CPU time used in seconds.
    printf("Average Time Taken for Test Case 2:  %f\n", time_spent2/50);


    clock_t begin3 = clock();
    char *array3[120];

for(int l=0; l<50; l++){
    for (int i = 0; i < 120; i++) {
        array3[i] = NULL;
    }
    int k=0;
    while(k<120){ 
        int n = rand() % 2; //picks if we should malloc or free.
        if (n == 0){ 
            array3[k] = malloc(1);
            k++;
        }
        else {
            int random = rand() % 120; //will free a random space if it is filled.
            free(array3[random]);
        }
    }
       for (int i = 0; i<120; i++){
            free(array3[i]);  
       }
}

    clock_t end3 = clock();

    double time_spent3 = (double)(end3 - begin3) / CLOCKS_PER_SEC;

    printf("Total Time Taken for Test Case 3:  %f\n", time_spent3); //CPU time used in seconds.
    printf("Average Time Taken for Test Case 3:  %f\n", time_spent3/50);

     //Test Case 4

    clock_t begin4 = clock();

    for (int i =0; i<50; i++){
    char* a = malloc(1000);
    char* b = malloc(1000);
    char* c = malloc(1000);
    char* d = malloc(1000);

    free(a);
    free(b);
    free(c);
    free(d);
    char* megaNode = malloc(4000); //Testing merging free Node.
    free(megaNode);
    }


    clock_t end4 = clock();

    double time_spent4 = (double)(end4 - begin4) / CLOCKS_PER_SEC;

    printf("Total Time Taken for Test Case 4:  %f\n", time_spent4); //CPU time used in seconds.
    printf("Average Time Taken for Test Case 4:  %f\n", time_spent4/50);

    //Test Case 5

    clock_t begin5 = clock();

    for (int i =0; i<50; i++){
    char* z = malloc(50);
    for(int i =0;  i<50;i++){
        z[i] = 'c';
    }
    free(z);
    char* x = malloc(10); //The user wont receive all 50 bytes because we can do it with less.
     for(int i =0;  i<10;i++){
        x[i] = 'c';
    }
    free(x);
    }


    clock_t end5 = clock();

    double time_spent5 = (double)(end5 - begin5) / CLOCKS_PER_SEC;

    printf("Total Time Taken for Test Case 5:  %f\n", time_spent5); //CPU time used in seconds.
    printf("Average Time Taken for Test Case 5:  %f\n", time_spent5/50);
}

