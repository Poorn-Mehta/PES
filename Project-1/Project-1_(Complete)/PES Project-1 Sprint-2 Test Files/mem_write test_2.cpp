#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<math.h>

main()

{
	for (;;)
	{
		int t;
		long int data;
		int address;
		long int *str;
		str = (long int *)	malloc(30);
		printf("value = %x,  Address = %x\n", *str, str);
		long int *p;
		p = str;
		printf("Enter the data \n \n");
		scanf("%x", &data);
		*p = data;
		printf("Your value is \n ");
		printf("%x \n \n \n", *p);
		printf("To invert your values, type 0 for NO or 1 for YES \n \n \n");
		scanf("%d", &t);
		if (t == 1)
		{
			*p ^= 1;
			printf("Your inverted value is: %x \n \n", *p);
		}
		else
		{
			printf("You have chosen to terminate this program. Your unchanged value is: %x \n \n", *p);
		}
	}
}
