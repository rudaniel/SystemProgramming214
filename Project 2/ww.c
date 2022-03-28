#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <dirent.h>

#define BUFFER 256
#define DELIM " \n"
#define INITIALIZE \
    int newLine=0; \
    char buf[BUFFER];\
    int currentWidth = 0; \
    int totalWords = 0; \
    char *word; 
#define INLOOP(word, currentWidth) \
    int wLength = ((strlen(word))+1);\
    int sum = (currentWidth) + wLength;

void fileWrapper(FILE *in, FILE *out, int userWidth){
    INITIALIZE;
    while(fgets(buf, BUFFER, in)){
        if(buf[0]=='\n'){
            if(newLine==0){
                fprintf(out, "\r\n");
                newLine=1;
            }
        }
        else{
            newLine=0;
            word = strtok (buf,DELIM);
            while (word != NULL){
                INLOOP(word, currentWidth);
                if(sum <= userWidth || currentWidth==0){
                    fprintf(out, "%s ", word);
                    currentWidth = sum;
                }
                else{
                     fprintf(out, "\n%s ", word);
                     currentWidth = wLength;
                }
                word = strtok (NULL, DELIM);
            }
        }
    }
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
            char *wrap = "wrap.";
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

/*void consoleWrapper(FILE *in, int userWidth){
    INITIALIZE;
    while(fgets(buf, BUFFER, in)){
        if(buf[0]=='\n'){
            currentWidth = 0;
            if(newLine==0){
                printf("\n\n");
                newLine=1;
            }
        }
        else{
            newLine=0;
            word = strtok (buf,DELIM);
            while (word != NULL){
                INLOOP(word, currentWidth);
                if(sum <= userWidth || currentWidth==0){
                    printf("%s ", word);
                    currentWidth = sum;
                }
                else{
                     printf("\n%s ", word);
                     currentWidth =wLength;
                }
                word = strtok (NULL, DELIM);
            }
        }
    }
   //added to end last line and start new one;
    printf("\n");
}*/

void consoleWrapper(FILE *in, int userWidth){
    char cur[2] = "\0";
    cur[0] = fgetc(in);
    if(cur[0]==EOF)
        return;
    char* temp=(char*)malloc(sizeof(char)), word=(char*)malloc(sizeof(char));
    int newLine= 0, currentWidth = 0, totalWords = 0, wLength = 1, space = 0;
    while(cur[0]!=EOF){
        if(cur[0]=='\n'){
            if(newLine==0){
                int sum = (currentWidth) + wLength;
                if(sum <= userWidth || currentWidth==0){
                    printf("%s ", word);
                    currentWidth = sum+1;
                }
                else{
                    printf("\n%s ", word);
                    currentWidth =wLength+1;
                }
            }
            else if(newLine==1){
                currentWidth = 0;
                space = 0;
                printf("\n\n");
            }
            newLine++;
            wLength=0;
            free(word);
            word= (char*)malloc(sizeof(char));
            strcpy(word, "");
        }
        else if(cur[0]==' '){
            if(space == 0){
                int sum = (currentWidth) + wLength;
                if(sum <= userWidth || currentWidth==0){
                    printf("%s ", word);
                    currentWidth = sum+1;
                    space++;
                }
                else{
                    printf("\n%s ", word);
                    currentWidth =wLength+1;
                    space=0;
                }
            }
            free(word);
            word= (char*)malloc(sizeof(char));
            strcpy(word, "");
            newLine = 0;
            wLength=0;
        }
        else{
            newLine = 0;
            space = 0;
            wLength++;
            temp= (char*)malloc(wLength*sizeof(char));
            strcpy(temp,word);
            strcat(temp, cur);
            free(word);
            word= (char*)malloc(wLength*sizeof(char));
            strcpy(word,temp);
            free(temp);
        }
        cur[0]= fgetc(in);
    }
    int sum = (currentWidth) + wLength;
    if(sum <= userWidth || currentWidth==0){
        printf("%s ", word);
        currentWidth = sum+1;
    }
    else{
        printf("\n%s ", word);
        currentWidth =wLength;
    }
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