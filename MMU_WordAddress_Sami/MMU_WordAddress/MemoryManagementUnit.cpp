#include "MemoryManagementUnit.h"
#include "MemoryManager.h"
#include "backingStore.h"
#include "TLB.h"
#include "ram.h"
#include <iostream>

// To perform the address translations
void getPageNumberAndOffset(int address, int & page_number, int & offset)
{
    // shifting 8 bits to the right gives the 8 leftmost bits, the PageNumber
    unsigned int left_most_8bits = address >> 8;
    // masking the 8 right bits gives the 8 rightmost bits, the Offset
    unsigned int right_most_8bits = address & 0xFF;
    page_number = left_most_8bits;
    offset = right_most_8bits;
}

Address MemoryManagementUnit::read(int logical_address)
{
    // pass in the logical address received from the CPU, and separate it into its two constituent parts
    // the page number and offset
    int page_number, offset;
    getPageNumberAndOffset(logical_address, page_number, offset);

    // Assign the page number and offset to the passed in Page.
    Address page;
    Word word_pg, word_offset;
    word_pg.value_     = page_number;
    word_offset.value_ = offset;
    page.address       = word_pg;
    page.displacement  = word_offset;

    return page;
}

void MemoryManagementUnit::displayDataValue(Address address)
{
    // cout the data value
}

void MemoryManagementUnit::tlbAccesses(Word page)
{
    Word temp_Display;
	tlb_access_count_++;
	bool HitOrMiss = tlb.hit(page); // Step 1

	if (HitOrMiss == -1) // Miss	//Step2
	{
		tlbFaults(page);
	}
	else// hit //Step 2
	{
		tlb_hits_++;
	    int frame_number = tlb.access(page);
		//Save to ram;
        physical_memory.memory.at(frame_number).physical_address = page.value_;
        physical_memory.memory.at(frame_number).frame_number = frame_number;
        
        // Get the data value stored from the associated frame in physical memory

	}
}

void MemoryManagementUnit::tlbFaults(Word page)
{
    tlb_faults_++;
	pageAccesses(page);
}

void MemoryManagementUnit::pageAccesses(Word page)
{
    page_access_count_++;
	bool HitOrMiss = ProcessControlBlock::page_table.hit(page);

	if(HitOrMiss == -1) //step 4
	{
		pageFaults(page);
        // access the backing_store

	}
	else
	{
		ProcessControlBlock::PCB.access(page);

        int frame_number = PageTable.access(page);
		//Save to ram;
        physical_memory.memory.at(frame_number).physical_address = page.value_;
        physical_memory.memory.at(frame_number).frame_number = frame_number;
	}
}

void MemoryManagementUnit::pageFaults(Address page)
{
    page_in_faults_++;
    // get value from backing store
    int data_value = b.read(page.address.value_, page.displacement.value_);

    // Get free frame from freeFrameList
    
    int frame_number = mm.getFrameNumber();
    // insert page

    //Save to ram;
    physical_memory.memory.at(frame_number).data_value = data_value;
    
    PCB.ptbl.page_table.at


}

void MemoryManagementUnit::clearTLB()
{
    for (int i = 0; i < 16; i--)
	{
		tlb.TLBEntries[i].page.value_ = -1;
		tlb.TLBEntries[i].frame.value_ = -1;
		tlb.TLBHitRatio[i] = -1;
	}
}


MemoryManagementUnit::MemoryManagementUnit()
{
    RAM physical_memory;
    BackingStore b;
    MemoryManager mm;
    struct ProcessControlBlock PCB;
}
