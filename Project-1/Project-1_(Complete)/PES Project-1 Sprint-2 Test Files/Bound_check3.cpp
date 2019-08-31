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
int total;
int total_2;
int error_flag2;
int random_flag;

boundcheck()
{
	printf("\nIs it a psuedo-random number operation? 1 for Yes and 0 for No\n");
	scanf("%d", &random_flag);
	if(random_flag == 1)
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
					error_flag2 = 0;
				}
				else
				{
					printf("\nBoundary limits are VIOLATED\n");
					error_flag2 = 1;
				}
			}
			else
			{
				printf("\nBoundary limits are VIOLATED\n");
				error_flag2 = 1;
			}
		}
		else 
		{
			printf("\nEnter the number of 32-bits you have been allocated (greater than or equal to 1):\n");
			scanf("%d", &n);
			printf("\nEnter the starting address of your allocated 32-bits memory space in hex:\n");
			scanf("%x", &alloc_hex);
			printf("\nEnter the absolute starting address for your operation in hex:\n");
			scanf("%x", &abs_add_start);
			printf("\nEnter the number of 32-bits data you are processing\n");
			scanf("%d", &len);
			total = abs_add_start - alloc_hex;
			total_2 = (alloc_hex + (4*n) - 1) - (abs_add_start+(4*len)-1);
			if(total >= 0)
			{
				if(total >= 0) 
				{
					printf("\nBoundary limits are MET SUCCESSFULLY\n");
					error_flag2 = 0;
				}
				else
				{
					printf("\nBoundary limits are VIOLATED\n");
					error_flag2 = 1;
				}
			}
			else
			{
				printf("\nBoundary limits are VIOLATED\n");
				error_flag2 = 1;
			}
		}
	}
	else if (random_flag == 0)
	{
		printf("\nIs it relative address or absolute address (1 for relative and 0 for absolute)\n");
		scanf("%d", &relativecheck);
		if(relativecheck == 1)
		{
			printf("\nEnter the number of 32-bits you have been allocated (greater than or equal to 1):\n");
			scanf("%d", &n);
			printf("\nEnter the relative starting address for your operation:\n");
			scanf("%d", &rel_add_start);
			len = 1;
			if(rel_add_start >= 1 && rel_add_start <= n)
			{
				if((rel_add_start+len-1) >= 1 && (rel_add_start+len-1) <= n)
				{
					printf("\nBoundary limits are MET SUCCESSFULLY\n");
					error_flag2 = 0;
				}
				else
				{
					printf("\nBoundary limits are VIOLATED\n");
					error_flag2 = 1;
				}
			}
			else
			{
				printf("\nBoundary limits are VIOLATED\n");
				error_flag2 = 1;
			}
		}
		else 
		{
			printf("\nEnter the number of 32-bits you have been allocated (greater than or equal to 1):\n");
			scanf("%d", &n);
			printf("\nEnter the starting address of your allocated 32-bits memory space in hex:\n");
			scanf("%x", &alloc_hex);
			printf("\nEnter the absolute starting address for your operation in hex:\n");
			scanf("%x", &abs_add_start);
			len = 1;
			total = abs_add_start - alloc_hex;
			total_2 = (alloc_hex + (4*n) - 1) - (abs_add_start+(4*len)-1);
			if(total >= 0)
			{
				if(total >= 0) 
				{
					printf("\nBoundary limits are MET SUCCESSFULLY\n");
					error_flag2 = 0;
				}
				else
				{
					printf("\nBoundary limits are VIOLATED\n");
					error_flag2 = 1;
				}
			}
			else
			{
				printf("\nBoundary limits are VIOLATED\n");
				error_flag2 = 1;
			}
		}
	}
}

main()
{
	while(1)
	{
		boundcheck();
		printf("\nerror_flag2 = %d\n", error_flag2);
		if (relativecheck == 1)
		{
			printf("\nrel_add_start: %d\t\t rel_add_end: %d\n", rel_add_start, rel_add_start+len-1);
			printf("\nalloc_add_start: %d\t\t alloc_add_end: %d\n", 1, n);
		}
		if (relativecheck == 0)
		{
			printf("\nalloc_hex: %d\t\t abs_add_start: %d\t\t abs_add_end: %d\t\t alloc_hex_end: %d\n", alloc_hex, abs_add_start, abs_add_start+(4*len)-1, alloc_hex+(4*n)-1);
			printf("\nalloc_hex: %x\t\t abs_add_start: %x\t\t abs_add_end: %x\t\t alloc_hex_end: %x\n", alloc_hex, abs_add_start, abs_add_start+(4*len)-1, alloc_hex+(4*n)-1);
		}
	}
}
