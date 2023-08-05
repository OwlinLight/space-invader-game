/* author: Sitao Tong */
#include <stdio.h>
#include <stdlib.h>

#include "invaders.h"
#include "framerate.h"
#include "linkedlist.h"

typedef struct node{
    int data;
    struct node *next;
} Node;

void printIt(void* data){
    printf("data: %s\n", data);
}

int compare_y(void *x, void *y){
    int a = *(int *)x;
    int b = *(int *)y;
    return a < b;
}

int firstLetter(void *x, void *y){
    int a = *(char *)x;
    int b = *(char *)y;
    return a < b;
}


int StartWith(void *data, void *helper){
    return *(char*)data == 'a';
}

int StartWith1(void *data, void *helper){
    return *(char*)data == 'O';
}

int main(){

    char* list = NULL;
    int rval = 0;
    insert(&list, "GO Bucks!", firstLetter, 1);
    
    insert(&list, "OHIO!", firstLetter, 1);
    insert(&list, "Alaska!", firstLetter, 1);


    deleteSome(&list, StartWith, NULL, printIt, 1);

    rval = any(list, StartWith1, NULL);

    printf("rval: %d\n", rval);
    iterate(list, printIt);

    return 0;
}