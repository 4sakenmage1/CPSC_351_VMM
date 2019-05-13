// First In First Out Algorithm implementation

#include "LRU.h"



// constructor
Pagereplacement::Pagereplacement() {};

// method finds the victim and deletes it
// victim is the entry with the smallest hit ratio put in
// returns the position of the entry
int Pagereplacement::findVictim(int TLBHitRatio[], Address tlb[])
{
	int position = 0;
	int leastRecentlyUsed;

	// loop through table to find least recently used entry
	for (int i = 0; i < TLB_SIZE; i++)
	{
		if (i == 0)
		{
			leastRecentlyUsed = TLBHitRatio[i];
		}
		if (TLBHitRatio[i] < leastRecentlyUsed)
		{
			leastRecentlyUsed = TLBHitRatio[i];
			position = i;
		}
	}

	// delete the entry
	tlb[position].page.value_ = -1;
	tlb[position].frame.value_ = -1;

	return position;
}

// method replaces the victim with entry
void Pagereplacement::replace(int position, Address tlb[], Word page)
{
	tlb[position].page.value_ = page.value_;
	tlb[position].frame.value_ = ;
}