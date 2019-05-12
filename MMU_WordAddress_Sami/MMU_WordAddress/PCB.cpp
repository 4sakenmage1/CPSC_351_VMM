// Page Table class implementation file

#include "PCB.h"
using namespace std;

// Constructor
PageTable::PageTable()
{
	for (int i = 0; i < PAGE_TABLE_SIZE; i++)
	{
		page_table[i].page.value = -1;
		page_table[i].frame.value = -1;
	}
}

// method checks if pagenumber is in the page table
int PageTable::pagehit(Word pg)
{
	for (int i = 0; i < PAGE_TABLE_SIZE; i++)
	{
		if (pagetable[i].page.value == pg.value_)
		{
			return i;
		}
	}

	return -1;
}

/// method searches table for pagenumber
// returns the framenumber
Word PageTable::access(Word pg)
{
	// if there is a hit
	if (pagehit(pg) != -1)
	{
		// return framenumber
		return pagetable[pagehit(pg)].frame.value;
	}

	// if there is no entry in page table
	else
	{
		pageFaults(); // call the pagefault method
		//fillTable(backingstore); // assuming pageFault will fill in a new page table. if not, then need another method to do so
	}
}
/ Page Table header /

// additional variables needed to update
// pagefaults
// page_accesscount

#ifndef PGT_H
#define PGT_H

#define PAGE_TABLE_SIZE 256 // size of the page table

using namespace std;

class PageTable
{
public:
	// constructor
	PageTable();

	// method searches table for pagenumber
	// returns the framenumber
	Word access(Word pg);

	// method checks the page table for the pagenumber
	bool pagehit(Word pg);

	// method fills in the page table
	// void fillTable(backingstore); ???

private:
	Address page_table[PAGE_TABLE_SIZE];
};
#endif