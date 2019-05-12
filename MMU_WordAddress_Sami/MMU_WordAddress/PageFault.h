#pragma once
#include <iostream>
#include "Word.h"
using namespace std;

struct PageFault
{
	Word pageNumber_;
	string& arg;
};