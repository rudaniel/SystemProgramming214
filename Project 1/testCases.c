#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mymalloc.h"
#include <time.h>


int main(int argc, char**argv){
srand(time(0));
    //Test Case 1
    clock_t begin = clock();
    
    // for (int i =0; i<=50; i++)
    // {
    //     for (int i =0; i<=120; i++){
    //         char* a = malloc(1);
    //         free(a);
    //     }
    // }   

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Time Taken for Test Csase 1:  %f\n", time_spent); //CPU time used in seconds.


    //Test Case 2

    clock_t begin2 = clock();
    
    char *array[120];

    // for (int i =0; i<50; i++){
    //     for (int i =0; i<120; i++){
    //         char* a = malloc(1);
    //         array[i] = a;
    //     }

    //     for (int i =0; i<120; i++){
    //         free(array[i]);
    //     }
    // }
   

    clock_t end2 = clock();
    double time_spent2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
    printf("Time Taken for Test Csase 2:  %f\n", time_spent2);


    clock_t begin3 = clock();
    char *array3[10];

    
    for (int i = 0; i < 10; i++) {
    array3[i] = NULL;
    printf("array3: %p\n", array3[i]);
    }

  //  for (int j = 0; j<50; j++){
         for (int i =0; i<10; i++){ 
             printf("looping at i: %d\n",i);
            int n = rand() % 2; //picks if we should malloc or free.
            if (n == 0){ 
                printf("malloc calling\n");
                array3[i] = malloc(1);
            }
            else {
                printf("free calling\n");
                int random = rand() % 10; //will free a random space if it is filled.
                 if (array3[random] == NULL){

                }
                else{
                free(array3[random]);  
                }
            }

        }
  //  }
    for (int i = 0; i < 10; i++) {
    printf("array3: %p\n", array3[i]);
    }

       for (int i = 0; i<10; i++){
           if (array3[i] == NULL){
               printf("null node\n");
           }
           else{
               printf("freeing node\n");
                free(array3[i]);  
        
           }
       }


    clock_t end3 = clock();
    double time_spent3 = (double)(end3 - begin3) / CLOCKS_PER_SEC;
    printf("Time Taken for Test Csase 3:  %f\n", time_spent3);

}

