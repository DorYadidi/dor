/*******************************************************************************
* NAME: Fixed Size Memory Allocation                                           *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  29.11.18                                                      *
*******************************************************************************/

#include "../include/test.h"
#include "../include/fixed_size_memory_allocation.h"
#include <stdio.h>

TestResult TestFSMACreate();
TestResult TestFSMAGetBlock();
TestResult TestFSMAFreeBlock();
TestResult TestSupportedBlockSize();

int main()
{
	RUN_TEST(TestFSMACreate);
	RUN_TEST(TestSupportedBlockSize);
	RUN_TEST(TestFSMAGetBlock);
	RUN_TEST(TestFSMAFreeBlock);

	return (0);
}

TestResult TestFSMACreate()
{
	size_t block_size = 8;
	size_t number_of_blocks = 6;
	fsmalloc_t *fsm = FSMAllocCreate(block_size, number_of_blocks);
	REQUIRE(6 == FSMAllocCountFree(fsm));
	
	
	FSMAllocDestroy(fsm);
	
	return (TEST_PASS);
}

TestResult TestFSMAGetBlock()
{
	size_t block_size = 8;
	size_t number_of_blocks = 6;
	fsmalloc_t *fsm = FSMAllocCreate(block_size, number_of_blocks);
	REQUIRE(6 == FSMAllocCountFree(fsm));
	REQUIRE(FSMAllocGetBlock(fsm));
	REQUIRE(5 == FSMAllocCountFree(fsm));
	REQUIRE(FSMAllocGetBlock(fsm));
	REQUIRE(4 == FSMAllocCountFree(fsm));
	REQUIRE(FSMAllocGetBlock(fsm));
	REQUIRE(3 == FSMAllocCountFree(fsm));
	REQUIRE(FSMAllocGetBlock(fsm));
	REQUIRE(2 == FSMAllocCountFree(fsm));
	REQUIRE(FSMAllocGetBlock(fsm));
	REQUIRE(1 == FSMAllocCountFree(fsm));
	REQUIRE(FSMAllocGetBlock(fsm));
	REQUIRE(0 == FSMAllocCountFree(fsm));
	
	FSMAllocDestroy(fsm);
	return (TEST_PASS);
}

TestResult TestFSMAFreeBlock()
{
	size_t block_size = 16;
	size_t number_of_blocks = 3;
	fsmalloc_t *fsm = FSMAllocCreate(block_size, number_of_blocks);
	void *block1;
	void *block2;	
	void *block3;	

	block1 = FSMAllocGetBlock(fsm);
	block2 = FSMAllocGetBlock(fsm);
	block3 = FSMAllocGetBlock(fsm);

	REQUIRE(0 == FSMAllocCountFree(fsm));

	FSMAllocFreeBlock(fsm, block1);
	REQUIRE(1 == FSMAllocCountFree(fsm));
	FSMAllocFreeBlock(fsm, block3);
	REQUIRE(2 == FSMAllocCountFree(fsm));
	FSMAllocFreeBlock(fsm, block2);
	REQUIRE(3 == FSMAllocCountFree(fsm));	

	FSMAllocDestroy(fsm);	
	return (TEST_PASS);
}

TestResult TestSupportedBlockSize()
{
	REQUIRE(FSMAllocSupportedBlockSize(12) == 16);
	REQUIRE(FSMAllocSupportedBlockSize(24) == 24);	

	return (TEST_PASS);
}
