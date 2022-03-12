#include<stdio.h>
#include<stdlib.h>
#include <string.h>

int main(){

    FILE *unwrapped = fopen("test1.txt", "r");
    if(unwrapped == NULL){
        printf("File unable to open.");
        exit(1);
    }

    char buf[256];
    char copy[100];

    while(fgets(buf, 256, unwrapped)){
        strncpy(copy, buf, 256);
        for(int i =0; i<256;i++){
            if(copy[i] == ' '){
                printf("\n");
            }
            else{
                 printf("%c", copy[i]); //This code goes through each line of the file and is able to sperate those lines by words
            }
           
        }
       // printf("NEW LINE\n");

    }







    fclose(unwrapped);
}