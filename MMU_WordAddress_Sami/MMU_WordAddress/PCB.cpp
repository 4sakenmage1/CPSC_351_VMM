// Page Table class implementation file

#include "PCB.h"
#include "PageFault.h"

using namespace std;

// Constructor
PageTable::PageTable()
{
	for (int i = 0; i < PAGE_TABLE_SIZE; i++)
	{
		page_table[i].page.value_ = -1;
		page_table[i].frame.value_ = -1;
	}
}

// method checks if pagenumber is in the page table
int PageTable::pagehit(Word pg)
{
	for (int i = 0; i < PAGE_TABLE_SIZE; i++)
	{
		if (page_table[i].page.value_ == pg.value_)
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
		return page_table[pagehit(pg)].frame;
	}

	// if there is no entry in page table
	else
	{
		pageFaults(); // call the pagefault method
		//fillTable(backingstore); // assuming pageFault will fill in a new page table. if not, then need another method to do so
	}
};
