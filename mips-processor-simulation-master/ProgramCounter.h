#ifndef __PROGRAMCOUNTER_H__
#define __PROGRAMCOUNTER_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <string>
#include <iomanip>

using namespace std;

/*
 * This class implements the program counter component.
 */
class ProgramCounter {
	private:
		bitset<32> pc;

	public:
		/*
		 * Default constructor of the class. Sets the initial value for
		 * PC to 0x400000;
		 */
		ProgramCounter();
		/*
		 * Mutator method for the PC.
		 */
		void setPC(bitset<32> c);

		/*
		 * Accessor method for the PC.
		 */
		bitset<32> getPC();

		/*
		 * This method prints the PC to the given output file
		 */
		void printPC(string output);

};


#endif