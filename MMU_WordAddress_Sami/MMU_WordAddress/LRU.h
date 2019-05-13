#pragma once

#ifndef LRU_H
#define LRU_H

#include "MemoryManagementUnit.h"

class Pagereplacement
{
public:
	int findVictim(int TLBHitRatio[], Address tlb[]);
	Pagereplacement() {};
	void replace(int i, Address tlb[], Word page);
};

#endif