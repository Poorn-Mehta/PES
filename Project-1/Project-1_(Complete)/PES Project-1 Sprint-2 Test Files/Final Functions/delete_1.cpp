// C Program to allow the user to control memory operations

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
//#include<math.h>

int main()
{
	int i,n;	// n specifies the number of 32 bit words the user wants to enter - this means the number of 4 characters that the user wants to enter since 1 char uses 1 byte of space
	char *str; // pointer to memory location
	char s[(4*n)+1]; // variable string
	char e[5] = {"exit"};
	char r[7] = {"return"};
	char e_test[7]; // exit option for this program
	int response; //response char which decides if the user wants to free the assigned memory location
	
L1:	printf("Hello! Please, enter the number of 32 bit words (4 characters) that you wish to store at a memory location: \n \n");
	if (scanf("%d", &n) == 1)
	{
	//	for (i=1; i=n; i++)
		{
			printf("Please, enter the data consecutively in a group of 4 characters that you wish to store \n \n");
			scanf("%s", &s);
				
			//Memory allocation
			str = (char *)	malloc((4*n)+1);
			strcpy(str, s);
			
			printf("String = %s,  Address = %u\n", str, str);
			
			printf("Do you wish to free this memory location? Type 0 for No and 1 for Yes \n");
			scanf("%d", &response);
			
			if (response == 1)
			{
				free (str);
				printf("You have successfully freed the memory locations \n \n");
				printf("Your current values are String = %s, Address = %u \n \n", str, str);
			}
			
			else if (response == 0)
			{
				printf("The memory location has not been freed as demanded \n \n");
				printf("Your current values are String = %s, Address = %u \n \n", str, str);
			}
		}
	}
	else
	{
		printf("Unfortunately, the data that you entered is not an integer value. \n \n");
	}	
L2:	printf("To exit, type 'exit' or to return back to this program execution 'return' \n \n");
	scanf("%s", &e_test);
	if ((strcmp(e_test, e)) == 0)
	{
		printf("\n \n Thank you for using our services \n \n");
	}
	if ((strcmp(e_test, r)) == 0)
	{
		goto L1;
	}
	if ((strcmp(e_test, e)) && strcmp (e_test, r) != 0)
	{
		goto L2;
	}
	return 0;
}
