// This is the C file containing all the PES Project-1 Functionalities

// Please note: All data handling is done in 32-bits. It has been established that the pointer jumps by 4-bytes (32-bits) for every single increment while every single memory location stores upto 8 bits.

/* This file contains the below given functions with the function names as mentioned below:
	1. Memory Allocation							: memalloc(number of 32-bit words) ; allocates the specified number of 4 pairs of 8-bit storage locations (32-bit locations)
	2. Memory Freeing								: memfree(void) ; will free the allocated memory and if the memory is not allocated then it will generate a warning sign
	3. Memory Read									: memread(address) ; will read only upto first 32-bits (one word) beginning from the specified 8-bit memory location
	4. Memory Write									: memwrite(address) ; will write only upto first 32-bits (one word) beginning from the specified 8-bit memory location
	5. Memory Data XORing							: memxor(address) ; will XOR the 32-bit data stored at the 8-bit memory locations beginning with the 8-bit memory location that is specified
	6. Psuedo-random number generator				: psuedogen(seed, n, address) ; simply generates the psuedo code for n times using the seed value and forms a pattern and stores it with the specified 8-bit memory address for the entire 32-bit psuedo code (which occupies 4 memory locations)
	7. Psuedo-random number verification			: psuedover(n, address) ; simply verifies the psuedo code for n 32-bit storage beginning at the specified 8-bit location
	8. Random memory compare/read test				: memtest(address_1, address_2) ; delivers 1 if the 32-bit storage beginning at location address_1 is exactly as the one stored beginning at address_2 and otherwise will be 0
	9. Time measurement for any operation			: timetest(L1,L2); specifies the time taken by the code to execute the lines between the labels L1 and L2
*/

//Libraries

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

// Global Constants

#define MAX 100000

//Global Variables

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

// ptr = 0;
// *ptr = 0;

int memalloc(int n);
void memfree(void);
int memread(int address);
int memwrite(int address);
int memxor(int address);
float psuedogen(float seed, int n, int address);
//psuedover(n, address);
//memtest(address_1, address_2);
//timetest(L1,L2);

// 1. Memory Allocation	Function						: memalloc(number of 32-bit words)

int memalloc(int n)
{
	printf("\nPlease, enter the number of 32-bit locations that you wish to be allocated to you:\n");
	scanf("%d", &n);
	ptr = (int *) malloc (4*n);
	printf("\nThe allocated addresses are as below:\n");
	for(i=1; i<=n; i++)
	{
		printf("\nRelative address: %d \t\t Actual address: %x \t\t Existing hex data at this location in Hex: %x", i, (ptr+i-1), *(ptr+i-1));
	}
	printf("\n\nThanks for executing the memory allocation operation...\n");	
}

// 2. Memory Freeing									: memfree(void)

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

// 3. Memory Read										: memread(address)

int memread(int address)
{
	if(ptr==0)
	{
		printf("\nUnfortunately, you have not been allocated any memory so far and so no memory can be read...\n");
	}
	else
	{
		printf("\nThe allocated addresses are as below:\n");
		for(i=1; i<=n; i++)
		{
		printf("\nRelative address: %d \t\t Actual address: %x \t\t Existing hex data at this location in Hex: %x", i, (ptr+i-1), *(ptr+i-1));
		}
		printf("\nEnter the hex address from the allocated set of addresses for which you wish to read the data:\n");
		scanf("%x",&ptr_2);
		printf("\nThe hex data at the specified location (%x) is %x", ptr_2, *ptr_2);
		printf("\nThanks for reading from an allocated memory location...\n");
	}
}

// 4. Memory Write										: memwrite(address)

int memwrite(int address)
{
	if(ptr==0)
	{
		printf("\nUnfortunately, you have not been allocated any memory so far and so no memory write cannot be done...\n");
	}
	else
	{
		printf("\nThe allocated addresses are as below:\n");
		for(i=1; i<=n; i++)
		{
		printf("\nRelative address: %d \t\t Actual address: %x \t\t Existing hex data at this location in Hex: %x", i, (ptr+i-1), *(ptr+i-1));
		}
		printf("\nEnter the hex address from the allocated set of addresses at which you wish to write the data:\n");
		scanf("%x",&ptr_2);
		printf("\nEnter the hex data that you wish to write to the specified memory location:\n");
		scanf("%x",&data);
		*ptr_2 = data;
		printf("\nThe hex data at the specified location (%x) is %x", ptr_2, *ptr_2);
		printf("\nThanks for writing to an allocated memory location...\n");
	}
}

// 5. Memory Data XORing								: memxor(address)

int memxor(int address)
{
	if(ptr==0)
	{
		printf("\nUnfortunately, you have not been allocated any memory so far and so XORing is not possible at this moment...\n");
	}
	else
	{
		printf("\nThe allocated addresses are as below:\n");
		for(i=1; i<=n; i++)
		{
		printf("\nRelative address: %d \t\t Actual address: %x \t\t Existing hex data at this location in Hex: %x", i, (ptr+i-1), *(ptr+i-1));
		}
		printf("\nEnter the hex address from the allocated set of addresses at which you wish to perform an XOR operation:\n");
		scanf("%x",&ptr_2);
		printf("\nThe data in hex at the specified memory location BEFORE XORing is %x\n", *ptr_2);
		{ 
    		// Calculate the time taken by fun() 
    		clock_t t; 
    		t = clock(); 
			*ptr_2 ^= 1;
    		t = clock() - t; 
    		double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
			printf("\nInversion took %f seconds to execute \n", time_taken); 
 		}
		printf("\nThe data in hex at the specified memory location AFTER XORing is %x\n", *ptr_2);
		printf("\nThanks for performing an XOR operation at an allocated memory location...\n");
	}
}

