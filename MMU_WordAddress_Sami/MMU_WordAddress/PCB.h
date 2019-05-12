#pragma once
/*PCB.h*/
#ifndef PCB_H
#define PCB_H

#include "TLB.h"
#include <array>

const int PAGE_TABLE_SIZE = 256;
struct ProcessControlBlock {

private:
	PageTable ptbl;

} ProcessControlBlock;

class PageTable
{
public:
	PageTable();
private:
	std::array<int, PAGE_TABLE_SIZE> page_table;
};
#endif
