#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<math.h>

#define Max 100

main()
{
	float seed;
	float psuedo;
	int k,print;
	while(1)
	{
		printf("\nPlease enter a valid seed value:\n\n");
		scanf("%f", &seed);
		printf("\nThe psuedo-random number is:\n");
		while(seed>1)
		{
			seed = seed / 10;
		}
		for(k=0; k<=10; k++)
		{
			psuedo = ((0.7423716721*seed)+0.3658612135);
			while(psuedo>1)
			{
				psuedo = psuedo / 10;
			}
			seed = psuedo;
			psuedo = psuedo * Max;
			print = (int) psuedo;
			printf("%d", print);
		}
	}
	return 0;
}
