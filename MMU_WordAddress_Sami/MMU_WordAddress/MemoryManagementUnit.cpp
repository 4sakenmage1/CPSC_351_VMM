#include "MemoryManagementUnit.h"
#include "TLB.h"

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
		tlbAccesses(addresses[i]);
	}
		


};

void MemoryManagementUnit::displayDataValue(Address addresses)
{
	

	cout << +static_cast<char>(addresses.page.value_ * 256 + addresses.displacement.value_) << endl;
	
		// std::cout << i+1 << " value from backing_store_buffer: " << +static_cast<char>(backing_store_buffer[page_number * BYTE_SIZE_256 + offset]) << "\n\n";
}

 void MemoryManagementUnit::tlbAccesses(Address addresses)
{
	 Word temp_Display;
	tlb_access_count_++;
	bool HitOrMiss = tlb.hit(addresses.page); // Step 1

	if (HitOrMiss == -1) // Miss	//Step2
	{
		tlbFaults(addresses); 
	}
	else// hit //Step 2
	{
		tlb_hits_++;
		tlb.access(addresses.page);
		//Save to ram;
		displayDataValue(addresses);

	}
};

void MemoryManagementUnit::tlbFaults(Address addresses)
{
	tlb_faults_++;
	pageAccesses(addresses); //Step3
	
};

void MemoryManagementUnit::pageAccesses(Address addresses)
{
	page_access_count_++;
	bool HitOrMiss = ProcessControlBlock::page_table.hit(addresses);

	if(HitOrMiss == -1) //step 4
	{
		pageFaults(addresses);
	}
	else
	{
		ProcessControlBlock::PCB.access(addresses);
	}

};

void MemoryManagementUnit::pageFaults(Address addresses)
{
	page_in_faults_++;

};



void MemoryManagementUnit::clearTLB(TLB& tlb)
{
	for (int i = 15; i >= 0; i--)
	{
		
	}
};