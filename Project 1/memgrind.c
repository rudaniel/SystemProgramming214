#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mymalloc.h"



int main(int argc, char**argv){
  // char* p= malloc(10);

  // for (int i = 0; i<10; i++){
  //    p[i] = 'a';
  //  }


  // char* pp = malloc(5);

  //    for (int i = 0; i<5; i++){
  //    pp[i] = 'b';
  //  }

  // char* ppp = malloc(15);

  //   for (int i = 0; i<15; i++){
  //    ppp[i] = 'c';
  //  }

  // free(pp);

  // char* qq = malloc(3);

  //   for (int i = 0; i<3; i++){
  //    qq[i] = 'd';
  //  }

  // char* qqq = malloc(10);
//   for (int i = 0; i<10; i++){
//     p[i] = 'a';
//   }
//     //free(p);
//   char* pp= malloc(15);

//   for (int i = 0; i<15; i++){
//     pp[i] = 'b';
//   }
//  free(p);
//  // int *q =malloc(0);
// char* pdfp= malloc(20);
//  for (int i = 0; i<20; i++){
//     pdfp[i] = 'c';
//   }
//   char* pdsdffp= malloc(10);

// for (int i = 0; i<10; i++){
//     printf("Array p %c\n",p[i]);
// }

// for (int i = 0; i<15; i++){
//    printf("Array pp %c\n",pp[i]);
// }
// for (int i = 0; i<20; i++){
//      printf("Array pdfp %c\n",pdfp[i]);
// }
  
 // int* q= malloc(10);


//int* pp= malloc(25);



//int* ppp= malloc(5);

//int* breaker= malloc(4021);



  //   int *p = malloc(10);

  //   for(int i = 0; i <10; i++){
  //       p[i] = i;
  //   }

  //   int *q = malloc(10);
    
  // //  for(int i = 0; i <1024; i++){
  // //        printf( "%d: \n", p[i]);
  // //  }
  //   free(p); 
  //   // gcc memgrind.c mymalloc.c -o test
  //   // ./filename

  //int p1;
  //free(&p1);
  free(NULL);
  char * q = malloc(4000);
  for (int i =0; i < 4000; i++){
    q[i] = 'a';
  }
  // char * t = malloc(1);
  free(q+1);
  //free(q);
    return EXIT_SUCCESS;
}