
#include <iostream>
#include <ctype.h>
#include "PageFault.h"
#include <fstream>
#include "Address.h"
#include "tlb.h"
#include "ram.h"
#include "PCB.h"
#include "backingStore.h"
#include "MemoryManager.h"
#include "PCB.h"

using namespace std;

class MemoryManagementUnit
{
    public:
        MemoryManagementUnit();

        Address read(int logical_address);
        void displayDataValue(Address address);
        void pageAccesses(Word page);
        void pageFaults(Address page);
        void tlbAccesses(Word page);
        void tlbFaults(Word page);

        void clearTLB();
    
    private:
        
        int page_access_count_ = 0;
        int page_in_faults_ = 0;

        TLB tlb;
        RAM physical_memory;
        BackingStore b;
        MemoryManager mm;
        struct ProcessControlBlock PCB;
        int tlb_access_count_ = 0;
        int tlb_faults_ = 0;
        int tlb_hits_ = 0;

};
