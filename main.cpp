#include <iostream>
#include <bitset>
#include <fstream>
#include <string>

#define NUMBER_LOGICAL_ADDRESSES 1000
#define BYTE_SIZE_256 256
#define PAGE_TABLE_SIZE_256 256
#define TLB_BUFFER_SIZE_16 16

void getPageNumberAndOffset(u_int16_t address, u_int16_t & page_number, u_int16_t & offset);

void readLogicalAddresses(char * address_file, u_int16_t logicalAddressArray[]);

class PageTable
{
    public:
    private:
        uint16_t table[PAGE_TABLE_SIZE_256];
};

class MMU
{
    public:
        MMU()
        {
            for(int i = 0; i < TLB_BUFFER_SIZE_16; ++i){
                tlb_buffer[i] = -1;
            }
        }

        bool checkTLB(uint16_t page_number)
        {
            bool entryFound = false;
            uint16_t i = 0;

            while(i < TLB_BUFFER_SIZE_16 && !entryFound )
            {
                if(tlb_buffer[i] == page_number)
                    entryFound = true;
                else if(tlb_buffer[i] == UNINITIALIZED) {
                    // this simulates a TLB miss;
                    // Since if we find a -1, then we must have checked all the previous initialized pages with no hits.
                    // The TLB must not contain the page_number, and in fact the TLB still has uninitialized entries.
                    // And so we simulate a TLB miss and we have to look up the value of the page_number from the page table
                    look_up_entry_from_page_table(i, page_number);
                }
                ++i;
            }
            // if this returns false, then we will have to replace one of the pages 
            // according to either the FIFO or LRU page-replacement algorithms
            return entryFound;
        }

        void look_up_entry_from_page_table(uint16_t index, uint16_t page_number)
        {
            tlb_buffer[index] = page_number;
        }

        void replaceEntry()
        {
            // this is where we use a FIFO or LRU algorithm to replace one of the entries in the full TLB
        }

    private:
        u_int16_t tlb_buffer[TLB_BUFFER_SIZE_16];
        const int UNINITIALIZED = -1;
};

class BackingStore
{
    public:
    private:
    char * backing_store_buffer;

};

int main(int argc, char **argv) {

    char * backing_store_buffer;

    std::ifstream is("BACKING_STORE.bin", std::ifstream::binary);
    if(is)
    {
        is.seekg(0, is.end);
        int length = is.tellg();
        is.seekg(0, is.beg);

        backing_store_buffer = new char[length];
        
        is.read(backing_store_buffer,length);

        is.close();
    }
    else
    {
        std::cout << "Error opening BACKING_STORE.bin.  Exiting.\n";
        return 1;
    }
    
    MMU memory_management_unit;

    // array of 1000 logical addresses
    u_int16_t logicalAddresses[NUMBER_LOGICAL_ADDRESSES];
    // pass logicalAddresses array by reference to be filled with 'logical' addresses from addresses.txt file
    readLogicalAddresses(argv[1], logicalAddresses);

    // these two u_int16_ts (unsigned ints) are to be passed by reference to the 'getPageNumberAndOffset' function
    u_int16_t page_number, offset;

    for (int i = 0; i < 10; ++i)
    {
        // when this function finishes, both parameters contain updated pg number and offset values from the current logical address
        getPageNumberAndOffset(logicalAddresses[i], page_number, offset);

        // the next step right here is to check the page_number against the TLB
        std::cout << "checking TLB: for pg_number: " << page_number << "\n" 
        << "entry " << (memory_management_unit.checkTLB(page_number) ? " found!\n" : "not found.\n");
        // if there is a TLB hit, we then use the frame number * byte_size + offset to access the value from physical memory

        // if there is a TLB miss, we then have to look up the frame_number from the page table


        // we use these values to determine the physical address (which we get from the backing_store) 
        // by this equation: physical address = (frame number * byte size) + offset
        // std::cout << i+1 << " value from backing_store_buffer: " << +static_cast<char>(backing_store_buffer[page_number * BYTE_SIZE_256 + offset]) << "\n\n";
    }

    delete[] backing_store_buffer;
    
    return 0;
}

void readLogicalAddresses(char * address_file, u_int16_t logicalAddressArray[])
{
    std::ifstream ifs(address_file);
    int count = 0;
    if(ifs.is_open())
    {
        char c;
        std::string number;
        while(ifs.get(c))
        {
            if(c == '\n')
            {
                logicalAddressArray[count] = atoi(number.c_str());
                number = "";
                ++count;
            }
            // std::cout << c;
            number += c;

            
        }
        ifs.close();
    }
    std::cout << "count : "  << count << "\n";
}

void getPageNumberAndOffset(u_int16_t address, u_int16_t & page_number, u_int16_t & offset)
{
    // these two lines are just for visualization purposes; they can be commented out and the VMM is unaffected
    // std::string binary = std::bitset<16>(address).to_string();
    // std::cout << binary << "\n";

    // shifting 8 bits to the right gives the 8 leftmost bits, the PageNumber
    unsigned int left_most_8bits = address >> 8;
    // masking the 8 right bits gives the 8 rightmost bits, the Offset
    unsigned int right_most_8bits = address & 0xFF;

    std::cout << "left_most_8bits = page number: " << left_most_8bits << " <- index of page table\n";
    std::cout << "right_most_8bits = offset: " << right_most_8bits << "\n";

    // we passed page_number and offset unsigned ints by reference so we can gain access to them outside of this function
    page_number = left_most_8bits;
    offset = right_most_8bits;
}