#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define BUFFER 256

typedef struct node{
    char *word;
    struct node *next;
} node;

int helper(char line[], int width, int space){
    char copy[BUFFER];
    strncpy(copy, line, BUFFER);
    int totalWords = 0; //I want to create an array that holds whole words not letters like below. This will tell us home many words there is.
    int charCount = 0;
    int spaceChecker =0;
    //char temp[]='\0';
    if(copy[0]=='\n'){
        printf("new line\n");
    }
    else{
        for(int i =0; i<BUFFER;i++){
            if(copy[i] == '\n'){
                if(totalWords == 0 && charCount == 0){
                }
                else{
                //printf("%s",temp);
                //temp='\0';
                totalWords++;
                }
                break;
            }
            else if(copy[i] == ' '){
                if(spaceChecker == 1){
                }
                else{
               // printf("%s",temp);
               // temp=" ";
                totalWords++;
                }
                spaceChecker = 1;
                printf("\n");
            }
            else{/*
                if(temp==" "){
                    temp=copy[i];
                }
                else{	
                    strcat(temp, copy[i]);
                 }
                 */printf("%c", copy[i]); //This code goes through each line of the file and is able to sperate those lines by words
                 spaceChecker = 0;
                 charCount = 1;
              //   printf("\n");
            }
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

    //gcc ww.c -o ww
    //./ww

    FILE *unwrapped = fopen("test1.txt", "r");
    if(unwrapped == NULL){
        printf("File unable to open.");
        exit(1);
    }

    char buf[BUFFER];
    int myWidth = 20;
    int space = 20; //current space at the start

    while(fgets(buf, BUFFER, unwrapped)){
     
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
