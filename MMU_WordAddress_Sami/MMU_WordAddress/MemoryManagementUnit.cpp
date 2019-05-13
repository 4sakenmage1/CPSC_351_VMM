#include "MemoryManagementUnit.h"
#include "TLB.h"
#include "PCB.h"



string iFile = "addresses.txt";
Address addresses[1000];
MemoryManagementUnit MMU;


void MemoryManagementUnit::read()
{
	ifstream iFile("addresses.txt");
	if (iFile.is_open())
	{
		for (int i = 0; i < 1000; i++)
		{
			iFile >> addresses[i].address.value_;
		}
	}
	iFile.close();

	for (int i = 0; i < 1000; i++)
	{
		// shifting 8 bits to the right gives the 8 leftmost bits, the PageNumber
		unsigned int left_most_8bits = addresses[i].address.value_ >> 8;
		// masking the 8 right bits gives the 8 rightmost bits, the Offset
		unsigned int right_most_8bits = addresses[i].address.value_ & 0xFF;

		// we passed page_number and offset unsigned ints by reference so we can gain access to them outside of this function
		addresses[i].page.value_ = left_most_8bits;
		addresses[i].displacement.value_ = right_most_8bits;
	}

	for (int i = 0; i < 1000; i++)
	{
		tlbAccesses(addresses[i].page);
	}
		


};

void MemoryManagementUnit::displayDataValue(Address addresses)
{
	

	cout << +static_cast<char>(addresses.page.value_ * 256 + addresses.displacement.value_) << endl;
	
		// std::cout << i+1 << " value from backing_store_buffer: " << +static_cast<char>(backing_store_buffer[page_number * BYTE_SIZE_256 + offset]) << "\n\n";
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
		tlb.access(page);
		//Save to ram;

	}
};

void MemoryManagementUnit::tlbFaults(Word page)
{
	tlb_faults_++;
	pageAccesses(page); //Step3
};

void MemoryManagementUnit::pageAccesses(Word page)
{
	page_access_count_++;
	int HitOrMiss = page_table.pagehit(page);

	if(HitOrMiss == -1) //step 4
	{
		pageFaults(page);
		//call backing store
	}
	else
	{
		.findVictim(page_table.access(page)));
	}

};

void MemoryManagementUnit::pageFaults(Word page)
{
	page_in_faults_++;

};



void MemoryManagementUnit::clearTLB()
{
	for (int i = 0; i < 16; i--)
	{
		tlb.TLBEntries[i].page.value_ = -1;
		tlb.TLBEntries[i].frame.value_ = -1;
		tlb.TLBHitRatio[i] = -1;
	}
};