/*
 *  Simple example of a CUnit unit test.
 *
 *  This program (crudely) demonstrates a very simple "black box"
 *  test of the standard library functions fprintf() and fread().
 *  It uses suite initialization and cleanup functions to open
 *  and close a common temporary file used by the test functions.
 *  The test functions then write to and read from the temporary
 *  file in the course of testing the library functions.
 *
 *  The 2 test functions are added to a single CUnit suite, and
 *  then run using the CUnit Basic interface.  The output of the
 *  program (on CUnit version 2.0-2) is:
 *
 *           CUnit : A Unit testing framework for C.
 *           http://cunit.sourceforge.net/
 *
 *       Suite: Suite_1
 *         Test: test of fprintf() ... passed
 *         Test: test of fread() ... passed
 *
 *       --Run Summary: Type      Total     Ran  Passed  Failed
 *                      suites        1       1     n/a       0
 *                      tests         2       2       2       0
 *                      asserts       5       5       5       0
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "CUnit/Basic.h"

#include "Custom_Main.h"
#include "Custom_Circular_Buffer.h"

/* Pointer to the file used by the tests. */
static FILE* temp_file = NULL;
uint32_t len1, len2, nlen;
uint8_t w_data[20], r_data[20], test_i, temp;
#define Max_Data	0x7E  // till ~
#define Min_Data	0x21 //from !
#define Max_Len		20
/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void)
{
   if (NULL == (temp_file = fopen("temp.txt", "w+"))) {
      return -1;
   }
   else {
      return 0;
   }
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void)
{
   if (0 != fclose(temp_file)) {
      return -1;
   }
   else {
      temp_file = NULL;
      return 0;
   }
}

/* test of buffer init
 */
void test_CBuf_Init(void)
{
   if (NULL != temp_file) {
      rewind(temp_file);
      fprintf(temp_file, "\n\n\nCBuffer Init Test\nBuffer0 Length: %d\tBuffer1 Length: %d\n", len1, len2);
      CU_ASSERT_FATAL(0 == CBuffer_Init(len1, len2));
   }
}

void test_CBuf_Overwrite(void)
{
   if (NULL != temp_file) {
      temp = rand() % (len1+1);
      fprintf(temp_file, "\n\n\nCBuffer Overwrite Test\nWriting %d bytes in Buffer0\n", (len1+temp));
      
      fprintf(temp_file, "\n\n\nStarting to Write");
      for(test_i = 0; test_i < len1; test_i ++)
      {
      	w_data[test_i] = Min_Data + (rand() % (Max_Data + 1));
      	CU_ASSERT(Success == CBuffer_Byte_Write(0, w_data[test_i]));
      	fprintf(temp_file, "\nWrote %c at %d in Buffer0", w_data[test_i], test_i);
	  }
	  
	  fprintf(temp_file, "\n\n\nStarting to Overwrite");
	  for(test_i = 0; test_i < temp; test_i ++)
      {
      	w_data[test_i] = Min_Data + (rand() % (Max_Data + 1));
      	CU_ASSERT(Overwriting == CBuffer_Byte_Write(0, w_data[test_i]));
      	fprintf(temp_file, "\nOverwrote %c at %d in Buffer0", w_data[test_i], test_i);
	  }
   }
}

void test_CBuf_Emptyread(void)
{
   if (NULL != temp_file) {
      temp = rand() % (len1+1);
	  fprintf(temp_file, "\n\n\nCBuffer Emptyread Test\nReading %d bytes from Buffer0\n", (len1+temp));
	  
	  fprintf(temp_file, "\n\n\nStarting to Read");
      for(test_i = 0; test_i < len1; test_i ++)
      {
      	CU_ASSERT(Success == CBuffer_Byte_Read(0, &r_data[test_i]));
        CU_ASSERT(w_data[test_i] == r_data[test_i]);
        fprintf(temp_file, "\nRead %c from %d in Buffer0", r_data[test_i], test_i);
	  }
	  
	  fprintf(temp_file, "\n\n\nStarting to Emptyread");
	  for(test_i = 0; test_i < temp; test_i ++)
      {
      	CU_ASSERT(Empty == CBuffer_Byte_Read(0, &r_data[test_i]));
        fprintf(temp_file, "\nBuffer0 Empty");
	  }
   }
}

