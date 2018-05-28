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

 insertSorted(list,four);
 insertSorted(list,two);
 insertSorted(list,four);
 insertSorted(list,three);
 insertSorted(list,five);

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
printf("\n Comparing %d and %d",first, second);
if(first==second){
    printf("\n 0:equal");
    return 0;
}
else if(first>second){
    printf("\n 1:first greater");
    return 1;
}
printf("\n -1:second greater");
return -1;
}

