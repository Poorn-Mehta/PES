// C Program to allow the user to control memory operations - "8-bit storage per address and jump of 32-bits"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<conio.h>
//#include<math.h>

int main()
{
	int n;	// n specifies the number of 32 bit words the user wants to enter - this means the number of 4 characters that the user wants to enter since 1 char uses 1 byte of space
	int *str; // pointer to memory location
	int i; // hex data
	int k; // the number of loops corresponding to the number of 32 bits
	int response; //response char which decides if the user wants to free the assigned memory location
	
		for(;;)
		{
			printf("Hello! Please, enter the number of 32 bits (4 bytes) that you wish to store at a memory location: \n \n");
			scanf("%d", &n);
//			for (k=1, k=n; k++)
			printf("Please, enter the 1st data that you wish to store \n \n");
			scanf("%x", &i);
			//Memory allocation
			str = (int *)	malloc(4*n);
			*str = i;
			printf("data = %x,  Address = %x, relative address = 0\n", *str, str);
			if(n > 1)
			{
				for (k=2; k<=n; k++)
				{
					printf("Please, enter the %d th data that you wish to store \n \n", k);
					scanf("%x", &i);
					*(str+(k-1))=i;
					printf("data = %x,  Address = %x, relative address = %d \n", *(str+(k-1)), (str+(k-1)),(k-1));
				}
			}
		}
			
//			printf("Do you wish to free this memory location? Type 0 for No and 1 for Yes \n");
//			scanf("%d", &response);
			
//			if (response == 1)
//			{
//				*str = 0;
//				printf("You have successfully freed the memory locations \n \n");
//				printf("Your current values are data = %x, Address = %x, second data = %x, Address = %x \n \n", *str, str, *(str+1), (str+1));
//			}
//			
//			else if (response == 0)
//			{
//				printf("The memory location has not been freed as demanded \n \n");
//				printf("Your current values are data = %x, Address = %x, second data = %x, Address = %x \n \n", *str, str, *(str+1), (str+1));
//			}
	
	printf("\n \n Thank you for using our services \n \n");
	return 0;
}
