// First In First Out Algorithm implementation

#include "FIFO.h"

// constructor
Pagereplacement::Pagereplacement() {};

// method finds the victim and deletes it
// victim is the first pagenumber put in for FIFO
Word Pagereplacement::findVictim()
{
	// first entry is always at the 0 index
	front = TLBEntries[0].page.value_;

	// scoot every entry over
	// this overwrites the first entry and so deleting it
	for (int i = 0; i < TLB_SIZE - 1; i++)
	{
		TLBEntries[i].page.value_ = TLBEntries[i + 1].page.value_;
		TLBEntries[i].frame.value_ = TLBEntries[i + 1].frame.value_;
	}

	// empty last slot
	TLBEntries[15].page.value_ = -1;
	TLBEntries[15].frame.value_ = -1;

	// return the victim
	return front;
}

// method finds empty slot and enters new entry
void Pagereplacement::replace(int position, Address tlb[], Word page)
{
	// input new entry into last slot
	tlb[15].page.value_ = page.value_;
	tlb[15].frame.value_ = ;// access pagetable for frame number
}
