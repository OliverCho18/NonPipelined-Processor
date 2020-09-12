#ifndef __MUX_H__
#define __MUX_H__


#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <vector>

using namespace std;

 /*
  *
  *	This class act as a multiplexor and returns the second input
  * if the control value is 1 and vice vers*
  */
  class MUX{


 private:
 	int componentNumber;
 	bitset<1> controlValue;
 	bitset<32> result;


 public:
 	// Default constructor
 	MUX();

 	// Constructor of MUX Class
 	MUX(int i);

 	// This method chooses one input from two parameters based on the control value
 	// and set the variable result to that input
 	void execute(bitset<32> input1, bitset<32> input2, string output);

 	// This method set the control value
 	void setControl(bitset<1> control);

 	// This method returns the result
 	bitset<32> getResult();




 };

#endif
