// C Program to allow the user to control memory operations

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<conio.h>
//#include<math.h>

int main()
{
	char *str;
	char s[21];
	char response;
//	int n;
	printf("Hello! Please, enter upto 20 characters without whitespaces that you wish to store at a memory location: \n");
//	scanf("%d", &n);
//	printf("Please, enter the data that you wish to store \n");
	scanf("%s", &s);
	//Memory allocation
	str = (char *)	malloc(21);
	strcpy(str, s);
	printf("String = %s,  Address = %u\n", str, str);
	printf("Do you wish to free this memory location? Type Y/N \n");
	scanf("%d", response);
	if (response = 'Y')
	free (str);
	else
	return 0;	
}
