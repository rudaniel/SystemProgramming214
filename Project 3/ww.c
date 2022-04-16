#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pthread.h>

#define BUFFER 256

typedef struct File{
    char* in;
    char* out;    
    struct File *next;
} File;

typedef struct Directory{
    char* in; 
    struct Directory *next;
} Directory;

pthread_mutex_t fLock;
File* fHead;

pthread_mutex_t dLock;
Directory* dHead;

pthread_mutex_t lock;

void addFile(char* in, char* out){
    File* temp= (struct File*)malloc(sizeof(struct File));
    File* node= fHead;
    temp->in = malloc(strlen(in)+10);
    temp->out = malloc(strlen(out)+10);
    temp->next=NULL;
    strcpy(temp->in,in);
    strcpy(temp->out,out);
    if(fHead==NULL){
        fHead=temp;
    }
    else{
        while(node->next!=NULL){
            node=node->next;
        }
        node->next = temp;
    }
}

void deleteFile(){
    if(fHead!=NULL){
        File* temp = fHead;
        fHead= fHead->next;
        free(temp->in);
        free(temp->out);
        free(temp);
    }
}

void addDirectory(char* in){
    Directory* temp= (struct Directory*)malloc(sizeof(struct Directory));
    Directory* node= dHead;
    temp->in = (char*)malloc(strlen(in)+10);
    strcpy(temp->in,in);
    temp->next=NULL;
    if(dHead==NULL){
        dHead=temp;
    }
    else{
        while(node->next!=NULL){
            node=node->next;
        }
        node->next = temp;
    }
}

void deleteDirectory(){
    if(dHead!=NULL){
        Directory* temp = dHead;
        dHead= dHead->next;
        free(temp->in);
        free(temp);
    }
}
int thread=0;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* makeDl(){
    pthread_mutex_lock(&dLock);
    if(dHead==NULL){
        thread--;
        while (dHead==NULL && thread > 0) {
            pthread_cond_wait(&cond, &dLock);
        }
        if(dHead==NULL&&thread<=0){
            printf("    Quiting Directory thread- %lu\n",pthread_self());
            pthread_cond_broadcast(&cond);
            pthread_mutex_unlock(&dLock);
            pthread_exit(NULL);
            return NULL;
        }
        thread++;
    }
    
    Directory* temp=dHead;
    char*directory= malloc(strlen(temp->in)+1);
    strcpy(directory,temp->in);
    deleteDirectory();
    pthread_mutex_unlock(&dLock);
    printf("Using Directory thread- %lu\n",pthread_self());
    struct dirent *dir;
    DIR *path=opendir(directory);
    while((dir=readdir(path))!=NULL){
        int len = strlen(dir->d_name);
        char *d=(char*)malloc(len*sizeof(char)+1);
        strcpy(d,dir->d_name);
        if( d[0] == '.'){
        }
        else{
            char* inN=(char*)malloc(len+strlen(directory)+10);
            int l=sizeof(inN);
            memset(inN, 0, l);
            strcat(inN, directory);
            if(directory[strlen(directory) - 1] != '/'){
                strcat(inN, "/");
            }
            strcat(inN, d);
            struct stat dirFile;
            stat (inN, &dirFile);
            if(S_ISDIR(dirFile.st_mode)){
                pthread_mutex_lock(&dLock);
                addDirectory(inN);
                pthread_cond_broadcast(&cond);
                pthread_mutex_unlock(&dLock);
            }
            else if(len > 5 && d[0] == 'w' && d[1] == 'r' && d[2] == 'a' && d[3] == 'p' && d[4] == '.' ){
            }
            else if (len > 4 && d[len - 4] == '.' && d[len - 3] == 't' && d[len - 2] == 'x' && d[len - 1] == 't' ){
                char* inN=(char*)malloc(len+strlen(directory)+10);
                int l=sizeof(inN); 
                memset(inN, 0, l);
                strcat(inN, directory);
                if(directory[strlen(directory) - 1] != '/'){
                    strcat(inN, "/");
                }
                strcat(inN, d);
                char* out=(char*)malloc(len+strlen(directory)+10);
                l=sizeof(inN);
                memset(out, 0, l);
                strcat(out, directory);
                if(directory[strlen(directory) - 1] != '/'){
                    strcat(out, "/");
                }
                strcat(out,"wrap.");
                strcat(out, d);
                pthread_mutex_lock(&fLock);
                addFile(inN, out);
                pthread_mutex_unlock(&fLock);
                free(out);
                free(inN);
            }
            free(inN);          
        }
        free(d);
    }
    closedir(path);
    free(directory);
    makeDl();
    return NULL;
}

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
        if(new == 1){
            strcat(temp," ");
        }
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

void* fileW(void* w){
    int* ww=(int*)w;
    int width=*ww;
    pthread_mutex_lock(&fLock);
    if(fHead==NULL){
        printf("    Quiting File thread- %lu\n",pthread_self());
        pthread_mutex_unlock(&fLock);
        pthread_exit(NULL);
        return NULL;
    }
    File* temp=fHead;
    char*in= malloc(strlen(temp->in)+1);
    char*out= malloc(strlen(temp->out)+1);
    strcpy(in,temp->in);
    strcpy(out,temp->out);
    deleteFile();
    pthread_mutex_unlock(&fLock);
    printf("Using File thread- %lu\n",pthread_self());
    int currentFile;
    int outFile;
    currentFile = open(in,O_RDONLY);
    outFile = open(out,O_WRONLY|O_CREAT|O_TRUNC,S_IRWXU|S_IRWXG|S_IRWXO);
    wrapper(currentFile, outFile, width);
    close(currentFile);
    close(outFile);
    free(in);
    free(out);
    fileW(w);
    return NULL;
}

void r(int width, int f, int d){
    pthread_t dIds[d];
    pthread_t fIds[f];
    for (int i = 0; i < d; i++){
        thread++;
        pthread_create(&dIds[i], NULL, makeDl, NULL);
    }
    for (int i = 0; i < d; i++){
        pthread_join(dIds[i], NULL);
    }
    for (int i = 0; i < f; i++){
        pthread_create(&fIds[i], NULL, fileW, &width);
    }
    for (int i = 0; i < f; i++){
        pthread_join(fIds[i], NULL);
    }
}

int main(int argc, char *argv[]){
    int width =  atoi(argv[2]);
    DIR *path;
    path = opendir(argv[3]);
    struct stat dirFile;
    int status = stat (argv[3], &dirFile);
    if(status != 0){
        closedir(path);
        perror("The Second Console Argument is INVALID Due to: \n  --Invaild Directory \n          OR \n  --File Doesn't Exist \n");
        exit(EXIT_FAILURE);
    }
    addDirectory(argv[3]);
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
    closedir(path);
    while (dHead != NULL) {
        deleteDirectory();
    }
    while (fHead != NULL) {
        deleteFile();
    }
}