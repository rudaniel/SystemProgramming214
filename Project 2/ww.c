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
            if(newLine==0){
                printf("\n");
                newLine=1;
            }
            else{
                printf("\n\n");
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
    }
   
}

int main(int argc, char *argv[]){
    int userWidth =  atoi(argv[1]);
    struct dirent *dir;
    DIR *path;
    path = opendir(argv[2]);
    FILE *unwrapped = fopen(argv[2], "r");
    if(path == NULL && unwrapped != NULL){
        consoleWrapper(unwrapped, userWidth);
    }
    else if(path == NULL && unwrapped == NULL){
        fclose(unwrapped);
        closedir(path);
        perror("Not acceptable argument.");
    }
    else if(path != NULL){
         char *txtFiles[256];
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
                char curName[256];
                memset(curName, 0, sizeof(curName));
                strcat(curName, argv[2]);
                strcat(curName, "/");
                strcat(curName, txtFiles[index]);
                currentFile = fopen(curName, "r");
                char *wrap = "wrap";
                char finalName[256];
                memset(finalName, 0, sizeof(finalName));
                strcat(finalName, argv[2]);
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
    fclose(unwrapped);
    closedir(path);
}











