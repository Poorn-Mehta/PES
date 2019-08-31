#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<math.h>

int main()
{
	int a;
	int *str;
	int *p;
	printf("Enter the number of 32 bits you want to be allocated");
	scanf("%d", &a);
	str = (int *)	malloc(4*a);
 	printf("The allocated address range is from %x to %x", str, (str+a));
    printf("Enter your address you want to read: \n");
    scanf("%x", &p);	
    printf("the data at the specified memory location is %x and the address is %x", *p, p);
    return 0;
}
