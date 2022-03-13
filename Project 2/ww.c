#include<stdio.h>
#include<stdlib.h>
#include <string.h>


int helper(char line[], int width, int space){
    char copy[256];
    strncpy(copy, line, 256);

    int totalWords = 0; //I want to create an array that holds whole words not letters like below. This will tell us home many words there is.
    int charCount = 0;
    int spaceChecker =0;
    for(int i =0; i<256;i++){
            if(copy[i] == '\n'){
                if(totalWords == 0 && charCount == 0){

                }
                else{
                totalWords++;
                }
                
                
                break;
            }
            else if(copy[i] == ' '){
                if(spaceChecker == 1){

                }
                else{
                totalWords++;
                }
                spaceChecker = 1;
                printf("\n");

            }
            else{
                 printf("%c", copy[i]); //This code goes through each line of the file and is able to sperate those lines by words
                 spaceChecker = 0;
                 charCount = 1;
              //   printf("\n");
            }
           
        }
        if(charCount ==1 && totalWords ==0){
            totalWords++;
        }
        printf("\n");
        printf("Total Word: %d\n", totalWords);
        //printf("charCount: %d\n", charCount);

        return space; //TODO code proper spacing 
}


int main(){

    FILE *unwrapped = fopen("test1.txt", "r");
    if(unwrapped == NULL){
        printf("File unable to open.");
        exit(1);
    }

    

    char buf[256];
    int myWidth = 20;
    int space = 20; //current space at the start

    while(fgets(buf, 256, unwrapped)){
     
        space = helper(buf, myWidth, space); //the helper function will write into the file and return space avail for next line.
      //  break;
    }

    fclose(unwrapped);
}












     // for(int i =0; i<256;i++){
        //     if(copy[i] == ' '){
        //         printf("\n");
        //     }
        //     else{
        //          printf("%c", copy[i]); //This code goes through each line of the file and is able to sperate those lines by words
        //     }
           
        //}
     //   printf("NEW LINE\n");
