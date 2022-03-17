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
    int totalWords = 1; //I want to create an array that holds whole words not letters like below. This will tell us home many words there is.
    int charCount = 0;
    int spaceChecker =0;
    char wordArray[BUFFER];
    char temp[BUFFER] = "";
    //char temp[]='\0';
    if(copy[0]=='\0'){       //this is already checked in the for loop lol.
        printf("new line\n");
        totalWords = -1;
        return totalWords;
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
            //    printf("\n");
            }
            else{/*
                if(temp==" "){
                    temp=copy[i];
                }
                else{	
                    strcat(temp, copy[i]);
                 }
                 */
               //  strcat(temp, &copy[i]);
            //     printf("%c", copy[i]); //This code goes through each line of the file and is able to sperate those lines by words
                 spaceChecker = 0;
                 charCount = 1;
              //   printf("\n");
            }
        }
    }
        if(charCount ==1 && totalWords ==0){
            totalWords++;
        }
     //   printf("\n");
     //   printf("Total Word: %d\n", totalWords);
        //printf("charCount: %d\n", charCount);
        return totalWords; //TODO code proper spacing 
}

int main(){

    //gcc ww.c -o ww
    //./ww

    FILE *unwrapped = fopen("test1.txt", "r");
    if(unwrapped == NULL){
        printf("File unable to open.");
        exit(1);
    }

    FILE *solution = fopen("solution.txt", "w");
    if(unwrapped == NULL){
        printf("File unable to open.");
        exit(1);
    }


    char buf[BUFFER];
    int myWidth = 20;
    int totalWords = 0; //current space at the start
    char *word;
    while(fgets(buf, BUFFER, unwrapped)){
        if(buf[0]=='\n'){
            printf("NewLine\n");
        }
        else{
        buf[strcspn(buf, "\n")] = '\0'; //removes new line character from the end.
       // totalWords = helper(buf, myWidth, totalWords); //the helper function will write into the file and return total words.
        //printf("Total Word: %d\n", totalWords);
        word = strtok (buf," ");
        //printf( "Size of word:%ld\n", strlen(word));
        while (word != NULL)
       {
         printf( "Size of word:%ld\n", strlen(word));
         printf ("%s\n",word);
         word = strtok (NULL, " ");

        
       }
        }
      //  break;
    }

    fclose(unwrapped);
    fclose(solution);
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
