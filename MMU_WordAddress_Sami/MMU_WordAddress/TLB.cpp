#include "tlb.h"
#include "Address.h"
#include <iostream>
using namespace std;

// Constructor
TLB::TLB()
{
	// default values for variables

	
	for (int i = 0; i < 16; i++)
	{
		
		tlb[i].page.value_ =  -1 ;
		tlb[i].frame.value_ = -1 ;
		TLBHitRatio[i] = -1 ;
	}

	size = 0;
}

// method checks if the TLB is full
bool TLB::isFull()
{
	if (size == TLB_SIZE)
		return true;
	else
		return false;
}

// method checks if the pagenumber exists in the TLB
// if it exists, return the position of the pagenumber in the array
// returns -1 if it doesn't exist
int TLB::hit(Word pg)
{
	int position;

	for (int i = 0; i < TLB_SIZE; i++)
	{
		if (tlb[i].page.value_ == pg.value_)
		{
			return i;
		}
	}

	return -1;
}

// access method
// adds a new entry to the TLB if it doesn't exist in TLB
void TLB::access(Word pg)
{
	// if TLB not full
	if (!isFull)
	{
		// if entry does not exist in TLB, add it
		if (hit(pg) == -1)
		{
			for (int i = 0; i < TLB_SIZE; i++)
			{
				// first empty slot
				if (TLBPageNumber[i] == -1)
				{
					TLBPageNumber[i] = pg;
					TLBFrameNumber[i] = // PageTableEntry.frameNumber;
						TLBHitRatio[i] = 16;
					size++;
					break;
				}
			}
		}

		// if entry already exist in TLB, update hit ratio
		else
		{
			for (int i = 0; i < TLB_SIZE; i++)
			{
				// decrement hit ratio if position is not empty and is not an entry
				if (TLBHitRatio[i] != -1 && i != hit(pg))
				{
					TLBHitRatio[i]--;
				}
			}
			TLBHitRatio[hit(pg)] = 16;
		}
	}

	// if TLB is full, check if the pagenumber exists in the TLB
	else if (isFull)
	{
		// if the pagenumber doesn't exist in TLB
		// then use page replacement algorithm and update fault counter
		if (hit(pg) == -1)
		{
			tlbFaults(); // increase tlb_faults_ counter
			PageReplacementAlgorithm(); // call the replacement algorithm
		}

		// if page already exists in TLB
		// then do not add, but update hit ratio
		else
		{
			for (int i = 0; i < TLB_SIZE; i++)
			{
				if (TLBPageNumber[i] != pg)
				{
					TLBHitRatio[i]--;
				}
				else if (TLBPageNumber[i] == pg)
				{
					TLBHitRatio[i] = 16;
				}
			}
		}
	}
}