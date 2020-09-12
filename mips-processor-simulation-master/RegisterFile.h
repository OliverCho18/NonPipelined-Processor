#ifndef __REGISTERFILE_H__
#define __REGISTERFILE_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <string>
#include <iomanip>

using namespace std;

/*
 * Register file class stores the registers, and simulates the behaviour of 
 * an actual register file with given input, storing the output readData to its fields. 
 * It’s operation is controlled by regWrite control value.
 */

class RegisterFile {
	private:
		bitset<32> readData1;
		bitset<32> readData2;
		bitset<1> regWrite;
		bitset<32> registers[32];

	public:
		/*
		 * Default constructor
		 */
		RegisterFile();

		/* 
		 * The constructor of the class, initializes all the registers with 
		 * the values from the input file.
		 */
		RegisterFile(string input);

		/*
		 * This method simulates the behavior of register file with given 
		 * parameters according to control value of register file (regWrite).
		 */
		void execute(bitset<5> readRegister1, bitset<5> readRegister2,
					 bitset<5> writeRegister, bitset<32> writeData, bool writeStage, string output);

		/*
		 * This method prints the content of the registers in the register 
		 * file to the specified output file.
		 */
		void printRegisterFile(string output);

		/*
		 * This method prints the read data fields and the regWrite control 
		 * value to the given output file.
		 */
		void printDataAndControlValues(string output);

		/*
		 * Accessor method for readData1.
		 */
		bitset<32> getReadData1();

		/*
		 * Accessor method for readData2.
		 */
		bitset<32> getReadData2();

		/*
		 * Acessor method for registers, returns the register numbered i.
		 */
		bitset<32> getRegister(int i);

		/*
		 * Mutator method for regWrite.
		 */
		void setRegWrite(bitset<1> c);

		/*
		 * Accessor method for regWrite.
		 */
		bitset<1> getRegWrite();
}; 


#endif