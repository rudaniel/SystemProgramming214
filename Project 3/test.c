#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "wordwrap.h"
#include <time.h>


int main(int argc, char**argv){
    srand(time(0));
    clock_t beginnn = clock();
    char* in= "test1.txt";
    char* out= "wrap.test1.txt";
    addFile(in, out);
    assert(fHead->in = "test1.txt");
    assert(fHead->out = "wrap.test1.txt");
    filePrint();
    deleteFile();
    filePrint(); //Here we tested adding and deleting to the file linked list.
    printf("\n");
    clock_t enddd = clock();
    double time_spenttt = (double)(enddd - beginnn) / CLOCKS_PER_SEC;
    printf("Total Time Taken for Test Case 1:  %f\n", time_spenttt); //CPU time used in seconds.

    clock_t beginn = clock();
    char* inn= "foo";
    addDirectory(inn);
    assert(dHead->in = "foo");
    dirPrint();
    deleteDirectory();
    dirPrint(); //Here we tested adding and deleting to the directory linked list.
    printf("\n");
    clock_t endd = clock();
    double time_spentt = (double)(endd - beginn) / CLOCKS_PER_SEC;
    printf("Total Time Taken for Test Case 2:  %f\n", time_spentt); //CPU time used in seconds.


    clock_t begin = clock();

    addDirectory(inn); //We will not be testing when giving a directory if both linked list will be filled properly
    fCount=0;
    dCount=0;
    dCount++;
    int rec=1;
    makeDl(&rec);
    printf("Number of Directories: %d\n", dCount);
    filePrint(); 
    printf("\n");
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Total Time Taken for Test Case 3:  %f\n", time_spent); //CPU time used in seconds.

    clock_t begin2 = clock();
    addDirectory(inn);
    fCount=0;
    dCount=0;
    dCount++;
    r(20,2,1); //testing multiple treads reading the file linked list and wrapping.
    printf("Number of Directories: %d\n", dCount);
    filePrint(); 
    printf("\n");
    clock_t end2 = clock();
    double time_spent2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
    printf("Total Time Taken for Test Case 4:  %f\n", time_spent2); //CPU time used in seconds.

    clock_t begin3 = clock();
    addDirectory(inn);
    fCount=0;
    dCount=0;
    dCount++;
    r(20,2,4); //testing multiple treads both wrapping and reading from directory.
    printf("Number of Directories: %d\n", dCount);
    filePrint(); 
    printf("\n");
    clock_t end3 = clock();
    double time_spent3 = (double)(end3 - begin3) / CLOCKS_PER_SEC;
    printf("Total Time Taken for Test Case 5:  %f\n", time_spent3); //CPU time used in seconds.

    clock_t begin4 = clock();
    addDirectory(inn);
    fCount=0;
    dCount=0;
    dCount++;
    r(20,4,6); //increased number of treads to make sure code is working at faster pace when more treads are added.
    printf("Number of Directories: %d\n", dCount);
    filePrint(); 
    printf("\n");
    clock_t end4 = clock();
    double time_spent4 = (double)(end4 - begin4) / CLOCKS_PER_SEC;
    printf("Total Time Taken for Test Case 6:  %f\n", time_spent4); //CPU time used in seconds.

    clock_t begin5 = clock();
    addDirectory(inn);
    fCount=0;
    dCount=0;
    dCount++;
    r(20,10,1); //here im testing just an increase of file treads no increase in direc treads.
    printf("Number of Directories: %d\n", dCount);
    filePrint(); 
    printf("\n");
    clock_t end5 = clock();
    double time_spent5 = (double)(end5 - begin5) / CLOCKS_PER_SEC;
    printf("Total Time Taken for Test Case 7:  %f\n", time_spent5); //CPU time used in seconds.

    //From these test cases we see that test case 5 is faster then test case 4 which is logical due to more treads working on both wrapping and reading.
    //test case 3 seems to be working the fastest but thats because we only test the filling of the file linked list. wrapping time is not calcualted in that test case.
    //in testcase 6 we proved that more treads added faster time!
    //These test cases test our functionaility. If errors occur its due to user error.
    

}