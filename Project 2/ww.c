#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

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

/*void fileWrapper(FILE *in, FILE *out, int userWidth){
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
}*/

void wrapper(int in, int out,int userWidth){
    if(in==-1&&out==-1)
        return;
    char cur[2] = "\0";
    int r = (char)read(in,cur,1);
    char* temp=(char*)malloc(sizeof(char));
    char* word=(char*)malloc(sizeof(char));
    int newLine= 0, currentWidth = 0, totalWords = 0, wLength = 1, space = 0;
    while(r!=0){
        if(cur[0]=='\n'){
            if(newLine==0){
                int sum = (currentWidth) + wLength;
                if(sum <= userWidth || currentWidth==0){
                    if(out==-1){
                        printf("%s ", word);
                    }
                    else{
                        write(out, word, wLength);
                        write(out, " ", strlen(" "));
                    }
                    currentWidth = sum+1;
                }
                else{
                    if(out==-1){
                        printf("\n%s ", word);
                    }
                    else{
                        write(out, "\n", strlen("\n"));
                        write(out, word, strlen(word));
                        write(out, " ", strlen(" "));
                    }
                    currentWidth =wLength+1;
                }
            }
            else if(newLine==1){
                currentWidth = 0;
                space = 0;
                if(out==-1){
                    printf("\n\n");
                }
                else{
                    write(out, "\r\n", strlen("\r\n"));
                }
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
                    if(out==-1){
                        printf("%s ", word);
                    }
                    else{
                        write(out, word, strlen(word));
                        write(out, " ", strlen(" "));
                    }
                    currentWidth = sum+1;
                    space++;
                }
                else{
                    if(out==-1){
                        printf("\n%s ", word);
                    }
                    else{
                        write(out, "\n", strlen("\n"));
                        write(out, word, strlen(word));
                        write(out, " ", strlen(" "));
                    }
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
        r= (char)read(in,cur,1);;
    }
    int sum = (currentWidth) + wLength;
    if(sum <= userWidth || currentWidth==0){
        if(out==-1){
            printf("%s ", word);
        }
        else{
            write(out, word, strlen(word));
            write(out, " ", strlen(" "));
        }
    }
    else{
        if(out==-1){
            printf("\n%s ", word);
        }
        else{
            write(out, "\n", strlen("\n"));
            write(out, word, strlen(word));
            write(out, " ", strlen(" "));
        }
    }
}

void directoryExplorer(int userWidth, DIR *path, char* directory){
    struct dirent *dir;
    char *txtFiles[BUFFER];
    int index = 0;
    int currentFile;
    int outFile;
    while((dir=readdir(path))!=NULL){
        const size_t len = strlen(dir->d_name);
        //printf("%d\n", len);
        if( dir->d_name[0] == 'w' &&
            dir->d_name[1] == 'r' &&
            dir->d_name[2] == 'a' &&
            dir->d_name[3] == 'p' &&
            dir->d_name[4] == '.' ){
                break;
            }
        if (len > 4                     &&
            dir->d_name[len - 4] == '.' &&
            dir->d_name[len - 3] == 't' &&
            dir->d_name[len - 2] == 'x' &&
            dir->d_name[len - 1] == 't' ){
            txtFiles[index] = dir->d_name;
            char curName[BUFFER];
            memset(curName, 0, sizeof(curName));
            strcat(curName, directory);
            strcat(curName, "/");
            strcat(curName, txtFiles[index]);
            currentFile = open(curName,O_RDONLY);
            char *wrap = "wrap.";
            char finalName[BUFFER];
            memset(finalName, 0, sizeof(finalName));
            strcat(finalName, directory);
            strcat(finalName, "/");
            strcat(finalName,wrap);
            strcat(finalName,txtFiles[index]);
            outFile = open(finalName,O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR);
            wrapper(currentFile, outFile, userWidth);
            index ++;
            close(currentFile);
            close(outFile);
        }

    }
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

int main(int argc, char *argv[]){
    if(argc!=3){
        printf("Invalid number of argumments\n");
        return-1;
    }
    int userWidth =  atoi(argv[1]);
    DIR *path;
    path = opendir(argv[2]);
    int rd = open(argv[2],O_RDONLY);
    struct stat dirFile;
    int status = stat (argv[2], &dirFile);

    //FILE *unwrapped = fopen(argv[2], "r");
    if(status != 0){
        closedir(path);
        perror("The Second Console Argument is INVALID Due to: \n  --Invaild Directory \n          OR \n  --File Doesn't Exist \n");
        return -1;
    }
    else if(S_ISREG(dirFile.st_mode)){
        wrapper(rd, -1,userWidth);
    }
    else if(S_ISDIR(dirFile.st_mode)){
        directoryExplorer(userWidth, path, argv[2]);
    }
    close(rd);
    closedir(path);
}