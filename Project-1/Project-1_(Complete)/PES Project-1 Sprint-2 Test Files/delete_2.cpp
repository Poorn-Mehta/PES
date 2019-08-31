#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main()
{
	int a;
	int *p;
    printf("Enter your address \n");
    scanf("%x", &a);
    *p = a;	
    printf("the data at the specified memory location is %x", p);
    return 0;
}
