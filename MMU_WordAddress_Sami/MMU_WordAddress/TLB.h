#pragma once
// TLB header file

// additional variables needed to update
// tlb_faults_
// tlb_access_count_
#include "MemoryManagementUnit.h"
#include "LRU.h"
#include "FIFO.h"

#ifndef TLB_H
#define TLB_H

#define TLB_SIZE 16 // size of the TLB

class TLB
{
private:

	int size; // number of entries in TLB
	

public:
	// constructor
	TLB();
	bool isFull();
	int hit(Word pg);
	void access(Word pg);
	Address TLBEntries[TLB_SIZE];  // array to hold the page numbers in the TLB
	int TLBHitRatio[TLB_SIZE]; // array to hold the hit ratios in TLB
	void pageReplacementAlgorithm(Word page);

};

#endif