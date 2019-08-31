// C Program to allow the user to seek help

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<math.h>

int main(void)
{	
	int m,n;
	char i[5];					// The important initial entry point
	char h[5] = {"help"};			// entry of 'help'
	char h_copy[8][30] = {"help.mem_alloc", "help.mem_free", "help.mem_disp", "help.mem_write", "help.mem_inv", "help.write_pattern", "help.verify_pattern"};	// entry of 'help.__' commands
	char test[30];
	char e[5] = {"exit"};			// entry of 'exit'
	char k[30];					// entry of 'relevant instruction keyword'
//	char instructions[8][25] = {"mem_alloc", "mem_free", "mem_disp", "mem_write", "mem_inv", "write_pattern", "verify_pattern"};
//	int result_1 = strcmp(i,h);
//	int result_2 = strcmp(k,h);
//	int result_3 = strcmp(k,test);
//	int result_4 = strcmp(i,e);
	
	for(;;)
	{
			
		printf("Welcome to the UI \n \n");
		printf("To seek help, write 'help' or enter 'exit' to exit this program \n \n \n");
//		if(scanf("%4s", i) == 1)
		scanf("%4s", &i);
		int result_1 = strcmp(i,h);
//		int result_4 = strcmp(i,e);
		
		// Comparing the entered initial data with 'help' and 'exit' to decide the next phase of the UI
		if(result_1 == 0)
		{
			printf("The list of help instructions are as follows: \n \n");
			printf("To learn more about instructions, enter 'help.___' where the space contains a valid instruction keyword \n \n \n");
//			if(scanf("%29s", k) == 1)
			scanf("%29s", &k);
			int result_2 = strcmp(k,h);
			while(result_2 >= 0)
			// If the help.__ data contains something valid other than NULL (0) then, we process further
			{
				for (m=0; m<8; m++)
				{
					for (n=0; n<30; n++)
					{
						test[n] = h_copy[m][n];
					}
					int result_3 = strcmp(k,test);
					if (result_3 >= 0)			// While the system concatenated the 'help' and available instructions, we compare it with the entered data if it is equal
					{
						printf("It's a valid instruction keyword associated with the help command \n \n \n");
			//			information_keyword(k);	 //external function which has yet to be designed
						return 0;
					}
					else
					{	
						printf("Unfortunately, the entered 'help.__' command is invalid or does not match with our database \n \n \n");
						return 0;
					}
				}
			}
		}
		
		// Since, the entered data is different from 'help', it will be compared with 'exit'
		int result_4 = strcmp(i,e);
		if (result_4 == 0)
		{
			printf("\n This UI has been terminated... Thanks \n \n \n \n \n");
		}
		
		// Since, the entered data does not match with 'help' or 'exit', it will be termed as invalid 
		else
		{
			printf("\n You have entered an invalid command \n \n \n \n \n");
		}
		return 0;
	}
	return 0;
}
