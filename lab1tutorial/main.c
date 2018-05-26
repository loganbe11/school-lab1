#include <stdio.h>
#include <stdlib.h>
#include "LinkedListAPI.h"
#include "main.h"
int main()
{
  //create a List
 List *list = initializeList(printInt,&free,compareIntFunction);

 //create some test integers
 int one   = 1;
 int two   = 2;
 int three = 3;
 int four  = 4;
 int five  = 5;

 insertBack(list,(void* )one);
 insertBack(list,(void* ) 2);
 insertBack(list,(void* ) 4);
 insertBack(list,(void* ) 5);

 printf("\nprint list forwards:\n");
 printForward(list);

 printf("\nprint list backwards:\n");
 printBackwards(list);


 printf("\nprint list forwards:\n");
 printForward(list);

 printf("\n");
 insertSorted(list,3);
 printForward(list);
 printf("%d\n",getFromFront(list));
 printf("%d",getFromBack(list));
 deleteList(list);
 printf("%d",list);
}
void printInt(void *toBePrinted){
printf("%d \n",toBePrinted);
}
int compareIntFunction(const void *first,const void *second){
if(first==second){
    return 0;
}
else if(first>second){
    return 1;
}
return -1;
}

