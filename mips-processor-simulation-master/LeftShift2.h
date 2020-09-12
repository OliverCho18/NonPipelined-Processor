#ifndef __LEFTSHIFT2_H__
#define __LEFTSHIFT2_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <string>
#include <iomanip>

using namespace std;

/*
 * This class implements the left shift unit.
 */
class LeftShift2 {
	private:
		int componentNumber;
	public:
		/*
		 * Default constructor.
		 */ 
		LeftShift2();

		/*
		 * Constructor of the class.
		 */
		LeftShift2(int i);

		/*
		 * This method performs left shift operation on the given input.
		 */
		bitset<32> execute(bitset<32> input, string output);
};


#endif