void test_CBuf_Partialfill(void)
{
	Byte data;
   if (NULL != temp_file) {
	  temp = rand() % len1;
	  fprintf(temp_file, "\n\n\nCBuffer Partialfill Test\nWriting %d bytes in Buffer0\n", temp);
	  
	  fprintf(temp_file, "\n\n\nStarting to Write");
	  for(test_i = 0; test_i < temp; test_i ++)
      {
      	w_data[test_i] = Min_Data + (rand() % (Max_Data + 1));
      	CU_ASSERT(Success == CBuffer_Byte_Write(0, w_data[test_i]));
      	fprintf(temp_file, "\nWrote %c at %d in Buffer0", w_data[test_i], test_i);
	  }
	  
	  fprintf(temp_file, "\n\n\nStarting to Read");
	  for(test_i = 0; test_i < temp; test_i ++)
      {
      	CU_ASSERT(Success == CBuffer_Byte_Read(0, &r_data[test_i]));
        CU_ASSERT(w_data[test_i] == r_data[test_i]);
        fprintf(temp_file, "\nRead %c from %d in Buffer0", r_data[test_i], test_i);
	  }
	  
	  fprintf(temp_file, "\n\n\nStarting to Emptyread");
	  for(test_i = 0; test_i < (len1 - temp); test_i ++)
      {
      	CU_ASSERT(Empty == CBuffer_Byte_Read(0, &r_data[test_i]));
        fprintf(temp_file, "\nBuffer0 Empty");
	  }
   }
}

//void test_CBuf_Continuouscomplex(void)
//{
//	Byte data;
//   if (NULL != temp_file) {
////      rewind(temp_file);
//      CU_ASSERT(Success == CBuffer_Byte_Write(0, 'P'));
//      CU_ASSERT(Success == CBuffer_Byte_Write(0, 'Q'));
//      CU_ASSERT(Success == CBuffer_Byte_Read(0, &data));
//      CU_ASSERT('P' == data);
//      CU_ASSERT(Success == CBuffer_Byte_Write(0, 'R'));
//      CU_ASSERT(Success == CBuffer_Byte_Write(0, 'S'));
//      CU_ASSERT(Success == CBuffer_Byte_Read(0, &data));
//      CU_ASSERT('Q' == data);
//      CU_ASSERT(Success == CBuffer_Byte_Read(0, &data));
//      CU_ASSERT('R' == data);
//      CU_ASSERT(Success == CBuffer_Byte_Write(0, 'T'));
//      CU_ASSERT(Success == CBuffer_Byte_Write(0, 'U'));
//      CU_ASSERT(Overwriting == CBuffer_Byte_Write(0, 'V'));
//      CU_ASSERT(Success == CBuffer_Byte_Read(0, &data));
//      CU_ASSERT('V' == data);
//      CU_ASSERT(Success == CBuffer_Byte_Read(0, &data));
//      CU_ASSERT('T' == data);
//      CU_ASSERT(Success == CBuffer_Byte_Read(0, &data));
//      CU_ASSERT('U' == data);
//      CU_ASSERT(Empty == CBuffer_Byte_Read(0, &data));
//      CU_ASSERT(Empty == CBuffer_Byte_Read(0, &data));
//   }
//}

