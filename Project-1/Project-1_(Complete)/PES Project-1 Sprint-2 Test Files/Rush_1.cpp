#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include<string.h>

main()
{
	int n;
	printf("Enter the number of 32 bit words (4 bytes) you wish to enter (remember that one character is worth one byte): \n \n");
	scanf("%d", &n);
	char c[n];
	printf("Enter that string now \n \n");
	scanf("%(n-1)s", &c);
	printf("Storage size of the strings you just entered: %d \n", sizeof(c) );
	return 0;
}
