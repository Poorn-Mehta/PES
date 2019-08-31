#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<math.h>

main()

{
	for (;;)
	{
		long data;
		int address;
		long int *str;
		str = (long int *)	malloc(100);
		printf("value = %u,  Address = %x\n", str, str);
		long int *p;
		p = str;
		printf("Enter the data \n \n");
		scanf("%ud", &data);
		*p = data;
		printf("Data: %u \t \t Address: %x\n\n\n\n", *p, p);
	}
}
