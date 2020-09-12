#ifndef __CONTROLUNIT_H__
#define __CONTROLUNIT_H__

#include "RegisterFile.h"
#include "DataMemory.h"
#include "MUX.h"
#include "ALUControl.h"

#include <bitset>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>



using namespace std;

/*This class implements the control unit component which 
*is responsible for setting control values of other components to let them execute properly. 
*/

class ControlUnit{
	private:
		bitset<6> opcode;
		bitset<1> regDst;//regDst control value
		bitset<1> jump;//jump control value
		bitset<1> branch;//branch control value
		bitset<1> memRead;//memRead control value
		bitset<1> memToReg;//memToReg control value
		bitset<1> aluOp0;//aluOp0 control value
		bitset<1> aluOp1;//aluOp1 control value
		bitset<1> memWrite;//memWrite control value
		bitset<1> aluSrc;//aluSrc control value
		bitset<1> regWrite;//regWrite control value
		RegisterFile controlRegFile;//control instance of RegisterFile
		DataMemory controlDataMem;// control instance of DataMemory
		ALUControl controlAluControl;//control instance of ALUControl
		MUX controlMux1;//control instance of Mux1
		MUX controlMux2;//control instance of Mux2
		MUX controlMux3;//control instance of Mux3
		MUX controlMux4;//control instance of Mux4
		MUX controlMux5;//control instance of Mux5
	public:
		ControlUnit(); // default constructor
		ControlUnit(RegisterFile &regFile, DataMemory &dataMem, MUX &mux1, MUX &mux2, MUX &mux3, MUX &mux4, MUX &mux5, ALUControl &aluControl);//Base constructor for ControlUnit


		void updateControlValues(bitset<6> opcode, RegisterFile &regFile, DataMemory &dataMem, MUX &mux1, MUX &mux2, MUX &mux3, MUX &mux4, MUX &mux5, ALUControl &aluControl);//This function will edit the field values (and corresponding control 

		void printControlValues(string outputFile);//This method prints the control values to the given output file.

		bitset<1> getRegDst();//This function gets regDst

		bitset<1> getJump();//This function gets jump

		bitset<1> getBranch();//This function gets branch

		bitset<1> getMemRead();//This function gets memRead

		bitset<1> getMemToReg();//This function gets memToReg

		bitset<1> getAluOp0();//This function gets aluOp0

		bitset<1> getAluOp1();//This function gets aluOp1

		bitset<1> getMemWrite();//This function gets memWrite

		bitset<1> getAluSrc();//This function gets aluSrc

		bitset<1> getRegWrite();//This function gets regWrite


};
#endif
