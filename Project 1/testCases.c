#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mymalloc.h"
#include <time.h>


int main(int argc, char**argv){

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

    char *array3[240];

    
    for (int i = 0; i < 240; i++) {
    array3[i] = NULL;
    }

    for (int j = 0; j<50; j++){
         for (int i =0; i<240; i++){ 
            int n = rand() % 2; //picks if we should malloc or free.
            if (n == 0){
                char* a = malloc(1);
                array3[i] = a;
            }
            else {
                int random = rand() % 120; //will free a random space if it is filled.
                 if (array3[random] == NULL){

                }
                else{
                free(array3[random]);  
                }
            }

        }
    }
       
    
       
       for (int i = 0; i<240; i++){
           if (array3[i] == NULL){

           }
           else{
                free(array3[i]);  
           }
       }
  


    clock_t end3 = clock();
    double time_spent3 = (double)(end3 - begin3) / CLOCKS_PER_SEC;
    printf("Time Taken for Test Csase 3:  %f\n", time_spent3);

}

