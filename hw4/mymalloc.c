#include "mymalloc.h"
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

#define SIZE 1024 * 1024

typedef struct node
{
	void *startPos;
	size_t size;
} node;

// HEAP where memory addresses are retrieved from and data is stored
void *HEAP[SIZE] = {0};

// FREE_LIST[i] == 0, means that the space is free
// FREE_LIST[i] == 1, means that the space is allocated
int FREE_LIST[SIZE] = {0};

// List of addresses and sizes of allocated memory
node *masterList;

// Number of nodes in masterList
int allocated = 0;

// 0 = first fit
// 1 = next fit
// 2 = best fit
int allocArg;

void myinit(int m_allocAlg)
{
	if (m_allocAlg != 0 && m_allocAlg != 1 && m_allocAlg != 2)
		exit(1);
	allocArg = m_allocAlg;

	masterList = (node *)malloc(sizeof(node) * SIZE);
	for (int i = 0; i < SIZE; i++)
	{
		masterList[i].startPos = NULL;
		masterList[i].size = 0;
	}
}

void *mymalloc(size_t size)
{
	if (size == 0)
		return NULL;

	if (size % 8 != 0)
		size = size + (8 - (size % 8));

	// First time mymalloc is called
	if (allocated == 0)
	{
		if (size > SIZE)
			return NULL;

		masterList[0].startPos = &HEAP[0];
		masterList[0].size = size;
		allocated += 1;

		for (int i = 0; i < size; i++)
		{
			FREE_LIST[i] = 1;
		}

		return &HEAP[0];
	}

	// first fit
	if (allocArg == 0)
	{
		int i = 0;
		while (i < SIZE)
		{
			if (FREE_LIST[i] == 0)
			{
				int j = i;
				int count = 0;
				while (j < SIZE && FREE_LIST[j] == 0)
				{
					count++;
					j++;
				}
				if (count >= size)
				{
					for (int k = i; k < i + size; k++)
					{
						FREE_LIST[k] = 1;
						HEAP[k] = 0;
					}
					masterList[allocated].startPos = &HEAP[i];
					masterList[allocated].size = size;
					allocated += 1;
					return &HEAP[i];
				}
				i = j;
			}
			i++;
		}
	}

	// next fit
	if (allocArg == 1)
	{
		static int i = 0;
		// printf("i = %d\n", i);
		if (i == 1048576)
			i = 0;
		while (i < SIZE)
		{
			if (FREE_LIST[i] == 0)
			{
				int j = i;
				int count = 0;
				while (j < SIZE && FREE_LIST[j] == 0)
				{
					count++;
					j++;
				}
				if (count >= size)
				{
					for (int k = i; k < i + size; k++)
					{
						FREE_LIST[k] = 1;
						HEAP[k] = 0;
					}
					masterList[allocated].startPos = &HEAP[i];
					masterList[allocated].size = size;
					allocated += 1;
					i += size;
					return &HEAP[i - size];
				}
				// i = j;
			}
			i++;
		}
	}

	// best fit
	if (allocArg == 2)
	{
		// printf("Allocating size of %d\n", size);

		int i = 0;
		int best = SIZE;
		int bestIndex = 0;
		while (i < SIZE)
		{
			if (FREE_LIST[i] == 0)
			{
				int j = i;
				int count = 0;
				while (j < SIZE && FREE_LIST[j] == 0)
				{
					count++;
					j++;
				}
				if (count >= size && count < best)
				{
					best = count;
					bestIndex = i;
				}
				i = j;
			}
			i++;
		}
		if (best != SIZE)
		{
			for (int k = bestIndex; k < bestIndex + size; k++)
			{
				FREE_LIST[k] = 1;
				HEAP[k] = 0;
			}
			masterList[allocated].startPos = &HEAP[bestIndex];
			masterList[allocated].size = size;
			allocated += 1;
			return &HEAP[bestIndex];
		}
	}

	return NULL;
}

