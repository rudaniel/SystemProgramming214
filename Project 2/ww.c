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
    char* temp=(char*)malloc(sizeof(char));
    char* word=(char*)malloc(sizeof(char));
    char* text=(char*)malloc(sizeof(char));
    int newLine= 0, currentWidth = 0, totalWords = 0, wLength = 1, space = 0, totalWidth = 0, error = 0;
    while(read(in,cur,1)>0){
        if(cur[0]=='\n'){
            if(newLine==0){
                totalWidth++;
                if(wLength>userWidth){
                    error=1;
                }
                int sum = (currentWidth) + wLength;
                if(sum <= userWidth || currentWidth==0){
                    /*if(out==-1){
                        printf("%s ", word);
                    }
                    else{
                        write(out, word, wLength);
                        write(out, " ", strlen(" "));
                    }*/
                    currentWidth = sum+1;
                    temp= (char*)malloc(totalWidth*sizeof(char));
                    strcpy(temp,text);
                    strcat(temp, word);
                    strcat(temp, " ");
                    //1 %s\n",text);
                    free(text);
                    text= (char*)malloc(totalWidth*sizeof(char));
                    strcpy(text,temp);
                    //2\n");
                    free(temp);
                }
                else{
                   /* if(out==-1){
                        printf("\n%s ", word);
                    }
                    else{
                        write(out, "\n", strlen("\n"));
                        write(out, word, strlen(word));
                        write(out, " ", strlen(" "));
                    }*/
                    currentWidth =wLength+1;
                    totalWidth++;
                    temp= (char*)malloc(totalWidth*sizeof(char));
                    strcpy(temp,text);
                    strcat(temp, "\n");
                    strcat(temp, word);
                    strcat(temp, " ");
                    //3\n");
                    free(text);
                    text= (char*)malloc(totalWidth*sizeof(char));
                    strcpy(text,temp);
                    //4\n");
                    free(temp);
                }
            }
            else if(newLine==1){
                totalWidth++;
                //totalWidth = totalWidth+currentWidth;
                currentWidth = 0;
                space = 0;
                totalWidth++;
                temp= (char*)malloc(totalWidth*sizeof(char));
                strcpy(temp,text);
                strcat(temp, "\n\n");
                //5\n");
                free(text);
                text= (char*)malloc(totalWidth*sizeof(char));
                strcpy(text,temp);
                //6\n");
                free(temp);
            }
            newLine++;
            wLength=0;
            //7\n");
            free(word);
            word= (char*)malloc(sizeof(char));
            strcpy(word, "");
        }
        else if(cur[0]==' '){
            if(space == 0){
                if(wLength>userWidth){
                    error=1;
                }
                totalWidth++;
                int sum = (currentWidth) + wLength;
                if(sum <= userWidth || currentWidth==0){
                    /*if(out==-1){
                        printf("%s ", word);
                    }
                    else{
                        write(out, word, strlen(word));
                        write(out, " ", strlen(" "));
                    }*/
                    temp= (char*)malloc(totalWidth*sizeof(char));
                    strcpy(temp,text);
                    strcat(temp, word);
                    strcat(temp, " ");
                    //8\n");
                    free(text);
                    text= (char*)malloc(totalWidth*sizeof(char));
                    strcpy(text,temp);
                    //9\n");
                    free(temp);
                    currentWidth = sum+1;
                    space++;
                }
                else{
                    /*if(out==-1){
                        printf("\n%s ", word);
                    }
                    else{
                        write(out, "\n", strlen("\n"));
                        write(out, word, strlen(word));
                        write(out, " ", strlen(" "));
                    }*/
                    totalWidth+=2;
                    temp= (char*)malloc(totalWidth*sizeof(char));
                    strcpy(temp,text);
                    strcat(temp, "\n");
                    strcat(temp, word);
                    strcat(temp, " ");
                    //10\n");
                    free(text);
                    text= (char*)malloc(totalWidth*sizeof(char));
                    strcpy(text,temp);
                    //11\n");
                    free(temp);
                    currentWidth =wLength+1;
                    space=0;
                }
            }
            //12\n");
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
            totalWidth++;
            temp= (char*)malloc(wLength*sizeof(char));
            strcpy(temp,word);
            strcat(temp, cur);
            //13\n");
            free(word);
            word= (char*)malloc(wLength*sizeof(char));
            strcpy(word,temp);
            //14\n");
            free(temp);
        }
    }
    int sum = (currentWidth) + wLength;
    //totalWidth+=sum;
    if(wLength>userWidth){
        error=1;
    }
    if(sum <= userWidth || currentWidth==0){
        /*if(out==-1){
            printf("%s", word);
        }
        else{
            write(out, word, strlen(word));
            //write(out, " ", strlen(" "));
        }*/
        temp= (char*)malloc(totalWidth*sizeof(char));
        strcpy(temp,text);
        strcat(temp, word);
        //strcat(temp, " ");
        //15\n");
        free(text);
        text= (char*)malloc(totalWidth*sizeof(char));
        strcpy(text,temp);
        //16\n");
        free(temp);
        //totalWidth++;
    }
    else{
        /*if(out==-1){
            printf("\n%s", word);
        }
        else{
            write(out, "\n", strlen("\n"));
            write(out, word, strlen(word));
            //write(out, " ", strlen(" "));
        }*/
        totalWidth++;
        temp= (char*)malloc(totalWidth*sizeof(char));
        strcpy(temp,text);
        strcat(temp, "\n");
        strcat(temp, word);
        //17\n");
        free(text);
        text= (char*)malloc(totalWidth*sizeof(char));
        strcpy(text,temp);
        //18\n");
        free(temp);
    }
    if(out==-1){
        printf("%s\n", text);
    }
    else{
        write(out, text, strlen(text));
        //write(out, word, strlen(word));
        //write(out, " ", strlen(" "));
    }
    if(error==1){
        printf("error: word length exceeded user wrap\n");
        close(in);
        close(out);
        exit(EXIT_FAILURE);
    }
    //printf("\ntotalWidth: %d\n",totalWidth-2);
}

void directoryExplorer(int userWidth, DIR *path, char* directory){
    struct dirent *dir;
    char *txtFiles[BUFFER];
    int index = 0;
    int currentFile;
    int outFile;
    while((dir=readdir(path))!=NULL){
        const size_t len = strlen(dir->d_name);
        //printf("cccc\n");
        //printf("%s\n", dir->d_name);
        if( dir->d_name[0] == '.'){
            //printf("broken 1\n");
           // break;
        }
        else if( dir->d_name[0] == 'w' &&
            dir->d_name[1] == 'r' &&
            dir->d_name[2] == 'a' &&
            dir->d_name[3] == 'p' &&
            dir->d_name[4] == '.' ){
                //printf("broken 2\n");
                //break;
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
           // printf("outfile %d\n",outFile);
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

        //FILE *unwrapped = fopen(argv[2], "r");
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