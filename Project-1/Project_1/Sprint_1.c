/*
 * Trial.c
 *
 *  Created on: Sep 24, 2018
 *      Author: root
 */


#include <stdio.h>
#include <string.h>
#include "Sprint_1.h"

int main(void)
{
	printf("Welcome\n");
	printf("\nType help to get information about using it");
	while(1)
	{
		printf("\nEnter Command: ");
		scanf("%s",str1);
			if((strcmp(str1, help) == 0) || (strcmp(str1, exit) == 0) || (strncmp(str1, "help.", 5) == 0))
			{
				if(strcmp(str1, help) == 0)
				{
					printf("Put a . after help and then type the command\n");
					printf("For example - type: help.exit\n");
				}
				else if(strcmp(str1, exit) == 0)
				{
					printf("Exiting\n");
					break;
				}
				else
				{
					unsigned char str_pos2 = 0;
					for(str_pos = 5;;str_pos ++)
					{
						str2[str_pos2] = str1[str_pos];
						str_pos2 += 1;
						if(str1[str_pos] == 0)
						{
							break;
						}
					}
					if(strcmp(str2, "exit") == 0)
					{
						printf("\n\n Help on Exit Command");
						printf("\n Just type in 'exit' to close");
					}
					else
					{
						printf("\n Command Not Recognized");
					}
				}
			}
			else
			{
				printf("Invalid Command");
			}
	}
}