void myfree(void *ptr)
{
	if (ptr == NULL)
		return;

	int i = 0;
	while (i < SIZE)
	{
		if (masterList[i].startPos == ptr)
		{
			for (int j = 0; j < SIZE; j++)
			{
				if (&HEAP[j] == ptr)
				{
					for (int k = j; k < j + masterList[i].size; k++)
					{
						FREE_LIST[k] = 0;
					}
					break;
				}
			}
			// printf("Removed %d bytes from memory\n", masterList[i].size);
			masterList[i].startPos = NULL;
			masterList[i].size = 0;
			// allocated -= 1;
			break;
		}
		i++;
	}
}

void *myrealloc(void *ptr, size_t size)
{
	if (size == 0 && ptr != NULL)
		myfree(ptr);
	if (ptr == NULL && size != 0)
		return mymalloc(size);
	if (ptr == NULL && size == 0)
		return NULL;

	// find region where ptr is located
	// reallocate memory in place if possible
	// if not, allocate new memory, copy data, and free old memory

	if (size % 8 != 0)
		size = size + (8 - (size % 8));

	// printf("Reallocing to size of %d\n", size);

	int i = 0;
	while (i < SIZE)
	{
		if (masterList[i].startPos == ptr)
		{
			// printf("FOUND PTR\n");
			// if new size is smaller than old size
			if (size < masterList[i].size)
			{
				for (int j = 0; j < SIZE; j++)
				{
					if (&HEAP[j] == ptr)
					{
						for (int k = j + size; k < j + masterList[i].size; k++)
						{
							FREE_LIST[k] = 0;
						}
						masterList[i].size = size;
						return ptr;
					}
				}
			}

			else if (size > masterList[i].size)
			{
				// location of ptr in heap
				int j = 0;
				while (&HEAP[j] != ptr)
					j++;

				// check if there is enough space after ptr
				int count = 0;
				int neededSpace = size - masterList[i].size;
				int k = j + masterList[i].size;
				while (k < SIZE && FREE_LIST[k] == 0)
				{
					count++;
					k++;
				}
				if (count >= neededSpace)
				{
					for (int k = j + masterList[i].size; k < j + size; k++)
					{
						FREE_LIST[k] = 1;
						HEAP[k] = 0;
					}
					masterList[i].size = size;
					return ptr;
				}
				else
				{
					// printf("Moving data to new location\n");
					// allocate new memory
					void *newPtr = mymalloc(size);
					if (newPtr == NULL)
						return NULL;
					// copy data
					for (int k = 0; k < masterList[i].size; k++)
					{
						((char *)newPtr)[k] = ((char *)ptr)[k];
					}
					// free old memory
					myfree(ptr);
					return newPtr;
				}
			}

			else
			{
				// Do nothing
			}
		}
		i++;
	}
	return NULL;
}

void mycleanup()
{
	allocArg = -1;
	free(masterList);
	for (int i = 0; i < SIZE; i++)
	{
		HEAP[i] = 0;
		FREE_LIST[i] = 0;
	}
	allocated = 0;
}

void print()
{
	printf("\nMaster List:\n");
	for (int i = 0; i < SIZE; i++)
	{
		if (masterList[i].startPos != NULL)
		{
			printf("Start Pos: %p, Size: %lu\n", masterList[i].startPos, masterList[i].size);
		}
	}

	printf("\nFree Blocks:\n");
	for (int i = 0; i < SIZE; i++)
	{
		if (FREE_LIST[i] == 0)
		{
			for (int j = i; j < SIZE; j++)
			{
				if (FREE_LIST[j] == 1)
				{
					printf("Block %d - %d\n", i, j - 1);
					i = j;
					break;
				}

				if (j == SIZE - 1)
				{
					printf("Block %d - %d\n", i, j);
					i = j;
					break;
				}
			}
		}
	}
}