// Courtesy: I found this code on Quora published by one Quora user. 
// Link:	 https://www.quora.com/How-do-I-generate-random-numbers-in-certain-range-without-using-rand-function-in-C

#include<stdio.h>
#include<time.h>

int main()

{
	for (;;)
	{
		
		int num;
		
		time_t sec;
		
		sec=time(NULL);
		
		printf("Enter The Number\n");
		
		scanf("%d",&num);
		
		if(num>0)
		
		{
		
		for(;;)
		
		{
		
		sec=sec%3600;
		
		if(num>=sec)
		
		{
		
		printf("%ld\n",sec);
		
		break;
		
		}
		
		sec=sec%num;
		
		}
		
		}
		
		else
		
		{
		
		printf("Please Enter Positive Value\n\n\n\n\n\n");
		
		}
		
	//	return 0;
	}
}
