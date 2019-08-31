#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
/*
#define Max		100000

float random, seed;
int print;

void generator(void)
{
	random = ((0.4353491074*seed) + 0.8173946121);
	while(random>1)
	{
		random /= 10;
	}
	random *= Max;
	print = (int)random;
	printf("\n%d",print);
	seed = random;
}*/

int main(void)
{
	printf("\nCode Started\n");
	uint32_t tmp, tmp2;
	scanf("%x", &tmp);
	scanf("%x", &tmp2);
	uint32_t *ptr;
	ptr = (uint32_t *)malloc(tmp);
	*ptr = tmp2;
	printf("%x",*ptr);
/*	uint8_t input_j, hex_flag;
	uint32_t value;
	hex_flag = 1;
	char test[50];
	while(1)
	{
		fgets(test, 50, stdin);
		input_j = 0;
		while(test[input_j] != '\n')
		{
			input_j += 1;
		}
		test[input_j] = 0;
		if(hex_flag == 0)
		{
			uint8_t dummy = 1;
		//	String_to_Decimal(test);
		}
		else
		{
			input_j = 0;
			char *ptr;
			ptr = &test;
			while(test[input_j] != 0)
			{
				if(((test[input_j] >= '0') && (test[input_j] <= '9')) || ((test[input_j] >= 'a') && (test[input_j] <= 'f')) || ((test[input_j] >= 'A') && (test[input_j] <= 'F')))
				{
					input_j += 1;
				}
				else
				{
					break;
				}
			}
			if(test[input_j] == 0)
			{
				value = (uint32_t) strtol(ptr, NULL, 16);
				printf("\n%x\n", value);
			}
			else
			{
				printf("\nError\n");
			}
		}
	}
	char arr[20];
	unsigned int print;
	fgets(arr, 20, stdin);
	print = (unsigned int) strtol(arr, NULL, 16);
	printf("%x", print);
	printf("%d",print);
	long int *tmp;
	tmp = (long int *) malloc(32);
	printf("%x", tmp);
	char str[100];
	printf("Enter string: ");
	fgets(str, 100, stdin);
	printf("%s",str);
	char arr[200], tmp[100], i, j;
	printf("Enter Seed: ");
	scanf("%s", tmp);
	j = 0;
	i = 0;
	while(tmp[j] != 0)
	{
		arr[i] = tmp[j];
		i += 1;
		j += 1;
	}
	arr[i] = 0;
	i += 1;
	printf("Enter Seed: ");
	scanf("%s", tmp);
	j = 0;
	while(tmp[j] != 0)
	{
		arr[i] = tmp[j];
		i += 1;
		j += 1;
	}
	arr[i] = 0;
	i += 1;
	arr[i] = '\n';
	i = 0;
	while(arr[i] != '\n')
	{
		
		printf("\n%x", arr[i]);
		i += 1;
	}
	int read;
	scanf("%x", &read);
	printf("\n%x", read);
	read ^= 0xFFFFFFFF;
	printf("\n%x",read);
	scanf("%f", &seed);
	while(seed > 1)
	{
		seed /= 10;
	}
	uint8_t tmp = 0;
	while(tmp < 15)
	{
		generator();
		tmp += 1;
	}*/
}
