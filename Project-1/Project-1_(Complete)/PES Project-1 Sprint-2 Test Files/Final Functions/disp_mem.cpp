#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<math.h>

main()
{
	for(;;)
	{
	    int x;
		printf("Enter your address \n \n");
	    scanf("%d", &x);
	    unsigned char *p = (unsigned char *)&x;
	
	    
	//	int y;
	
	    printf("the data at the specified memory location is =");
	 //   for (y = 0; y < sizeof(x); ++y)
	    {
	        printf(" %02x", p);
	    }
	    printf("\n");
	}
	return 0;
}
