#ifndef __PROCESSOR_H__
#define __PROCESSOR_H__

#include "RegisterFile.h"
#include "ALU.h"
#include "ALUControl.h"
#include "InstructionMemory.h"
#include "DataMemory.h"
#include "ControlUnit.h"
#include "MUX.h"
#include "ProgramCounter.h"
#include "SignExtend.h"
#include "LeftShift2.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <bitset>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;


/*
 * The driver file of the simulation. Initializes the objects, sets 
 * the instruction memory and executes all the 5-stages on the instructions 
 * until the program termination.
 */
class Processor {
	private:
		ProgramCounter programCounter;
		RegisterFile regFile;
		ALU alu1;
		ALU alu2;
		ALU alu3;
		ALUControl aluControl;
		InstructionMemory instMem;
		DataMemory dataMem;
		ControlUnit cUnit;
		MUX mux1;
		MUX mux2;
		MUX mux3;
		MUX mux4;
		MUX mux5;
		SignExtend signExtend;
		LeftShift2 shift_left_1;
		LeftShift2 shift_left_2;

		bitset<32> currentInst;
		map<string, string> config;

	public:
		/*
		 * The constructor of the class, reads the configuration file 
		 * and initializes all the components.
		 */
		Processor(string filename);

		/*
		 * The main function of the program. Until program termination, 
		 * in a while loop, this method fetches the instruction from 
		 * instruction memory with respect to current program counter 
		 * and executes it.
		 */
		void run();


		/*
		 * Accessor method for config map
		 */
		map<string,string> getConfig();


};

#endif