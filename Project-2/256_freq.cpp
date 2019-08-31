// PES Project - 2 [CODE for the Application Part]

/* Including libraries */

#include <stdio.h>
#include <string.h>

#define str_length 100000 // user-defined string length in terms of characters

/* Declaring a function that calculates the number of characters in an input string */
 
int character_count(char [], long int []);
void count_reset(int, long int []);

/* Main Function */
 
int main()
{
/* int str_length; // taking the length of the string from the user in terms of number of characters
   printf("\nEnter the string length: ");
   scanf("%d", &str_length);*/
   
   char input_string[str_length]; // Array for the string accepted from the user
   long int count_const, count[256] = {0}, clear_count; // count_const updates the count array and clear count helps flush off past count values
   while(1)
   {     
	   printf("\n\nInput a string\n");
	   gets(input_string);
	 
	   character_count(input_string, count); // using the self-declared function
	   
	   printf("\nYou entered the string: %s\n", input_string);
	   printf("\nThe entered string length including whitespaces is: %d\n\n", sizeof(input_string));
		{
			for (count_const = 0; count_const < 256; count_const++) // for 95 specific character values, the count array calculates the char reps
			{
				if(count[count_const] > 0) // provides characters with one or more reps
				{
					printf("Hex Code: %x \t Count: %d \t Character: %c \n", count_const + 0x0, count[count_const], count_const + 0x0);
				}
			}
		}
		
		//Flushing the count data
		count_reset(clear_count, count);
		printf("-----------------------------------------------------");
	}
   return 0;
}
 
int character_count(char string[], long int count[]) 
{
   int count_const = 0;
   
   while (string[count_const] != '\0')  // Accepting string inputs other than NULL values
   {
    if (string[count_const] >= 0 && string[count_const] <= 255) // Including the ASCII values contained between and inclusive of SPACE and ~
    {
      	count[string[count_const]-0x0]++; // Relative addressing for the count array for the 95 character values
      	count_const++; // Incrementing the variable to store new character reps at a new location in the array
	}
	else // Error checking: If the string contains unidentified characters then an error message will be generated but will still count the character frequency
	{
		printf("\nCAUTION: [ERROR] The string has one or more characters that cannot be documented which has been replaced by a similar character...\n");
		return 0;
	}
   }
}

void count_reset(int clear_count, long int count[]) // Count-reset function used for clearing the counts for new freq check
{
	for(clear_count = 0; clear_count < 256; clear_count++) // for all test cases
	{
		count[clear_count] = 0; // simply cleared all the count locations that stored the previous frequency values
	}
}
