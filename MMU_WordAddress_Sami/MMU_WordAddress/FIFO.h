#pragma once

// First In First Out Algorithm header
// inherits the Page Replacement Algorithm Class
#include "MemoryManagementUnit.h"

#ifndef FIFO_H
#define FIFO_H

struct Pagereplacement 
{
public:
	// method finds the victim
	Word findVictim();

	// constructor
	Pagereplacement() {};

	// method replaces the victim with new entry
	void replace(int position, Address tlb[], Word page);
};

#endif