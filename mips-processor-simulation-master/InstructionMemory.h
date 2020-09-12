#ifndef __INSTRUCTIONMEMORY_H__
#define __INSTRUCTIONMEMORY_H__

#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include "ASMParser.h"
#include "Instruction.h"
#include "RegisterTable.h"
#include "Opcode.h"

using namespace std;


/* This class reads a program input file and converts all the
 * instructions into binary encoding
 */

class InstructionMemory{
	private:
		// Bitset array representing each 32 bit instructions
		// The max instruction count is 100
		bitset<32> instructions[100];
		string instruction_strings[100];

		// The total number of instructions 
		int numInstructions;


	public:
		// Default constructor of the class
		InstructionMemory();

		// Constructor of the class, with input file specified
		InstructionMemory(string input_file);

		// This method reads the instruction from the program input file 
		// Decodes them and places them into the instructions array
		// Also counts the number of instructions
		void readInstructions(string program_input);

		// This method gets the instruction indicated by the program counter parameter
		bitset<32> getInstruction(bitset<32> programCounter);

		// This method prints the instructions in the instruction memory in binary 
		// to the specified output file
		void printInstructionMemory(string output);

		// This method checks if all the instruction are run 
		// and the program needs to be terminated
		bool isFinished(bitset<32> programCounter);

		string getInstructionString(bitset<32> programCounter);




};

#endif
