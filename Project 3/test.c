#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "wordwrap.h"

int main(int argc, char**argv){
    srand(time(0));
    clock_t beginnn = clock();
    char* in= "test1.txt";
    char* out= "wrap.test1.txt";
    addFile(in, out);
    printf("\n");
    printf("Testing Adding File...\n");
    assert(strcmp(fHead->in,"test1.txt")==0);
    assert(strcmp(fHead->out,"wrap.test1.txt")==0);
    deleteFile();
    clock_t enddd = clock();
    double time_spenttt = (double)(enddd - beginnn) / CLOCKS_PER_SEC;
    printf("Total Time Taken for Test Case 1:  %f\n", time_spenttt); //CPU time used in seconds.
    printf("\n");

    clock_t beginn = clock();
    char* inn= "foo";
    addDirectory(inn);
    printf("Testing Adding Directory...\n");
    assert(strcmp(dHead->in,"foo")==0);
    deleteDirectory();
    //Here we tested adding and deleting to the directory linked list.
    clock_t endd = clock();
    double time_spentt = (double)(endd - beginn) / CLOCKS_PER_SEC;
    printf("Total Time Taken for Test Case 2:  %f\n", time_spentt); //CPU time used in seconds.
    printf("\n");

    clock_t begin = clock();

    addDirectory(inn); //We will not be testing when giving a directory if both linked list will be filled properly
    fCount=0;
    dCount=0;
    dCount++;
    int rec=1;
    printf("Testing All Files Show up in File Linked List through recursive directory traversal...\n");
    makeDl(&rec);
    assert(fCount==7);
    printf("Number of Directories: %d\n", dCount);
    printf("Number of Files: %d\n", fCount); 
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Total Time Taken for Test Case 3:  %f\n", time_spent); //CPU time used in seconds.
    printf("\n");

    clock_t begin2 = clock();
    addDirectory(inn);
    fCount=0;
    dCount=0;
    dCount++;
    printf("Testing Single threaded file wrapper...\n");
    r(50,1,1);
    assert(fCount==7);
    assert(dCount==9);
    printf("Number of Directories: %d\n", dCount);
    printf("Number of Files: %d\n", fCount); 
    clock_t end2 = clock();
    double time_spent2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
    printf("Total Time Taken for Test Case 4:  %f\n", time_spent2); //CPU time used in seconds.
    printf("\n");

    clock_t begin3 = clock();
    addDirectory(inn);
    fCount=0;
    dCount=0;
    dCount++;
    printf("Testing Multi-Threaded threaded file wrapper...\n");
    r(50,3,4); //testing multiple treads both wrapping and reading from directory.
    assert(fCount==7);
    assert(dCount==9);
    printf("Number of Directories: %d\n", dCount);
    printf("Number of Files: %d\n", fCount); 
    clock_t end3 = clock();
    double time_spent3 = (double)(end3 - begin3) / CLOCKS_PER_SEC;
    printf("Total Time Taken for Test Case 5:  %f\n", time_spent3); //CPU time used in seconds.
    printf("\n");

    clock_t begin4 = clock();
    addDirectory(inn);
    fCount=0;
    dCount=0;
    dCount++;
    printf("Testing Increased threaded file wrapper...\n");
    r(50,6,7); //increased number of treads to make sure code is working at faster pace when more treads are added.
    assert(fCount==7);
    assert(dCount==9);
    printf("Number of Directories: %d\n", dCount);
    printf("Number of Files: %d\n", fCount); 
    clock_t end4 = clock();
    double time_spent4 = (double)(end4 - begin4) / CLOCKS_PER_SEC;
    printf("Total Time Taken for Test Case 6:  %f\n", time_spent4); //CPU time used in seconds.
    printf("\n");

    clock_t begin5 = clock();
    addDirectory(inn);
    fCount=0;
    dCount=0;
    dCount++;
    printf("Testing Increased threaded file wrapper...\n");
    r(50,12,14); 
    assert(fCount==7);
    assert(dCount==9);
    printf("Number of Directories: %d\n", dCount); 
    printf("Number of Files: %d\n", fCount); 
    clock_t end5 = clock();
    double time_spent5 = (double)(end5 - begin5) / CLOCKS_PER_SEC;
    printf("Total Time Taken for Test Case 7:  %f\n", time_spent5); //CPU time used in seconds.
    printf("\n");
    //From these test cases we see that test case 5 is faster then test case 4 which is logical due to more treads working on both wrapping and reading.
    //test case 3 seems to be working the fastest but thats because we only test the filling of the file linked list. wrapping time is not calcualted in that test case.
    //in testcase 6 we proved that more treads added faster time!
    //These test cases test our functionaility. If errors occur its due to user error. Downward average trend.
}