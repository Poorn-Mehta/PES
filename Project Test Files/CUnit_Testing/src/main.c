#include "Custom_Main.h"
#include "Custom_Circular_Buffer.h"

Byte CBuffer_Data;

#ifdef	FRDM
void FGETS(char *array_to_write, Byte bytes, FILE *stream)
{
	char *tmp;
	tmp = array_to_write;
	do{
		*array_to_write = GETCHAR();
		PUTCHAR(*array_to_write);
		if(*array_to_write == Enter_Detected)	break;
		array_to_write += 1;
	}while(array_to_write < (tmp + bytes));
}
#endif


int main(void)
{
//	#if		TEST
//	
//	return (t_main());
//	
//	#else

#ifdef FRDM
    // Initialize standard SDK demo application pins
    hardware_init();
#endif

    //take 2 buffers, with the first one having the length of 3, another around 4-10

	if(CBuffer_Init())	Output_String("\n\rInit Failed\n\r");

	//test 1 - overwriting

	CBuffer_Operation(0, Write, 'A', &CBuffer_Data);
	CBuffer_Operation(0, Write, 'B', &CBuffer_Data);
	CBuffer_Operation(0, Write, 'C', &CBuffer_Data);
	CBuffer_Operation(0, Write, 'D', &CBuffer_Data);

	Output_String("\n\r\n\r");

	//test 2 - empty reading

	CBuffer_Operation(0, Read, 0, &CBuffer_Data);
	CBuffer_Operation(0, Read, 0, &CBuffer_Data);
	CBuffer_Operation(0, Read, 0, &CBuffer_Data);
	CBuffer_Operation(0, Read, 0, &CBuffer_Data);
	CBuffer_Operation(0, Read, 0, &CBuffer_Data);

	Output_String("\n\r\n\r");

	//test 3 - less than full writing

	CBuffer_Operation(0, Write, 'X', &CBuffer_Data);
	CBuffer_Operation(0, Write, 'Y', &CBuffer_Data);

	Output_String("\n\r\n\r");

	//test 4 - reading only the new data

	CBuffer_Operation(0, Read, 0, &CBuffer_Data);
	CBuffer_Operation(0, Read, 0, &CBuffer_Data);
	CBuffer_Operation(0, Read, 0, &CBuffer_Data);

	//test 5 - multiple read and write after one another

	CBuffer_Operation(0, Write, 'P', &CBuffer_Data);
	CBuffer_Operation(0, Write, 'Q', &CBuffer_Data);
	CBuffer_Operation(0, Read, 0, &CBuffer_Data);
	CBuffer_Operation(0, Write, 'R', &CBuffer_Data);
	CBuffer_Operation(0, Write, 'S', &CBuffer_Data);
	CBuffer_Operation(0, Read, 0, &CBuffer_Data);
	CBuffer_Operation(0, Read, 0, &CBuffer_Data);
	CBuffer_Operation(0, Write, 'T', &CBuffer_Data);
	CBuffer_Operation(0, Write, 'U', &CBuffer_Data);
	CBuffer_Operation(0, Write, 'V', &CBuffer_Data);

	CBuffer_Operation(0, Read, 0, &CBuffer_Data);
	CBuffer_Operation(0, Read, 0, &CBuffer_Data);
	CBuffer_Operation(0, Read, 0, &CBuffer_Data);
	CBuffer_Operation(0, Read, 0, &CBuffer_Data);
	CBuffer_Operation(0, Read, 0, &CBuffer_Data);
	CBuffer_Operation(0, Read, 0, &CBuffer_Data);


	//test 6 - getting number of elements in buffer 1


	CBuffer_Operation(1, Write, 'E', &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Write, 'F', &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Write, 'G', &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Write, 'H', &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Write, 'I', &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Write, 'J', &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Write, 'K', &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Write, 'L', &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Write, 'M', &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Write, 'N', &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Write, 'O', &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Write, 'P', &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));

	CBuffer_Operation(1, Read, 0, &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Read, 0, &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Read, 0, &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Read, 0, &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Read, 0, &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Read, 0, &CBuffer_Data);

	//test 7 - runtime resizing

	if(CBuffer_Resize(1))	return 1;


	CBuffer_Operation(1, Write, 'E', &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Write, 'F', &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Write, 'G', &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Write, 'H', &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Write, 'I', &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Write, 'J', &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Write, 'K', &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Write, 'L', &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Write, 'M', &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Write, 'N', &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Write, 'O', &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Write, 'P', &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));

	CBuffer_Operation(1, Read, 0, &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Read, 0, &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Read, 0, &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Read, 0, &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Read, 0, &CBuffer_Data);
	Output_String("\n\rElements in 1: %d\n\r", CBuffer_Elements(1));
	CBuffer_Operation(1, Read, 0, &CBuffer_Data);
    return 0;
//    #endif
}
