#pragma once
#include <iostream>
#include "Word.h"
#include "MemoryManagementUnit.h"
using namespace std;


struct PageFault
{
	PageFault() {};
	Word pageNumber_;
	
};

// using standard exceptions
#include <iostream>
#include <exception>
using namespace std;

class PageFault : public exception
{
	virtual const char* what() const throw()
	{
		return "My exception happened";
	}
} PageFault;
