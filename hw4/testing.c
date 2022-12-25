#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "mymalloc.h"

void printPtr(void* ptr, size_t size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d ", ((int*)ptr)[i]);
    }
    printf("\n");
}

int main(int argc, char **argv){
    // first fit testing
    // printf("First Fit Testing\n================\n");
    // myinit(0);
    // int *fa = mymalloc(100);
    // int *fb = mymalloc(100);
    // int *fc = mymalloc(100);
    // int *fd = mymalloc(100);
    // int *fe = mymalloc(100);
    // int *ff = mymalloc(100);
    // int *fg = mymalloc(100);
    // int *fh = mymalloc(100);
    
    // print();

    // myfree(fa);
    // myfree(fb);
    // myfree(fd);

    // print();

    // int *fi = mymalloc(100);

    // print();

    // myrealloc(fi, 200);

    // print();

    // for(int i = 0; i < 20; i++)
    // {
    //     fi[i] = i;
    // }

    // printPtr(fi, 20);

    // myrealloc(fi, 600);

    // print();

    // printPtr(fi, 20);

    // mycleanup();

    // // best fit testing
    // printf("\n\nBest Fit Testing\n================\n");
    // myinit(2);

    // int* ba = mymalloc(100);
    // int* bb = mymalloc(100);
    // int* bc = mymalloc(100);
    // int* bd = mymalloc(100);
    // int* be = mymalloc(100);
    // int* bf = mymalloc(100);
    // int* bg = mymalloc(100);
    // int* bh = mymalloc(100);
    
    // print();

    // myfree(ba);
    // myfree(bb);
    // myfree(bd);

    // print();

    // int* bi = mymalloc(100);

    // print();

    // myrealloc(bi, 200);

    // print();

    // for(int i = 0; i < 20; i++)
    // {
    //     bi[i] = i;
    // }

    // printPtr(bi, 20);

    // int* bj = mymalloc(100000);

    // print();

    // myrealloc(bj, 10);

    // print();

    // myrealloc(bj, 40);

    // print();

    // mycleanup();

    myinit(2);

    int size = 1000;
    int **pointer_list = malloc(sizeof(int*) * size);
    // create 1000 pointers of random size between 1 and 1000
    for(int i = 0; i < size; i++)
    {
        pointer_list[i] = mymalloc(rand() % 10000 + 1);
    }

    print();

    // for each of the thousand pointers, free a random number of them
    for(int i = 0; i < size; i++)
    {
        if(rand() % 2 == 0)
        {
            myfree(pointer_list[i]);
        }
    }

    print();

    for(int i = 0; i < size; i++)
    {
        pointer_list[i] = mymalloc(rand() % 100 + 1);
    }

    print();

    mycleanup();

    free(pointer_list);

    return 0;
}