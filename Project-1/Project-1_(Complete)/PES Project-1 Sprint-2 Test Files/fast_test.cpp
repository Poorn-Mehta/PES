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
		int seed;
		long int address;
		long int *ptr;
		float psuedo;
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
		printf("\nPlease enter a valid seed value in decimal:\n\n");
		scanf("%f", &seed);
		while(seed>1)
				{
					seed /= 10;
				}
//		if(seed>=0 && seed<=100)
				for(k=0; k=15; k++)
				{
					psuedo = ((0.2165464567*seed)+0.4658612135);
					while(psuedo>1)
					{
						psuedo /= 10;
					}
					*ptr = psuedo;
					printf("\nThe psuedo-random number is %f\n", psuedo);
					seed = psuedo;
				}
	}
}
/*				printf("\nThe address of the 1st stored psuedo-random number is %x\n", ptr);
				if(a>1)
/*				{
					for(k=2; k<=a; k++)
					{
						psuedo = ((2*psuedo)+3)%4;
						if(psuedo>=4294967296)
						{
							printf("\n Unfortunately, the expected outcome overflows the storage capacity. Please, enter a slightly reduced seed value.\n");
							goto L0;
						}
						*(ptr+k-1)= psuedo;
						printf("\nThe %dth psudeo-random number is %d\n", k, psuedo);
						printf("\nThe address of the %dth stored psuedo-random number is %x\n", k, (ptr+k-1));
					}
					printf("\n\n\n The psuedo-random number pattern is:\t");
					psuedo = (((2*seed)+3)%4);
					printf("%d ", psuedo);
					for(k=2;k<=a;k++)
					{
						psuedo = (((2*psuedo)+3)%4);
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
}
*/
