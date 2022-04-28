#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pthread.h>
#include "wordwrap.h"

int main(int argc, char *argv[]){
    int args=argc;
    char* version=argv[1];
    int width;
    int recursion;
    int offset=0;
    struct stat dirFile;
    int status;
    if(version[0]=='-'&& version[1]=='r'){
        printf("Recursive code: \n");
        width =  atoi(argv[2]);
        for(args-=3;args>0; args--,offset++){
            dCount=0;
            fCount=0;
            //printf("Number of args: %d\n",args);
            status = stat (argv[3+offset], &dirFile);
            if(status != 0){
                perror("The Second Console Argument is INVALID Due to: \n  --Invaild Directory \n          OR \n  --File Doesn't Exist \n");
                exit(EXIT_FAILURE);
            }
            if(S_ISDIR(dirFile.st_mode)){
                addDirectory(argv[3+offset]);
                dCount++;
                char* f=malloc(strlen(argv[1])+1);
                strcpy(f,argv[1]);
                int length=strlen(f);
                int count=0;
                char* token = strtok(f, ",");
                while (token) {
                    token = strtok(NULL, ",");
                    count++;
                }
                free(f);
                f=malloc(strlen(argv[1])+1);
                strcpy(f,argv[1]);
                if(strcmp(f,"-r")==0){
                    printf("    Regular\n\n");
                    r(width,1,1);
                }
                else if(count==1&&f[0]=='-'&&f[1]=='r'&& length>2){
                    char* num= malloc(length+1);
                    memcpy(num,&f[2],(length-2));
                    int threads=atoi(num);
                    free(num);
                    free(f);
                    printf("    Using %d Threads\n\n",threads);
                    r(width,threads,1);
                }
                else{
                    char* tok = strtok(f, ",");
                    count=0;
                    char* temp;
                    int t2;
                    while (tok) {
                        if(count==0){
                            temp= malloc(strlen(tok)+1);
                            strcpy(temp,tok);
                        }
                        else if(count==1){
                            t2=atoi(tok);
                        }
                        count++;
                        tok = strtok(NULL, ",");
                    }
                    char num[(length-1)];
                    memcpy(num,&temp[2],(length-2));
                    int threads=atoi(num);
                    free(f);
                    free(temp);
                    printf("    Using %d Threads for Directories and %d Threads for Files.\n\n",threads,t2);
                    r(width,t2,threads);
                }
            }
            else{
                int rd = open(argv[3+offset],O_RDONLY);
                if(S_ISREG(dirFile.st_mode)){
                    wrapper(rd, -1,width);
                    fCount++;
                }
            }
            while (dHead != NULL) {
                deleteDirectory();
            }
            while (fHead != NULL) {
                deleteFile();
            }
        }
        if(argc==3){
            printf("Enter text now:(Press ctrl d to run word wrapper)\n");
            wrapper(0, -1, atoi(argv[2]));
        }
    }
    else{
        if(argc<1){
            printf("Invalid number of argumments\n");
            return-1;
        }
        else if(argc==2){
            printf("Enter text now:(Press ctrl d to run word wrapper)\n");
            wrapper(0, -1, atoi(argv[1]));
        }
        else {
            for(args-=2;args>0; args--,offset++){
                //printf("Number of args: %d\n",args);
                dCount=0;
                fCount=0;
                width =  atoi(argv[1]);
                int rd = open(argv[2+offset],O_RDONLY);
                status = stat (argv[2+offset], &dirFile);
                if(status != 0){
                    close(rd);
                    perror("The Second Console Argument is INVALID Due to: \n  --Invaild Directory \n          OR \n  --File Doesn't Exist \n");
                    exit(EXIT_FAILURE);
                }
                else if(S_ISREG(dirFile.st_mode)){
                    wrapper(rd, -1,width);
                    fCount++;
                }
                else if(S_ISDIR(dirFile.st_mode)){
                    recursion=0;
                    addDirectory(argv[2+offset]);
                    dCount++;
                    makeDl(&recursion);
                    fileW(&width);
                }
                close(rd);
            }
        }
    }
    pthread_exit(NULL);
}