#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

int address, address_1, address_2; // addresses required for the functionalities
float seed; // seed value entry for generating a psuedo-random number
int data; // potential data to be written
int n; // number of 32-bit address that needs to be entered anywhere in this file
int n_2; // number of 32-bit address that needs to be entered anywhere in this file
int i; // Loop counter
int k; // extra loop counter
int t; // test integer
int *ptr, *ptr_2; //Pointer for memory operations
char c; //testing char for the Switch Case in the main function
int test; // testing if the user wishes to store the psuedo-random number pattern
float random; // psuedo-gen variable for generating a psuedo-random number
int print, tmp;	// Printer and temporary counter for the psuedo-random number pattern

// ptr = 0;
// *ptr = 0;

//functions:

void memalloc(void);
void memfree(void);

void memalloc(void)
{
	printf("\nPlease, enter the number of 32-bit locations that you wish to be allocated to you:\n");
	scanf("%d", &n);
	ptr = (int *) malloc (4*n);
//	ptrclr();
	printf("\nThe allocated addresses are as below:\n");
	for(i=1; i<=n; i++)
	{
		printf("\nRelative address: %d \t\t Actual address: %x \t\t Existing hex data at this location in Hex: %x", i, (ptr+i-1), *(ptr+i-1));
	}
	printf("\n\nThanks for executing the memory allocation operation...\n");	
}

// 2. Memory Freeing									: memfree()

void memfree(void)
{
	if(ptr==0)
	{
		printf("\nUnfortunately, you have not been allocated any memory so far and so no memory was freed...\n");
	}
	else
	{
		free(ptr);
		printf("\nThe allocated memory has been successfully freed...\n");
		printf("\nThanks for freeing the allocated memory...\n");
	}
}

main()
{
	while(1)
	{
		memalloc;
		memfree;
	}
}
