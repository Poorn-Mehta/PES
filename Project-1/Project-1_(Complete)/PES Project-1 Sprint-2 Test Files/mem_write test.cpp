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
		str = (long int *)	malloc(30);
		printf("value = %s,  Address = %u\n", str, str);
		long int *p;
		p = str;
		printf("Enter the data \n \n");
		scanf("%x", &data);
		*p = data;
		printf("%d", *p);
	}
}
