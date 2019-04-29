/******************************************************************************
* Name: Variable Size Memory Allocation                                        *
*                                                                              *
* Author: Dor Yadidi                                                           *
* Last Update: 4.12.18                                                         *
*******************************************************************************/

#include "../include/test.h"
#include "../include/variable_size_memory_allocation.h"
#include <stdio.h>

TestResult TestVSMACreate();
TestResult TestVSMAGetBlock();
TestResult TestVSMAFreeBlock();
TestResult TestSupportedBlockSize();

int main()
{
	RUN_TEST(TestVSMACreate);
	RUN_TEST(TestVSMAGetBlock);
	RUN_TEST(TestSupportedBlockSize);
	RUN_TEST(TestVSMAFreeBlock);

	return (0);
}

TestResult TestVSMACreate()
{
	size_t block_size = 1024;
	size_t sizeof_head = VSMAllocGetHeaderSize();
	vsmalloc_t *vsm = VSMAllocCreate(block_size);
	REQUIRE(block_size - sizeof_head  == VSMAllocGetBiggestFreeBlockSize(vsm));
	
	VSMAllocDestroy(vsm);
	
	return (TEST_PASS);
}

TestResult TestVSMAGetBlock()
{
	size_t block_size = 1024;
	size_t get_bigest = 0;
	size_t get_bigest2 = 0;
	size_t get_bigest3 = 0;		
	size_t sizeof_head = VSMAllocGetHeaderSize();	
	
	vsmalloc_t *vsm = VSMAllocCreate(block_size);
	get_bigest = VSMAllocGetBiggestFreeBlockSize(vsm);
	REQUIRE(block_size - sizeof_head  == get_bigest);
	
	VSMAllocGetBlock(vsm , 53);
	get_bigest2 = VSMAllocGetBiggestFreeBlockSize(vsm);
	REQUIRE(get_bigest - 53 - sizeof_head  == get_bigest2);
	
	VSMAllocGetBlock(vsm , 12);
	get_bigest3 = VSMAllocGetBiggestFreeBlockSize(vsm);	
	REQUIRE(get_bigest2 - 12 - sizeof_head  == get_bigest3);
	
	VSMAllocDestroy(vsm);
	return (TEST_PASS);
}

TestResult TestVSMAFreeBlock()
{
	size_t block_size = 1024;
	size_t sizeof_head = VSMAllocGetHeaderSize();
	size_t get_bigest = 0;
	size_t get_bigest2 = 0;	
	vsmalloc_t *vsm = VSMAllocCreate(block_size);
	void *block2 = NULL;
	void *block3 = NULL;	

	VSMAllocGetBlock(vsm , 53);
	VSMAllocGetBlock(vsm , 12);
	block2 = VSMAllocGetBlock(vsm , 500);
	block3 = VSMAllocGetBlock(vsm , 200);	

	get_bigest = VSMAllocGetBiggestFreeBlockSize(vsm);
	REQUIRE(block_size - (5 * sizeof_head) - 765  == get_bigest);

	VSMAllocFreeBlock(block2);
	get_bigest2 = VSMAllocGetBiggestFreeBlockSize(vsm);
	REQUIRE(500 == get_bigest2);	
	
	VSMAllocFreeBlock(block3);
	get_bigest2 = VSMAllocGetBiggestFreeBlockSize(vsm);
	REQUIRE(block_size - (3 * sizeof_head) - 65 == get_bigest2);				
	
	VSMAllocDestroy(vsm);	
	return (TEST_PASS);
}

TestResult TestSupportedBlockSize()
{
	REQUIRE(VSMAllocSupportedBlockSize(12) == 16);
	REQUIRE(VSMAllocSupportedBlockSize(24) == 24);	

	return (TEST_PASS);
}