// 6. Psuedo-random number generator				: psuedogen(seed, n, address)

float psuedogen(float seed, int n, int address)
{
	float random;
	int print;

	void generator(void)
	{
		random = ((0.4353491074*seed) + 0.8173946121);
		while(random>1)
		{
			random /= 10;
		}
		random *= MAX;
		print = (int)random;
		printf("\n%d ",print);
		seed = random;
	}

	{
		printf("\nPlease, enter a valid seed value (compatible with float data type): \n");
		scanf("%f", &seed);
		printf("\nPlease, enter the number of 32-bit psuedo-random numbers you wish to create:\n");
		scanf("%d", &n_2);
		while(seed > 1)
		{
			seed /= 10;
		}
		int tmp = 0;
		while(tmp < n_2)
		{
			generator();
			tmp += 1;
		}
		printf("\nThanks for performing generating a psuedo random number...\n");
		printf("\nDo you wish to store this psuedo-random pattern? (Please type 1 for yes and 0 for no)\n");
		scanf("%d", &test);
		if(test == 1)
		{
			if(ptr==0)
			{
				printf("\nUnfortunately, you have not been allocated any memory so far and so it is not possible to store the pattern at this point of time...\n");
				goto END;
			}
			else if(n < n_2)
			{
				printf("\nSince, the allocated memory is not enough to store the pattern, please, allocate more words of memory than the number of psuedo-random numbers that are generated...\n ");
				goto END;
			}	
			else
			{
				printf("\nThe allocated addresses are as below:\n");
				for(i=1; i<=n; i++)
				{
					printf("\nRelative address: %d \t\t Actual address: %x \t\t Existing hex data at this location in Hex: %x", i, (ptr+i-1), *(ptr+i-1));
				}
P0:				printf("\nPlease, specify the starting memory location in hex from the allocated memory locations to store the pattern:\n");
				scanf("%x", &ptr_2);
				for(k=1; k<=n_2; k++)
				{
					if(ptr_2 != (ptr+k-1))
					{
						printf("\nThe entered memory location is outside the allocated range\n");
						goto P0;
					}
					else
					{
						random = ((0.4353491074*seed) + 0.8173946121);
						while(random>1)
						{
							random /= 10;
						}
						while(seed > 1)
						{
							seed /= 10;
						}
						random *= MAX;
						print = (int)random;
						seed = random;
						*(ptr_2+k-1)=print;
						printf("\nThe list of the pattern data vs the memory location in hex is as below:\n");
						printf("\nPattern data: %d \t\t Corresponding Hex Memory Location: %x", print, (ptr_2+k-1));
						printf("\nThanks for storing the generated psuedo-random number pattern...\n");
					}
				}
			}
			goto P0;
		}
		else
		{
			printf("\nThe generated psuedo-random number has not been stored into the allocated memory\n");
		}
	}
END: printf("\n...Taking back to the main options...\n");
}

main()
{
top:	printf("\nPlease, enter any one of the alphabets in capital letters as per the below given chart to execute the function:\n");
		printf("\nA	int memalloc(int n);\n");
		printf("\nB	void memfree(void);\n");
		printf("\nC	memread(address);\n");
		printf("\nD	memwrite(address);\n");
		printf("\nE 	memxor(address);\n");
		printf("\nF 	psuedogen(n, address);\n");
		printf("\nG 	psuedover(n, address);\n");
		printf("\nH 	memtest(address_1, address_2);\n");
		printf("\nI 	timetest(L1,L2);\n\n");
		scanf("%c", &c);
		switch(c)
		{
			case 'A':	memalloc(n);
						printf("\nThanks for giving us the opportunity to serve you...\n");
						break;
			case 'B':	memfree();
						printf("\nThanks for giving us the opportunity to serve you...\n");
						break;
			case 'C':	memread(address);
						printf("\nThanks for giving us the opportunity to serve you...\n");
						break;
			case 'D':	memwrite(address);
						printf("\nThanks for giving us the opportunity to serve you...\n");
						break;
			case 'E':	memxor(address);
						printf("\nThanks for giving us the opportunity to serve you...\n");
						break;
			case 'F':	psuedogen(seed, n, address);
						printf("\nThanks for giving us the opportunity to serve you...\n");
						break;
//			case 'G':	psuedover(n, address);
//						printf("\nThanks for giving us the opportunity to serve you...\n");
//						break;
//			case 'H':	memtest(address_1, address_2);
//						printf("\nThanks for giving us the opportunity to serve you...\n");
//						break;
//			case 'I':	timetest(L1,L2);
//						printf("\nThanks for giving us the opportunity to serve you...\n");
//						break;
			default:	printf("\nThanks for giving us the opportunity to serve you...\n");
						goto top;
		}
		printf("\nRe-starting the process...\n");
		goto top;
	
	return 0;	
}