void test_CBuf_Numberofelements(void)
{
	Byte data;
   if (NULL != temp_file) {
	  temp = rand() % (len2+1);
	  fprintf(temp_file, "\n\n\nBuffer Numberofelements Test\nWriting & Reading %d bytes of data from Buffer1\n", (len2+temp));
	  
	  fprintf(temp_file, "\n\n\nStarting to Write");
	  CU_ASSERT(0 == CBuffer_Elements(1));
      fprintf(temp_file, "\nNumber of Elements in Buffer1 are 0");
	  for(test_i = 0; test_i < len2; test_i ++)
      {
      	w_data[test_i] = Min_Data + (rand() % (Max_Data + 1));
      	CU_ASSERT(Success == CBuffer_Byte_Write(1, w_data[test_i]));
      	fprintf(temp_file, "\nWrote %c at %d in Buffer1", w_data[test_i], test_i);
      	CU_ASSERT((test_i+1) == CBuffer_Elements(1));
      	fprintf(temp_file, "\nNumber of Elements in Buffer1 are %d", (test_i+1));
	  }
	  
	  fprintf(temp_file, "\n\n\nStarting to Overwrite");
	  for(test_i = 0; test_i < temp; test_i ++)
      {
      	w_data[test_i] = Min_Data + (rand() % (Max_Data + 1));
      	CU_ASSERT(Overwriting == CBuffer_Byte_Write(1, w_data[test_i]));
      	fprintf(temp_file, "\nOverwrote %c at %d in Buffer1", w_data[test_i], test_i);
      	CU_ASSERT(len2 == CBuffer_Elements(1));
      	fprintf(temp_file, "\nNumber of Elements in Buffer1 are %d", len2);
	  }
	  
	  fprintf(temp_file, "\n\n\nStarting to Read");
      for(test_i = 0; test_i < len2; test_i ++)
      {
      	CU_ASSERT(Success == CBuffer_Byte_Read(1, &r_data[test_i]));
        CU_ASSERT(w_data[test_i] == r_data[test_i]);
        fprintf(temp_file, "\nRead %c from %d in Buffer1", r_data[test_i], test_i);
        CU_ASSERT((len2-(test_i+1)) == CBuffer_Elements(1));
      	fprintf(temp_file, "\nNumber of Elements in Buffer1 are %d", (len2-(test_i+1)));
	  }
	  
	  fprintf(temp_file, "\n\n\nStarting to Emptyread");
	  for(test_i = 0; test_i < temp; test_i ++)
      {
      	CU_ASSERT(Empty == CBuffer_Byte_Read(1, &r_data[test_i]));
        fprintf(temp_file, "\nBuffer0 Empty");
		CU_ASSERT(0 == CBuffer_Elements(1));
      	fprintf(temp_file, "\nNumber of Elements in Buffer1 are 0");
	  }
   }
}

