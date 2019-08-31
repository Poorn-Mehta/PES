// Program for Psuedo Random Numbers

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<math.h>

int main()
{
	while(1)
	{
		int i,t, a, k;
		int hd;
		long int smax;
		long int seed;
		long int address;
		long int *ptr;
		long int psuedo;
		int j;
		printf("Enter the number of 32-bit words you want to create: \n\n");
		scanf("%d", &a);
		j = 4*a;
		ptr = (long int *)	malloc(4*a);
		printf("\nYour allocated memory location begins at %x and the current value at that location is %x \n", ptr, *ptr);
		printf("\nThe list of memory locations with the relative addresses are as below:\n");
		for(i=1; i<=a; i++)
		{
			printf("Relative address: %d \t \t Data at the address: %x \t \t 8-bit Actual Address: %x\n", i, *(ptr+i-1), (ptr+i-1));
		}
		printf("\nEnter the maximum seed value you want to work with starting from 0:\n");
		scanf("%d", smax);
		if(smax>=4294967288)
		printf()
L0:		printf("If you want to enter your seed in decimal, type 0 and if you want to enter it in hexademical value, please type 1\n\n");
		scanf("%d", &hd );
		if(hd == 0)
		{
			printf("\nPlease enter a valid seed value in decimal between 0 and %d:\n\n", smax);
			scanf("%d", &seed);
			if(seed>=0 && seed<=smax)
			{
				psuedo = seed + 7;
				*ptr = psuedo;
				printf("\nThe psuedo-random number is %d\n", psuedo);
				printf("\nThe address of the 1st stored psuedo-random number is %x\n", ptr);
				if(a>1)
				{
					for(k=2; k<=a; k++)
					{
						psuedo = psuedo + 7;
						if(psuedo>=4294967296)
						{
							printf("\n Unfortunately, the expected outcome overflows the storage capacity. Please, enter a slightly reduced seed value.\n");
							goto L1;
						}
						*(ptr+k-1)= psuedo;
						printf("\nThe %dth psudeo-random number is %d\n", k, psuedo);
						printf("\nThe address of the %dth stored psuedo-random number is %x\n", k, (ptr+k-1));
					}
					printf("\n\n\n The psuedo-random number pattern is:\t\t\t");
					psuedo = seed + 7;
					printf("%d ", psuedo);
					for(k=2;k<=a;k++)
					{
						psuedo = psuedo + 7;
						printf("%d ", psuedo);
					}
					printf("\n\n\nThank you for using our services...\n\n\n\n\n");
				}
				else
				{
				printf("\nThank you for using our services...\n\n\n\n\n");
				}
			}
			else
			{
				printf("\nINVALID SEED\n");
				goto L0;
			}
		}
		if(hd == 1)
		{
			printf("\nPlease enter a valid seed value in decimal between 0 and 100:\n\n");
			scanf("%d", &seed);
			if(seed>=0 && seed<=100)
			{
				psuedo = seed + 7;
				*ptr = psuedo;
				printf("\nThe psuedo-random number is %d\n", psuedo);
				printf("\nThe address of the 1st stored psuedo-random number is %x\n", ptr);
				if(a>1)
				{
					for(k=2; k<=a; k++)
					{
						psuedo = psuedo + 7;
						if(psuedo>=4294967296)
						{
							printf("\n Unfortunately, the expected outcome overflows the storage capacity. Please, enter a slightly reduced seed value.\n");
							goto L1;
						}
						*(ptr+k-1)= psuedo;
						printf("\nThe %dth psudeo-random number is %d\n", k, psuedo);
						printf("\nThe address of the %dth stored psuedo-random number is %x\n", k, (ptr+k-1));
					}
					printf("\n\n\n The psuedo-random number pattern is:\t\t\t");
					psuedo = seed + 7;
					printf("%d ", psuedo);
					for(k=2;k<=a;k++)
					{
						psuedo = psuedo + 7;
						printf("%d ", psuedo);
					}
					printf("\n\n\nThank you for using our services...\n\n\n\n\n");
				}
				else
				{
				printf("\nThank you for using our services...\n\n\n\n\n");
				}
			}
			else
			{
				printf("\nINVALID SEED\n");
				goto L0;
			}
		}
		else
		{
			printf("\nINVALID SEED DATA TYPE ENTRY\n")
			goto L0;
		}
		
	}


/*	long int a, i;
	printf("Enter the number of 32-bit words of psuedo random number you want to create: \n");
	scanf("%d", a);
	long int *ptr;
	ptr = (long int *) malloc(4*a);
	printf("\nYour allocated memory location begins at %x and the current value at that location is %x \n", ptr, *ptr);
	printf("\n The list of memory locations with the relative addresses are as below:\n");
	for(i=0; i=psuedo_bytes; i++)
	{
		printf("Relative address: %d \t \t \t Actual Address: %x", i, (ptr+(i/4)));
	}
*/	return 0;
}
