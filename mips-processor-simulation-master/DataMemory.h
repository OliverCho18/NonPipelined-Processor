#ifndef __DATAMEMORY_H__
#define __DATAMEMORY_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <string>
#include <iomanip>

using namespace std;

/*Data memory class is responsible for storing values that
*are supposed to be in memory and simulate the behavior of
*data memory with given input and with respect to its control
*values memWrite and memRead.
*/


class DataMemory{
	private:
		bitset<32> memory[100];//memory table
		bitset<32> readData;//data to be written into memory
		bitset<1> memWrite;//variable which turns on and off the write to memory, controlled by control unit
		bitset<1> memRead;//variable which turns on and off the read of memory, controlled by contol unit
		long long offset;
		int memSize;

	public:
		DataMemory(); // default constructor
		DataMemory(string input);//The constructor of the class, initializes all the values in the memory with the values from the input file.

		void execute(bitset<32> address, bitset<32> writeData, string output);//This method simulates the behavior of the memory with given
		//parameters according to control values of the data memory.

		void printDataMemory(string output);//This method prints the content of the memory to the specified output file.

		void printControlValues(string output);//This method prints the memRead and memWrite control values to the given output file.

		bitset<32> getReadData();//Accessor method for readData.

		void setMemWrite(bitset<1> c);//Mutator method for control value memWrite.

		void setMemRead(bitset<1> c);//Mutator method for control value memRead.

		bitset<1> getMemRead(); // Accessor method for memRead

		bitset<1> getMemWrite(); // Accessor method for memWrite

		bitset<32> getMemValue(int i);//Accessor method for memory values, returns ith value on the memory.

};
#endif