void test_CBuf_Runtimelengthchange(void)
{
	Byte data;
   if (NULL != temp_file) {
//      rewind(temp_file);
	  temp = rand() % (nlen+1);
	  fprintf(temp_file, "\n\n\nBuffer Runtimelengthchange Test\nNew length of Buffer1 is %d\n", nlen);
	  CU_ASSERT(0 == CBuffer_Resize(1, nlen));
	  fprintf(temp_file, "\nWriting & Reading %d bytes of data from Buffer1\n", (nlen+temp));
	  
	  fprintf(temp_file, "\n\n\nStarting to Write");
	  CU_ASSERT(0 == CBuffer_Elements(1));
      fprintf(temp_file, "\nNumber of Elements in Buffer1 are 0");
	  for(test_i = 0; test_i < nlen; test_i ++)
      {
      	w_data[test_i] = Min_Data + (rand() % (Max_Data + 1));
      	CU_ASSERT(Success == CBuffer_Byte_Write(1, w_data[test_i]));
      	fprintf(temp_file, "\nWrote %c at %d in Buffer1", w_data[test_i], test_i);
      	CU_ASSERT((test_i+1) == CBuffer_Elements(1));
      	fprintf(temp_file, "\nNumber of Elements in Buffer1 are %d", (test_i+1));
	  }
	  
	  fprintf(temp_file, "\n\n\nStarting to Overwrite");
	  for(test_i = 0; test_i < temp; test_i ++)
      {
      	w_data[test_i] = Min_Data + (rand() % (Max_Data + 1));
      	CU_ASSERT(Overwriting == CBuffer_Byte_Write(1, w_data[test_i]));
      	fprintf(temp_file, "\nOverwrote %c at %d in Buffer0", w_data[test_i], test_i);
      	CU_ASSERT(nlen == CBuffer_Elements(1));
      	fprintf(temp_file, "\nNumber of Elements in Buffer1 are %d", nlen);
	  }
	  
	  fprintf(temp_file, "\n\n\nStarting to Read");
      for(test_i = 0; test_i < nlen; test_i ++)
      {
      	CU_ASSERT(Success == CBuffer_Byte_Read(1, &r_data[test_i]));
        CU_ASSERT(w_data[test_i] == r_data[test_i]);
        fprintf(temp_file, "\nRead %c from %d in Buffer1", r_data[test_i], test_i);
        CU_ASSERT((nlen-(test_i+1)) == CBuffer_Elements(1));
      	fprintf(temp_file, "\nNumber of Elements in Buffer1 are %d", (nlen-(test_i+1)));
	  }
	  
	  fprintf(temp_file, "\n\n\nStarting to Emptyread");
	  for(test_i = 0; test_i < temp; test_i ++)
      {
      	CU_ASSERT(Empty == CBuffer_Byte_Read(1, &r_data[test_i]));
        fprintf(temp_file, "\nBuffer1 Empty");
		CU_ASSERT(0 == CBuffer_Elements(1));
      	fprintf(temp_file, "\nNumber of Elements in Buffer1 are 0");
	  }
//      CU_ASSERT(0 == CBuffer_Resize(1, 4));
//      CU_ASSERT(0 == CBuffer_Elements(1));
//      CU_ASSERT(Success == CBuffer_Byte_Write(1, 'W'));
//      CU_ASSERT(1 == CBuffer_Elements(1));
//      CU_ASSERT(Success == CBuffer_Byte_Write(1, 'X'));
//      CU_ASSERT(2 == CBuffer_Elements(1));
//      CU_ASSERT(Success == CBuffer_Byte_Write(1, 'Y'));
//      CU_ASSERT(3 == CBuffer_Elements(1));
//	  CU_ASSERT(Success == CBuffer_Byte_Write(1, 'Z'));
//      CU_ASSERT(4 == CBuffer_Elements(1));
//	  CU_ASSERT(Overwriting == CBuffer_Byte_Write(1, 'E'));
//      CU_ASSERT(4 == CBuffer_Elements(1));
//	  CU_ASSERT(Overwriting == CBuffer_Byte_Write(1, 'F'));
//      CU_ASSERT(4 == CBuffer_Elements(1));
//      CU_ASSERT(Success == CBuffer_Byte_Read(1, &data));
//      CU_ASSERT('E' == data);
//      CU_ASSERT(3 == CBuffer_Elements(1));
//      CU_ASSERT(Success == CBuffer_Byte_Read(1, &data));
//      CU_ASSERT('F' == data);
//      CU_ASSERT(2 == CBuffer_Elements(1));
//      CU_ASSERT(Success == CBuffer_Byte_Read(1, &data));
//      CU_ASSERT('Y' == data);
//      CU_ASSERT(1 == CBuffer_Elements(1));
//      CU_ASSERT(Success == CBuffer_Byte_Read(1, &data));
//      CU_ASSERT('Z' == data);
//      CU_ASSERT(0 == CBuffer_Elements(1));
//      CU_ASSERT(Empty == CBuffer_Byte_Read(1, &data));
//      CU_ASSERT(Empty == CBuffer_Byte_Read(1, &data));
   }
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
	srand(time(0));
    len1 = rand() % (Max_Len+1);
    len2 = rand() % (Max_Len+1);
    nlen = rand() % (Max_Len+1);
	
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
   if ((NULL == CU_add_test(pSuite, "test of CBuffer_Init()", test_CBuf_Init)) ||
	   (NULL == CU_add_test(pSuite, "test of CBuffer_Overwrite", test_CBuf_Overwrite)) ||
       (NULL == CU_add_test(pSuite, "test of CBuffer_Emptyread", test_CBuf_Emptyread)) ||
	   (NULL == CU_add_test(pSuite, "test of CBuffer_Partialfill", test_CBuf_Partialfill)) ||
	//   (NULL == CU_add_test(pSuite, "test of CBuffer_Continuouscomplex", test_CBuf_Continuouscomplex)) || 
	   (NULL == CU_add_test(pSuite, "test of CBuffer_Numberofelements", test_CBuf_Numberofelements)) ||
	   (NULL == CU_add_test(pSuite, "test of CBuffer_Runtimelengthchange", test_CBuf_Runtimelengthchange)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
