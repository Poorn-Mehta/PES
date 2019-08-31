// C Program to allow the user to control memory operations

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<conio.h>
//#include<math.h>

int main()
{
	int n;	// n specifies the number of 32 bit words the user wants to enter - this means the number of 4 characters that the user wants to enter since 1 char uses 1 byte of space
	char *str; // pointer to memory location
	char s[n+1]; // variable string
	int response; //response char which decides if the user wants to free the assigned memory location
	
	printf("Hello! Please, enter the number of 32 bit words (4 characters) that you wish to store at a memory location: \n \n");
	scanf("%d", &n);
	printf("Please, enter the data that you wish to store \n \n");
	scanf("%50s", &s);
	
	//Memory allocation
	str = (char *)	malloc(n+1);
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
	
	printf("\n \n Thank you for using our services \n \n");
	return 0;
}
