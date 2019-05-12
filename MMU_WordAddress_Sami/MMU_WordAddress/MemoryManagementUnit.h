#pragma once
#include <iostream>
#include <ctype.h>
#include "PageFault.h"
#include <fstream>
#include "Address.h"
#include "tlb.h"
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

	

	void clearTLB();

private:
	MemoryManagementUnit();

	int page_access_count_ = 0;
	int page_in_faults_ = 0;

	TLB tlb;
	int tlb_access_count_ = 0;
	int tlb_faults_ = 0;
	int tlb_hits_ = 0;


};