#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <dirent.h>

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

void fileWrapper(char  *txtFiles[], int userWidth){
    int newLine=0;
    char buf[BUFFER];
    int myWidth = userWidth;
    int currentWidth = 0;
    int totalWords = 0; //current space at the start
    char *word;

     char *fileName;
     fileName = strtok (txtFiles,".txt");

        while (fileName != NULL)
            {
                char * namer = "wrap";
                char * txt = ".txt";

                char *temp = strcat(namer ,fileName);
                char *tempin = strcat(fileName, txt);

                 FILE *out = fopen(temp, "w");
                 FILE *in = fopen(tempin, "r");
            

    while(fgets(buf, BUFFER, in)){
        if(buf[0]=='\n'){
            if(newLine==0){
                //printf("NewLine\n");
                fprintf(out, "\n\r");
                newLine=1;
            }
        }
        else{
            newLine=0;
            buf[strcspn(buf, "\n")] = '\0'; //removes new line character from the end.
            // totalWords = helper(buf, myWidth, totalWords); //the helper function will write into the file and return total words.
            //printf("Total Word: %d\n", totalWords);
            word = strtok (buf," ");
            //printf( "Size of word:%ld\n", strlen(word));
            while (word != NULL)
            {
                //printf( "Size of word:%ld\n", strlen(word));
                //printf ("%s\n",word);
                currentWidth =  currentWidth + strlen(word)+1;

                if(currentWidth <= myWidth){
                    fprintf(out, "%s ", word);
                }
                else{
                     fprintf(out, "\n");
                     fprintf(out, "%s ", word);
                     currentWidth = 0;
                     currentWidth = currentWidth + strlen(word)+1;
                }
                word = strtok (NULL, " ");
            }
        }
      //  break;
    }
     fileName = strtok (NULL, " ");
            }
}

void consoleWrapper(FILE *in, int userWidth){
    int newLine=0;
    char buf[BUFFER];
    int myWidth = userWidth;
    int currentWidth = 0;
    int totalWords = 0; //current space at the start
    char *word;
    while(fgets(buf, BUFFER, in)){
        if(buf[0]=='\n'){
            if(newLine==0){
                //printf("NewLine\n");
                printf("\n");
                newLine=1;
            }
            else{
                printf("\n\n");
            }
        }
        else{
            newLine=0;
            buf[strcspn(buf, "\n")] = '\0'; //removes new line character from the end.
            // totalWords = helper(buf, myWidth, totalWords); //the helper function will write into the file and return total words.
            //printf("Total Word: %d\n", totalWords);
            word = strtok (buf," ");
            //printf( "Size of word:%ld\n", strlen(word));
            while (word != NULL)
            {
                //printf( "Size of word:%ld\n", strlen(word));
                //printf ("%s\n",word);
                currentWidth =  currentWidth + strlen(word)+1;

                if(currentWidth <= myWidth){
                    printf("%s ", word);
                }
                else{
                     printf("\n");
                     newLine=1;
                     printf("%s ", word);
                     currentWidth = 0;
                     currentWidth = currentWidth + strlen(word)+1;
                }
                word = strtok (NULL, " ");
            }
        }
      //  break;
    }
}

int main(int argc, char *argv[]){

    //gcc ww.c -o ww
    //./ww
    int userWidth =  atoi(argv[1]);
    //char *testvar = strdup(argv[2]); //free
   //printf("%s", testvar);
    struct dirent *dir; //need to close maybe
    DIR *path; //need to close maybe. this wrong btw need help
    path = opendir(argv[2]);
    int dirct =0;
    int file = 0;
    FILE *unwrapped = fopen(argv[2], "r");
    
    if(path == NULL){
        dirct = 1;
       // printf("Dirct: %d\n", dirct);
       //perror("Directory unable to open.");
       //exit(1);
    }
     //printf("Dirct out if: %d\n", dirct);

     if(dirct == 0){
         char *txtFiles[256];
         int index = 0;
        while((dir=readdir(path))!=NULL){
            const size_t len = strlen(dir->d_name);
            if (len > 4                     &&
                dir->d_name[len - 4] == '.' &&
                dir->d_name[len - 3] == 't' &&
                dir->d_name[len - 2] == 'x' &&
                dir->d_name[len - 1] == 't'){

                txtFiles[index] = dir->d_name;
                 printf ("%s\n", txtFiles[index]);
                index ++;
               // printf ("%s\n", dir->d_name);
         }

    }

    fileWrapper(txtFiles, userWidth);

    }

    
    if(unwrapped == NULL){
        file = 1;
       // printf("File: %d\n", file);
        // perror("File unable to open.");
        // exit(1);
    }
   //  printf("File out if: %d\n", file);

   
    if(dirct == 1 && file == 0){
        consoleWrapper(unwrapped, userWidth);
    }
    if(dirct == 1 && file == 1){
        perror("Not acceptable argument.");
    }

  
       
   
    

   

    // FILE *solution = fopen("solution.txt", "w");
    // if(solution == NULL){
    //     perror("File unable to open.");
    //     exit(1);
    // }
   // fileWrapper(unwrapped, solution, userWidth);
    
    

    fclose(unwrapped);
    //fclose(solution);
}











