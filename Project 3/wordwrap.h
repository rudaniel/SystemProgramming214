typedef struct File{
    char* in;
    char* out;    
    struct File *next;
} File;

typedef struct Directory{
    char* in; 
    struct Directory *next;
} Directory;

extern File* fHead;
extern Directory* dHead;

extern int fCount;
extern int dCount;

void addFile(char* in, char* out);
void deleteFile();
void addDirectory(char* in);
void deleteDirectory();
void* makeDl(void* r);
void wrapper(int in, int out,int userWidth);
void* fileW(void* w);
void r(int width, int f, int d);
int main(int argc, char *argv[]);