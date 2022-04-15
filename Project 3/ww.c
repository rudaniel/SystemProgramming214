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


void filePrint() {
    File* node= fHead;
   	while (node!=NULL) {
        printf("    Elements in File List: %s , %s\n", node->in, node->out);
         node= node->next;
    }
}

void addFile(char* in, char* out){
    //pthread_mutex_lock(&fLock);
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
    //pthread_mutex_unlock(&fLock);
}

void deleteFile(){
    //pthread_mutex_lock(&fLock);
    if(fHead!=NULL){
        File* temp = fHead;
        fHead= fHead->next;
        free(temp->in);
        free(temp->out);
        free(temp);
    }
    //pthread_mutex_unlock(&fLock);
}

/*void makeFl(){
    Directory* node = dHead;
    while (node != NULL) {
        char* directory=malloc(strlen(node->in)+10);
        strcpy(directory, node->in);
        //printf("Current Dirct: %s\n", directory);
        struct dirent *dir;
        DIR *path=opendir(directory);
        while((dir=readdir(path))!=NULL){
            int len = strlen(dir->d_name);
            char *d=(char*)malloc(len*sizeof(char)+10);
            strcpy(d,dir->d_name);
            //printf("Name of Path: %s\n", d);
            if( d[0] == '.'){
            }
            else if(len > 5 &&
            d[0] == 'w' &&
            d[1] == 'r' &&
            d[2] == 'a' &&
            d[3] == 'p' &&
            d[4] == '.' ){
            }
            else if (len > 4                     &&
            d[len - 4] == '.' &&
            d[len - 3] == 't' &&
            d[len - 2] == 'x' &&
            d[len - 1] == 't' ){
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
                //printf("Name of File Path: %s\n", inN);
                //printf("Name of File Path: %s\n", out);
                addFile(inN, out);
                free(out);
                free(inN);
                
            }
            free(d);
        }
        //printf("%s %s\n", node->in,node->out);
        node = node->next;
        closedir(path);
        free(directory);
    }
}
*/
/*Directory queue*/

void dirPrint() {
    Directory* node= dHead;
   	while (node!=NULL) {
        printf("    Elements in Directory List: %s\n", node->in); //Printing list is not working? My be adding elements wrong?
        //printf("Start: %d\n", start);
        //start++;
        node = node->next;
    }
}

void addDirectory(char* in){
    //pthread_mutex_lock(&dLock);
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
    //pthread_mutex_unlock(&dLock);
}

void deleteDirectory(){
    //pthread_mutex_lock(&dLock);
    if(dHead!=NULL){
        Directory* temp = dHead;
        dHead= dHead->next;
        free(temp->in);
        free(temp);
    }
    //pthread_mutex_unlock(&dLock);
}

void* makeDl(){
    //int infiniteLoop = 0;
    pthread_mutex_lock(&dLock);
    if(dHead==NULL){
        printf("    Quiting Directory thread- %lu\n",pthread_self());
        pthread_mutex_unlock(&dLock);
        return NULL;
    }
    Directory* temp=dHead;
    char*directory= malloc(strlen(temp->in)+1);
    strcpy(directory,temp->in);
    deleteDirectory();
    pthread_mutex_unlock(&dLock);
    printf("Using Directory thread- %lu\n",pthread_self());
    //printf("rere: %s\n",directory);
    //deleteDirectory();
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
                pthread_mutex_unlock(&dLock);
                //printf("added: %s\n",node->in);
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
                //printf("Name of File Path: %s\n", inN);
                //printf("Name of File Path: %s\n", out);
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

/*typedef struct dQueue {
    directory *front;
    directory *end;
    int size;
    pthread_mutex_t lock;
    pthread_cond_t enqueue_ready, dequeue_ready;
} dQueue;

int queue_init(dQueue *q)
{
    q->front = NULL;
    q->end = NULL;
    q->size = 0;
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->enqueue_ready, NULL);
    pthread_cond_init(&q->dequeue_ready, NULL);
    return 0;
}

int enqueue(int n, dQueue *q)
{
    pthread_mutex_lock(&q->lock);
    while (q->full) {
        pthread_cond_wait(&q->enqueue_ready, &q->lock);
    }
    q->data[q->stop] = n;
    q->stop++;
    if (q->stop == QUEUESIZE) q->stop = 0;
    if (q->start == q->stop) q->full = 1;
    pthread_cond_signal(&q->dequeue_ready);
    pthread_mutex_unlock(&q->lock);
    return 0;
}

int dequeue(int *n, dQueue *q)
{
    pthread_mutex_lock(&q->lock);
    while (!q->full && q->start == q->stop) {
        pthread_cond_wait(&q->dequeue_ready, &q->lock);
    }
    * n = q->data[q->start];
    q->start++;
    if (q->start == QUEUESIZE) q->start == 0;
    q->full = 0;
    pthread_signal(&q->enqueue_ready);
    pthread_mutex_unlock(&q->lock);
    return 0;
}
*/
/*
*
*
*END OF DIRECTORY QUEUE CODE
*
*
*/

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
    int width=(int)w;
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
    pthread_t ids[f+d];
    int c=0;
    //pthread_t id;
    /*for (int i = 0; i < d; i++){
        //printf("added thread %d...\n",i);
        pthread_create(&ids[c], NULL, makeDl, NULL);
        c++;
    }*/
    for (int i = 0; i < f; i++){
        //printf("added thread %d...\n",i);
        pthread_create(&ids[c], NULL, fileW, (void*)width);
        c++;
    }
    /*for (int i = 0; i < (f+d); i++){
       //pthread_join(ids[i], NULL);
    }*/
   // pthread_exit(NULL);
}

