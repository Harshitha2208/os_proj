#include <stdio.h>
#include "filehandle.h"
int main(){
    int choice;
   while(choice>0){
     printf("enter choice for menu :\n");
   scanf("%d",&choice);
    switch(choice){
        case 1:filecrud();break;
        default: printf("chioce out of scope\n");
    }
   }
}