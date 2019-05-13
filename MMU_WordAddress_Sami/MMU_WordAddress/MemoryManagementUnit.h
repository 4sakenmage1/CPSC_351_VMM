#pragma once
#include <iostream>
#include <fstream>
#include "PageFault.h"
#include "Address.h"
#include "TLB.h"
#include "PCB.h"


using namespace std;


class MemoryManagementUnit
{
	
public:
	MemoryManagementUnit()
	{
	};
	MemoryManagementUnit& instance() {};
	
	MemoryManagementUnit& operator= (MemoryManagementUnit& y) {};

	void read();
	void displayDataValue(Address addresses);

	void pageAccesses(Word page);
	void pageFaults(Word page);
	
	void tlbAccesses(Word page);
	void tlbFaults(Word page);

	PageTable page_table;
	

	void clearTLB();

private:
	int page_access_count_ = 0;
	int page_in_faults_ = 0;


	TLB tlb;
	int tlb_access_count_ = 0;
	int tlb_faults_ = 0;
	int tlb_hits_ = 0;


};