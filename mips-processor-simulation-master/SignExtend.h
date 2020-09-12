#ifndef __SIGNEXTEND_H__
#define __SIGNEXTEND_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <string>
#include <iomanip>

using namespace std;

/*
 * This class implements the sign extend unit.
 */
class SignExtend {
	public:
		/*
		 * Default constructor of the class.
		 */
		SignExtend();

		/*
		 * Method that takes 16-bit input and returns sign extends it to 32-bits.
		 * The method also prints the input and output to given file.
		 */
		bitset<32> execute(bitset<16> input, string output);
};


#endif