int main(int argc, char *argv[]){
   /* if(argc<1){
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
    }*/

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
    makeDl();
    char* f=malloc(strlen(argv[1])+1);
    strcpy(f,argv[1]);
    int length=strlen(f);
    int count=0;
    char* token = strtok(f, ",");
    while (token) {
        //printf("token: %s\n", token);
        token = strtok(NULL, ",");
        count++;
    }
    free(f);
    f=malloc(strlen(argv[1])+1);
    strcpy(f,argv[1]);
    //printf("Count: %d\n",count);
    if(strcmp(f,"-r")==0){
        printf("    Regular\n\n");
        r(width,1,1);
    }
    else if(count==1&&f[0]=='-'&&f[1]=='r'&& length>2){
        char* num= malloc(length+1);
        //memset(num,0,strlen(num));
        memcpy(num,&f[2],(length-2));
        int threads=atoi(num);
        free(num);
        free(f);
        printf("    Using %d Threads\n\n",threads);
        r(width,threads,1);
    }
    else{
        //printf("    Gotta Blast %s\n\n",f);
        //printf("B======================================D\n");
        char* tok = strtok(f, ",");
        count=0;
        char* temp;
        int t2;
        while (tok) {
            //printf("token: %s\n", tok);
            if(count==0){
                temp= malloc(strlen(tok)+1);
                strcpy(temp,tok);
            }
            else if(count==1){
                t2=atoi(tok);
                //printf("tt %d\n",t2);
            }
            count++;
            tok = strtok(NULL, ",");
        }
        char num[(length-1)];
        memcpy(num,&temp[2],(length-2));
        int threads=atoi(num);
        free(f);
        free(temp);
        printf("    Using %d Threads for Files and %d Threads for Directories.\n\n",threads,t2);
        r(width,threads,t2);
    }
    closedir(path);
    /*
    addDirectory("foo");
    makeDl();
   // makeFl();
    dirPrint();
    filePrint();
*/
    //wipe directory
    //printf("dddddddd\n");
    //dirPrint();
    while (dHead != NULL) {
        deleteDirectory();
    }
    while (fHead != NULL) {
        deleteFile();
    }
    
pthread_exit(NULL);
   /* makeFl();
    File* node = fHead;
    while (node != NULL) {
        printf("%s %s\n", node->in,node->out);
        node = node->next;
    }
    printf("\n\n");
    deleteFile();
    node = fHead;
    while (node != NULL) {
        printf("%s %s\n", node->in,node->out);
        node = node->next;
    }
    node = fHead;
    for(int i=10; i>0;i--) {
        deleteFile();
    }
printf("new lsit\n");
    node = fHead;
    while (node != NULL) {
        printf("%s %s\n", node->in,node->out);
        node = node->next;
    }
    printf("\n\n");*/
}