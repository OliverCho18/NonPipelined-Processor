#ifndef __ALU_H__
#define __ALU_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <string>
#include <iomanip>

using namespace std;

/*
 * This class implements the main arithmetic & logic operation 
 * component of the simulation. 
 */
class ALU {
	private: 
		bitset<32> ALUresult;
		bitset<4> ALUcontrolLine;
		bitset<1> zero;
		int componentNumber;
		
	public:
		/*
		 * Default constructor for ALU class. Sets ALUresult to 0.
		 */
		ALU();

		/*
		 * Constructor for ALU class. Sets ALUresult to 0. Sets component number to
		 * given integer value.
		 */
		ALU(int i);

		/*
		 * This function will simulate an ALU applied to the given information
		 * in data1 and data 2. Also the if ALUcontrol holds a value, the 
		 * ALU will apply what the ALUcontrol function says to do on data1 data 2.
		 */
		void execute(bitset<32> data1, bitset<32> data2, string output);

		/*
		 * Accessor method for ALUresult
		 */
		bitset<32> getALUresult();

		/*
		 * Mutator method for ALUcontrolLine
		 */
		void setALUcontrolLine(bitset<4> c);

		/*
		 * Accessor method for ALUcontrolLine
		 */
		bitset<4> getALUcontrolLine();

		/*
		 * Accessor method for zero
		 */
		bitset<1> getZero();
};

#endif