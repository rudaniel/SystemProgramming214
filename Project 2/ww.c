#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <dirent.h>

#define BUFFER 256

void fileWrapper(FILE *in, FILE *out, int userWidth){
    int newLine=0;
    char buf[BUFFER];
    int myWidth = userWidth;
    int currentWidth = 0;
    int totalWords = 0;
    char *word;
    while(fgets(buf, BUFFER, in)){
        if(buf[0]=='\n'){
            if(newLine==0){
                fprintf(out, "\n\r");
                newLine=1;
            }
        }
        else{
            newLine=0;
            buf[strcspn(buf, "\n")] = '\0';
            word = strtok (buf," ");
            while (word != NULL)
            {
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
    }
}

void consoleWrapper(FILE *in, int userWidth){
    int newLine=0;
    char buf[BUFFER];
    int myWidth = userWidth;
    int currentWidth = 0;
    int totalWords = 0;
    char *word;
    while(fgets(buf, BUFFER, in)){
        if(buf[0]=='\n'){
            currentWidth = 0;
            /*if(newLine==0){
                printf("\n");
            }
            else if(newLine==1){
                printf("\n\n");
            }*/
            //newLine=2;
            if(newLine==0){
                printf("\n\n");
                newLine=1;
            }
        }
        else{
            newLine=0;
            //buf[strcspn(buf, "\n")] = '\0';
            word = strtok (buf," \n");
            while (word != NULL)
            {
                int wLength= strlen(word)+1;
                //printf(" CW: %d ",currentWidth);
                //printf(" WL: %d ",wLength);
                //currentWidth =  currentWidth + wLength;
                if((currentWidth + wLength) <= myWidth || currentWidth==0){
                    printf("%s ", word);
                    currentWidth =  currentWidth + wLength;
                    //printf(" FIRST ");
                }
                // else if(wLength > myWidth){
                //     printf(" MIDDLE ");
                //     printf("%s\n", word);
                //     currentWidth= currentWidth + wLength;
                //     newLine=3;
                // }
                else{
                     //newLine=1;
                     printf("\n%s ", word);
                     currentWidth =wLength;
                     //printf(" LAST ");
                }
                //printf(" CL: %d ",wLength);
                word = strtok (NULL, " \n");
            }
        }
    }
   //added to end last line and start new one;
        printf("\n");
}

void directoryExplorer(int userWidth, DIR *path, char* directory){
    struct dirent *dir;
    char *txtFiles[BUFFER];
    int index = 0;
    FILE *currentFile;
    FILE *outFile;
    while((dir=readdir(path))!=NULL){
        const size_t len = strlen(dir->d_name);
        if (len > 4                     &&
            dir->d_name[len - 4] == '.' &&
            dir->d_name[len - 3] == 't' &&
            dir->d_name[len - 2] == 'x' &&
            dir->d_name[len - 1] == 't'){
            txtFiles[index] = dir->d_name;
            char curName[BUFFER];
            memset(curName, 0, sizeof(curName));
            strcat(curName, directory);
            strcat(curName, "/");
            strcat(curName, txtFiles[index]);
            currentFile = fopen(curName, "r");
            char *wrap = "wrap";
            char finalName[BUFFER];
            memset(finalName, 0, sizeof(finalName));
            strcat(finalName, directory);
            strcat(finalName, "/");
            strcat(finalName,wrap);
            strcat(finalName,txtFiles[index]);
            outFile = fopen(finalName, "w");
            fileWrapper(currentFile, outFile, userWidth);
            index ++;
        }

    }
    fclose(currentFile);
    fclose(outFile);
}

int main(int argc, char *argv[]){
    if(argc!=3){
        printf("Invalid number of argumments\n");
        return-1;
    }
    int userWidth =  atoi(argv[1]);
    DIR *path;
    path = opendir(argv[2]);
    FILE *unwrapped = fopen(argv[2], "r");
    if(path == NULL && unwrapped == NULL){
        closedir(path);
        perror("The Second Console Argument is INVALID Due to: \n  --Invaild Directory \n          OR \n  --File Doesn't Exist \n");
        return -1;
    }
    else if(path != NULL){
        directoryExplorer(userWidth, path, argv[2]);
    }
    else if(unwrapped != NULL){
        consoleWrapper(unwrapped, userWidth);
    }
    fclose(unwrapped);
    closedir(path);
}