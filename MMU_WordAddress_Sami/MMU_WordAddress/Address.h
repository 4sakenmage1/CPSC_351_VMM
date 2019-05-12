#pragma once
#include "Word.h"


struct Address
{
public:
	Word address;
	Word displacement;
	Word frame;
	Word page;


};