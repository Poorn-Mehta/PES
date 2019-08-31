#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<math.h>

int main(void)
{
    int address;
//  int tst_address;
	int data;
	char *str;
	str = (char *)	malloc(30);
	printf("value = %s,  Address = %u\n", str, str);
	
	printf("Enter your address");
    scanf("%d", &address);
    printf("Enter your 32-bit (4 byte - 4 number) data in hex");
    scanf("%04x", &data);
//	int a = 12;
    int *p = (int *) data;
    p = (int *) address;
//    int i;

//    printf("Now, to read the memory location, enter the address once more:");
//    scanf("%d", &tst_address);
//    char *q = (char*) tst_address;
    
//    for (i = 0; i < sizeof(a); ++i)
    {
        printf(" %x", *p);
    }
    printf("\n");
    return 0;
}
