#include <iostream>
#include <bitset>
#include <fstream>
#include <string>


#define NUMBER_LOGICAL_ADDRESSES 1000
#define BYTE_SIZE_256 256

unsigned int binaryToDecimal(unsigned int binary_number);

void getPageNumberAndOffset(unsigned int address, unsigned int & page_number, unsigned int & offset);

void readLogicalAddresses(char * address_file, unsigned int logicalAddressArray[]);

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

    // array of 1000 logical addresses
    unsigned int logicalAddresses[NUMBER_LOGICAL_ADDRESSES];
    // pass logicalAddresses array by reference to be filled with 'logical' addresses from addresses.txt file
    readLogicalAddresses(argv[1], logicalAddresses);

    // these two unsigned ints are to be passed by reference to the 'getPageNumberAndOffset' function
    unsigned int frame_number, offset;

    for (int i = 0; i < 5; ++i)
    {
        // when this function finishes, both parameters contain updated pg number and offset values from the current logical address
        getPageNumberAndOffset(logicalAddresses[i], frame_number, offset);
        // we use these values to determine the physical address (which we get from the backing_store) 
        // by this equation: physical address = (frame number * byte size) + offset
        std::cout << i+1 << " value from backing_store_buffer: " << +static_cast<char>(backing_store_buffer[frame_number * BYTE_SIZE_256 + offset]) << "\n\n";
    }

    delete[] backing_store_buffer;
    
    return 0;
}

void readLogicalAddresses(char * address_file, unsigned int logicalAddressArray[])
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

unsigned int binaryToDecimal(unsigned int binary_number)
{
    int i = 0, decimal = 0;
    while(binary_number > 0)
    {
        if(binary_number % 10 == 1)
        {
            decimal += 1 << i; 
        }
        binary_number /= 10;
        i++;
    }
    return decimal;
}

void getPageNumberAndOffset(unsigned int address, unsigned int & page_number, unsigned int & offset)
{
    std::string binary = std::bitset<16>(address).to_string();
    std::cout << binary << "\n";

    // shifting 8 bits to the right gives the 8 leftmost bits
    unsigned int left_most_8bits = address >> 8;
    // masking the 8 right bits gives the 8 rightmost bits
    unsigned int right_most_8bits = address & 0xFF;

    std::string page_number_str = (std::bitset<8>(left_most_8bits)).to_string();
    std::string offset_str = (std::bitset<8>(right_most_8bits) ).to_string();

    std::cout << "left  most " << atoi( (page_number_str.c_str() )) << "\n";
    std::cout << "right most " << offset_str << "\n";

    unsigned int pgnumber = binaryToDecimal( atoi( (page_number_str.c_str() )));
    unsigned int off = binaryToDecimal( atoi( (offset_str.c_str() )));

    std::cout << "page number converted to decimal = " << pgnumber << " <- index of page table\n";
    std::cout << "offset converted to decimal = " << off << "\n";

    page_number = pgnumber;
    offset = off;

    // unsigned char uchar = '0';  // unsigned char occupies 1 byte
}