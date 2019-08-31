#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

int relativecheck;
int rel_add_start;
int abs_add_start;
int n, len;
int alloc_hex;

boundcheck()
{
	printf("\nIs it relative address or absolute address (1 for relative and 0 for absolute)\n");
	scanf("%d", &relativecheck);
	if(relativecheck == 1)
	{
		printf("\nEnter the number of 32-bits you have been allocated (greater than or equal to 1):\n");
		scanf("%d", &n);
		printf("\nEnter the relative starting address for your operation:\n");
		scanf("%d", &rel_add_start);
		printf("\nEnter the number of 32-bits data you are processing\n");
		scanf("%d", &len);
		if(rel_add_start >= 1 && rel_add_start <= n)
		{
			if((rel_add_start+len-1) >= 1 && (rel_add_start+len-1) <= n)
			{
				printf("\nBoundary limits are MET SUCCESSFULLY\n");
			}
			else
			{
				printf("\nBoundary limits are VIOLATED\n");
			}
		}
		else
		{
			printf("\nBoundary limits are VIOLATED\n");
		}
	}
	else if(relativecheck == 0)
	{
		printf("\nEnter the number of 32-bits you have been allocated (greater than or equal to 1):\n");
		scanf("%d", &n);
		printf("\nEnter the starting address of your allocated 32-bits memory space in hex:\n");
		scanf("%x", &alloc_hex);
		printf("\nEnter the absolute starting address for your operation in hex:\n");
		scanf("%x", &abs_add_start);
		printf("\nEnter the number of 32-bits data you are processing\n");
		scanf("%d", &len);
		if(abs_add_start >= alloc_hex && abs_add_start <= alloc_hex)
		{
			if((abs_add_start+(4*len)-1) >= (alloc_hex+(4*n)-1) && (abs_add_start+(4*len)-1) <= (alloc_hex+(4*n)-1))
			{
				printf("\nBoundary limits are MET SUCCESSFULLY\n");
			}
			else
			{
				printf("\nBoundary limits are VIOLATED\n");
			}
		}
	}
}

main()
{
	while(1)
	{
	boundcheck();
	if (relativecheck == 1)
	{
		printf("\nrel_add_start: %d\t\t rel_add_start+len-1: %d\n", rel_add_start, rel_add_start+len-1);
	}
	if (relativecheck == 0)
	{
		printf("\nalloc_hex: %d\t\t abs_add_start: %d\t\t abs_add_start+(4*len)-1: %d\t\t alloc_hex+(4*n)-1: %d\n", alloc_hex, abs_add_start, abs_add_start+(4*len)-1, alloc_hex+(4*n)-1);
		printf("\nalloc_hex: %x\t\t abs_add_start: %x\t\t abs_add_start+(4*len)-1: %x\t\t alloc_hex+(4*n)-1: %x\n", alloc_hex, abs_add_start, abs_add_start+(4*len)-1, alloc_hex+(4*n)-1);
	}
	}
}
