#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUFFER 256

void wrapper(int in, int out,int userWidth){
    if(in==-1&&out==-1)
        return;
    char cur[2] = "\0";
    char* temp;
    char* word=(char*)malloc(sizeof(char));
    strcpy(word, "\0");
    char* text=(char*)malloc(sizeof(char));
    strcpy(text, "\0");
    int newLine= 0, currentWidth = 0, wLength = 1, space = 0, totalWidth = 0, error = 0, new = 0;
    while(read(in,cur,1)>0){
        if(cur[0]=='\n'){
            if(newLine==0){
                totalWidth++;
                if(wLength>userWidth){
                    error=1;
                }
                int sum = (currentWidth) + wLength;
                if(sum <= userWidth || currentWidth==0){
                    currentWidth = sum+1;
                    temp= (char*)malloc(totalWidth*sizeof(char));
                    strcpy(temp,text);
                    if(new==0){
                        new=1;
                    }
                    else{
                        strcat(temp, " ");
                    }
                    strcat(temp, word);
                    free(text);
                    text= (char*)malloc(totalWidth*sizeof(char));
                    strcpy(text,temp);
                    free(temp);
                }
                else{
                    currentWidth =wLength+1;
                    temp= (char*)malloc(totalWidth*sizeof(char));
                    strcpy(temp,text);
                    strcat(temp, "\n");
                    strcat(temp, word);
                    free(text);
                    text= (char*)malloc(totalWidth*sizeof(char));
                    strcpy(text,temp);
                    free(temp);
                }
            }
            else if(newLine==1){
                totalWidth++;
                currentWidth = 0;
                space = 0;
                new = 0;
                totalWidth++;
                temp= (char*)malloc(totalWidth*sizeof(char));
                strcpy(temp,text);
                strcat(temp, "\n\n");
                free(text);
                text= (char*)malloc(totalWidth*sizeof(char));
                strcpy(text,temp);
                free(temp);
            }
            newLine++;
            wLength=0;
            free(word);
            word= (char*)malloc(sizeof(char));
            strcpy(word, "\0");
        }
        else if(cur[0]==' '){
            if(space == 0){
                if(wLength>userWidth){
                    error=1;
                }
                totalWidth++;
                int sum = (currentWidth) + wLength;
                if(sum <= userWidth || currentWidth==0){
                    temp= (char*)malloc((totalWidth*2)*sizeof(char));
                    strcpy(temp,text);
                    if(new==0){
                        new=1;
                    }
                    else{
                        strcat(temp, " ");
                    }
                    strcat(temp, word);
                    free(text);
                    text= (char*)malloc((totalWidth*2)*sizeof(char));
                    strcpy(text,temp);
                    free(temp);
                    currentWidth = sum+1;
                    space++;
                }
                else{
                    totalWidth++;
                    temp= (char*)malloc(totalWidth*sizeof(char));
                    strcpy(temp,text);
                    strcat(temp, "\n");
                    strcat(temp, word);
                    free(text);
                    text= (char*)malloc(totalWidth*sizeof(char));
                    strcpy(text,temp);
                    free(temp);
                    currentWidth =wLength+1;
                    space=0;
                }
            }
            free(word);
            word= (char*)malloc(sizeof(char));
            strcpy(word, "\0");
            newLine = 0;
            wLength=0;
        }
        else{
            newLine = 0;
            space = 0;
            wLength++;
            totalWidth++;
            temp= (char*)malloc((wLength*2)*sizeof(char));
            strcpy(temp,word);
            strcat(temp, cur);
            free(word);
            word= (char*)malloc((wLength*2)*sizeof(char));
            strcpy(word,temp);
            free(temp);
        }
    }
    int sum = (currentWidth) + wLength;
    if(wLength>userWidth){
        error=1;
    }
    if(sum <= userWidth || currentWidth==0){
        temp= (char*)malloc((totalWidth*2)*sizeof(char));
        strcpy(temp,text);
        strcat(temp, word);
        free(text);
        text= (char*)malloc((totalWidth*2)*sizeof(char));
        strcpy(text,temp);
    }
    else{
        totalWidth++;
        temp= (char*)malloc((totalWidth*2)*sizeof(char));
        strcpy(temp,text);
        strcat(temp, "\n");
        strcat(temp, word);
        free(text);
        text= (char*)malloc((totalWidth*2)*sizeof(char));
        strcpy(text,temp);
    }
    if(out==-1){
        printf("%s\n", text);
    }
    else{
        int o=write(out, text, strlen(text));
        if(o>0){
        o=write(out, "\n", 1);
        }
    }
    free(text);
    free(word);
    free(temp);
    if(error==1){
        printf("error: word length exceeded user wrap\n");
        close(in);
        close(out);
        exit(EXIT_FAILURE);
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
        if( dir->d_name[0] == '.'){
        }
        else if( dir->d_name[0] == 'w' &&
            dir->d_name[1] == 'r' &&
            dir->d_name[2] == 'a' &&
            dir->d_name[3] == 'p' &&
            dir->d_name[4] == '.' ){
            }
        else if (len > 4                     &&
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
            outFile = open(finalName,O_WRONLY|O_CREAT|O_TRUNC,S_IRWXU|S_IRWXG|S_IRWXO);
            wrapper(currentFile, outFile, userWidth);
            index ++;
            close(currentFile);
            close(outFile);
        }

    }
}

int main(int argc, char *argv[]){
    if(argc<1){
        printf("Invalid number of argumments\n");
        return-1;
    }
    else if(argc==2){
        printf("Enter text now:(Press ctrl d to run word wrapper)\n");
        wrapper(0, -1, atoi(argv[1]));
    }
    else {
        int userWidth =  atoi(argv[1]);
        DIR *path;
        path = opendir(argv[2]);
        int rd = open(argv[2],O_RDONLY);
        struct stat dirFile;
        int status = stat (argv[2], &dirFile);
        if(status != 0){
            close(rd);
            closedir(path);
            perror("The Second Console Argument is INVALID Due to: \n  --Invaild Directory \n          OR \n  --File Doesn't Exist \n");
            exit(EXIT_FAILURE);
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
}