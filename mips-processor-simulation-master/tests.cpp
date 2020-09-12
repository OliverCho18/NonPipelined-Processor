#include "Processor.h"
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


void testRegFile()
{
	cout << "#######################################" << endl;
	cout << "######    TESTING REGISTERFILE  #######" << endl;
	cout << "#######################################" << endl;
	cout << "\tTesting constructor with 'register1.memory' " << endl;
	RegisterFile regFile1("register1.memory");
	regFile1.printRegisterFile("");
	cout << "#######################################" << endl;
	cout << "\tTesting read operation with 1st register" << endl;
	regFile1.execute(bitset<5>(15), bitset<5>(-1), bitset<5>(-1), bitset<32>(-1), false, "");
	cout << "readData1: " << hex << setfill('0') << setw(8)  << regFile1.getReadData1().to_ulong() << endl;
	cout << "register[15]: " << hex << setfill('0') << setw(8)  << regFile1.getRegister(15).to_ulong() << endl;
	cout << "readData2: " << hex << setfill('0') << setw(8)  << regFile1.getReadData2().to_ulong() << "\t Expected:" << hex << setfill('0') << setw(8) << 0 << endl;

	cout << "#######################################" << endl;

	cout << "\tTesting read operation with 2nd register" << endl;

	regFile1.execute(bitset<5>(-1),bitset<5>(7),bitset<5>(-1), bitset<32>(-1), false,"");
	cout << "readData2: " << hex << setfill('0') << setw(8)  << regFile1.getReadData2().to_ulong() << endl;
	cout << "register[7]: " << hex << setfill('0') << setw(8)  << regFile1.getRegister(7).to_ulong() << endl;
	cout << "readData1: " << hex << setfill('0') << setw(8)  << regFile1.getReadData1().to_ulong() << "\t Expected:" << hex << setfill('0') << setw(8) << 0 << endl;

	cout << "#######################################" << endl;

	cout << "\tTesting read operation with both registers" << endl;

	regFile1.execute(bitset<5>(20), bitset<5>(29), bitset<5>(-1), bitset<32>(-1),false, "");

	cout << "readData1: " << hex  << setfill('0') << setw(8) << regFile1.getReadData1().to_ulong() << endl;
	cout << "register[20]: " << hex << setfill('0') << setw(8)  << regFile1.getRegister(20).to_ulong() << endl;

	cout << "readData2: " << hex << setfill('0') << setw(8)  << regFile1.getReadData2().to_ulong() << endl;
	cout << "register[29]: " << hex << setfill('0') << setw(8)  << regFile1.getRegister(29).to_ulong() << endl;

	cout << "#######################################" << endl;
	cout << "\tTesting write operation" << endl;

	regFile1.setRegWrite(bitset<1>(1));
	regFile1.execute(bitset<5>(-1), bitset<5>(-1), bitset<5>(10), bitset<32>(121), true, "");
	cout << "register[10]: " << hex << setfill('0') << setw(8)  << regFile1.getRegister(10).to_ulong() << "\tExpected:" << hex << setfill('0') << setw(8)  << 121 << endl;

	regFile1.execute(bitset<5>(-1), bitset<5>(-1), bitset<5>(27), bitset<32>(3278492),true, "");
	cout << "register[27]: " << hex << setfill('0') << setw(8)  << regFile1.getRegister(27).to_ulong() << "\tExpected:" << hex << setfill('0') << setw(8)  << 3278492 << endl;

	regFile1.execute(bitset<5>(-1), bitset<5>(-1), bitset<5>(0), bitset<32>(812389721),true, "");
	cout << "register[0]: " <<  hex << setfill('0') << setw(8)  << regFile1.getRegister(0).to_ulong() << "\tExpected:" << hex << setfill('0') << setw(8)  << 812389721 << endl;


	cout << "#######################################" << endl;
	cout << "\tTesting printing control and data values" << endl;
	regFile1.printDataAndControlValues("");

	regFile1.setRegWrite(bitset<1>(0));
	regFile1.execute(bitset<5>(20), bitset<5>(29), bitset<5>(-1), bitset<32>(-1),false, "");
	regFile1.printDataAndControlValues("");

	cout << "#######################################" << endl;
	cout << "\tTesting reg file output to file" << endl;
	regFile1.printRegisterFile("regFileOut.test");
	regFile1.printDataAndControlValues("regFileOut.test");
}

void testALU()
{
	cout << "#######################################" << endl;
	cout << "##########    TESTING ALU   ###########" << endl;
	cout << "#######################################" << endl;

	ALU alu1(1);

	cout << "\tTesting constructor" << endl;
	cout << "ALU result: " << alu1.getALUresult() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine().to_string() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;

	cout << "#######################################" << endl;

	bitset<4> ANDcontrol("0000");
	bitset<4> ORcontrol("0001");
	bitset<4> ADDcontrol("0010");
	bitset<4> SUBcontrol("0110");
	bitset<4> SLTcontrol("0111");
	bitset<4> NORcontrol("1100");

	bitset<32> b1("101101");
	bitset<32> b2("010100011");
	bitset<32> b3(-5);
	bitset<32> b4(10);
	bitset<32> b5(5);

	cout << "\tTesting execute with AND" << endl;
	alu1.setALUcontrolLine(ANDcontrol);
	alu1.execute(b1,b2, "");
	cout << "data1: " << b1 << endl;
	cout << "data2: " << b2 << endl;
	cout << "ALU result: " << alu1.getALUresult() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine().to_string() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;

	cout << "#######################################" << endl;

	cout << "\tTesting execute with OR" << endl;
	alu1.setALUcontrolLine(ORcontrol);
	alu1.execute(b1,b2, "");
	cout << "data1: " << b1 << endl;
	cout << "data2: " << b2 << endl;
	cout << "ALU result: " << alu1.getALUresult() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine().to_string() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;


	cout << "#######################################" << endl;

	cout << "\tTesting execute with ADD" << endl;
	alu1.setALUcontrolLine(ADDcontrol);
	alu1.execute(b1,b2, "");
	cout << "data1: " << b1 << endl;
	cout << "data2: " << b2 << endl;
	cout << "ALU result: " << alu1.getALUresult() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine().to_string() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;
	cout << endl << endl;

	alu1.execute(b3,b4, "");
	cout << "data1: " << (int) b3.to_ulong() << endl;
	cout << "data2: " << (int) b4.to_ulong() << endl;
	cout << "ALU result: " << (int)  alu1.getALUresult().to_ulong() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;
	cout << endl << endl;


	alu1.execute(b3,b5, "");
	cout << "data1: " << (int) b3.to_ulong() << endl;
	cout << "data2: " << (int) b5.to_ulong() << endl;
	cout << "ALU result: " << (int) alu1.getALUresult().to_ulong() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;
	cout << endl << endl;


	cout << "#######################################" << endl;

	cout << "\tTesting execute with SUB" << endl;
	alu1.setALUcontrolLine(SUBcontrol);
	alu1.execute(b1,b2, "");
	cout << "data1: " << b1 << endl;
	cout << "data2: " << b2 << endl;
	cout << "ALU result: " << alu1.getALUresult() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine().to_string() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;
	cout << endl << endl;

	alu1.execute(b3,b4, "");
	cout << "data1: " << (int) b3.to_ulong() << endl;
	cout << "data2: " << (int) b4.to_ulong() << endl;
	cout << "ALU result: " << (int)  alu1.getALUresult().to_ulong() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;
	cout << endl << endl;


	alu1.execute(b3,b3, "");
	cout << "data1: " << (int) b3.to_ulong() << endl;
	cout << "data2: " << (int) b3.to_ulong() << endl;
	cout << "ALU result: " << (int) alu1.getALUresult().to_ulong() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;
	cout << endl << endl;


	cout << "#######################################" << endl;

	cout << "\tTesting execute with SLT" << endl;
	alu1.setALUcontrolLine(SLTcontrol);
	alu1.execute(b1,b2, "");
	cout << "data1: " << b1 << endl;
	cout << "data2: " << b2 << endl;
	cout << "ALU result: " << alu1.getALUresult() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine().to_string() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;
	cout << endl << endl;

	alu1.execute(b3,b4, "");
	cout << "data1: " << (int) b3.to_ulong() << endl;
	cout << "data2: " << (int) b4.to_ulong() << endl;
	cout << "ALU result: " << (int)  alu1.getALUresult().to_ulong() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;
	cout << endl << endl;

	alu1.execute(b4,b4, "");
	cout << "data1: " << (int) b4.to_ulong() << endl;
	cout << "data2: " << (int) b4.to_ulong() << endl;
	cout << "ALU result: " << (int)  alu1.getALUresult().to_ulong() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;
	cout << endl << endl;


	cout << "#######################################" << endl;

	cout << "\tTesting execute with NOR" << endl;
	alu1.setALUcontrolLine(NORcontrol);
	alu1.execute(b1,b2, "");
	cout << "data1: " << b1 << endl;
	cout << "data2: " << b2 << endl;
	cout << "ALU result: " << alu1.getALUresult() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine().to_string() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;

}

void testALUControl()
{
	cout << "#######################################" << endl;
	cout << "#######    TESTING ALUControl  ########" << endl;
	cout << "#######################################" << endl;

	ALUControl aluControl1;

	cout << "\tTesting constructor" << endl;
	cout << "ALUOp: " << aluControl1.getALUOp() << endl;
	cout << "opcode: " << aluControl1.getOpcode() << endl;

	cout << "#######################################" << endl;
	cout << "\tTesting setALUControl" << endl;
	ALU alu1(1);


	aluControl1.setALUOp(00);
	aluControl1.setOpcode(bitset<6>("000000"));
	cout << "ALUOp: " << aluControl1.getALUOp() << endl;
	cout << "opcode: " << aluControl1.getOpcode() << endl;
	aluControl1.setALUControl(alu1);
	cout << "ALU control line: " << alu1.getALUcontrolLine().to_string() << endl << endl;

	aluControl1.setALUOp(01);
	aluControl1.setOpcode(bitset<6>("000000"));
	cout << "ALUOp: " << aluControl1.getALUOp() << endl;
	cout << "opcode: " << aluControl1.getOpcode() << endl;
	aluControl1.setALUControl(alu1);
	cout << "ALU control line: " << alu1.getALUcontrolLine().to_string() << endl << endl;


	aluControl1.setALUOp(10);
	aluControl1.setOpcode(bitset<6>("100000"));
	cout << "ALUOp: " << aluControl1.getALUOp() << endl;
	cout << "opcode: " << aluControl1.getOpcode() << endl;
	aluControl1.setALUControl(alu1);
	cout << "ALU control line: " << alu1.getALUcontrolLine().to_string() << endl << endl;

	aluControl1.setALUOp(10);
	aluControl1.setOpcode(bitset<6>("100010"));
	cout << "ALUOp: " << aluControl1.getALUOp() << endl;
	cout << "opcode: " << aluControl1.getOpcode() << endl;
	aluControl1.setALUControl(alu1);
	cout << "ALU control line: " << alu1.getALUcontrolLine().to_string() << endl << endl;


	aluControl1.setALUOp(10);
	aluControl1.setOpcode(bitset<6>("101010"));
	cout << "ALUOp: " << aluControl1.getALUOp() << endl;
	cout << "opcode: " << aluControl1.getOpcode() << endl;
	aluControl1.setALUControl(alu1);
	cout << "ALU control line: " << alu1.getALUcontrolLine().to_string() << endl << endl;

}


void testProcessor()
{
	cout << "#######################################" << endl;
	cout << "#######    TESTING PROCESSOR   ########" << endl;
	cout << "#######################################" << endl;

	cout << "\tTesting constructor" << endl;
	Processor sim1("input.config");
	map<string, string> config1 = sim1.getConfig();

	map<string, string>::iterator it;
	for(it = config1.begin(); it != config1.end(); it++ )
	{
	   cout << it->first << ':' << it->second << endl ;
	}

	cout << "#######################################" << endl;
}


void testLeftShift()
{
	cout << "#######################################" << endl;
	cout << "#######    TESTING LeftShift2  ########" << endl;
	cout << "#######################################" << endl;

	LeftShift2 shift = LeftShift2(1);

	bitset<32> b1 = bitset<32>("10100010");
	bitset<32> b2 = bitset<32>("1");
	bitset<32> b3 = bitset<32>("10010100100101001001010010010100");
	bitset<32> res;
	cout << "\tTesting execute" << endl;
	cout << "Input: " << b1 << endl;
	res = shift.execute(b1, "");
	cout << "Result: " << res << endl << endl;

	cout << "Input: " << b2 << endl;
	res = shift.execute(b2, "");
	cout << "Result: " << res << endl << endl;

	cout << "Input: " << b3 << endl;
	res = shift.execute(b3, "");
	cout << "Result: " << res << endl << endl;
}

void testProgramCounter()
{
	cout << "#######################################" << endl;
	cout << "####### TESTING ProgramCounter ########" << endl;
	cout << "#######################################" << endl;
	cout << "\tTesting constructor" << endl;
	ProgramCounter pc1;
	pc1.printPC("");

	cout << "\tTesting setPC" << endl;
	pc1.setPC(bitset<32>(0x40000c));
	pc1.printPC("");
}


void testSignExtend()
{
	cout << "#######################################" << endl;
	cout << "#######   TESTING SignExtned   ########" << endl;
	cout << "#######################################" << endl;
	SignExtend extend1;

	bitset<16> b1 = bitset<16>(65);
	bitset<16> b2 = bitset<16>(-45);
	bitset<32> res;
	cout << "\tTesting execute" << endl;

	cout << "Input: " << b1 << endl;
	res = extend1.execute(b1, "");
	cout << "Output: " << res << endl << endl;


	cout << "Input: " << b2 << endl;
	res = extend1.execute(b2, "");
	cout << "Output: " << res << endl << endl;
}

void testDataMemory()
{
	cout << "#######################################" << endl;
	cout << "#######    TESTING DataMemory  ########" << endl;
	cout << "#######################################" << endl;

	cout<<"\tTesting constructor of dataMemory with 'register1.memory' "<<endl;
	string input="data1.memory";
	DataMemory dataMemory1(input);
	dataMemory1.printDataMemory("");

	cout << "#######################################" << endl;
	cout << "\tTesting read operation of dataMemory" << endl;
	dataMemory1.setMemRead(1);
	dataMemory1.setMemWrite(0);
	dataMemory1.printControlValues("");
	bitset<32> address1 (0x10000000);
	cout<< "the value in memory location 1 is :" << hex<< dataMemory1.getMemValue(0).to_ulong()<< endl;
	dataMemory1.execute(address1,bitset<32>(0),"");


	cout << "#######################################" << endl;

	cout << "\tTesting write operation of dataMemory" << endl;

	dataMemory1.setMemRead(0);
	dataMemory1.setMemWrite(1);
	dataMemory1.printControlValues("");
	bitset<32> address2 (0x10000004);
	bitset<32> writeData (0x58eed051);
	dataMemory1.execute(address2, writeData,"");
	cout<<"writeData "<<dataMemory1.getMemValue(1)<< endl;

	cout<<"Data written "<<dataMemory1.getMemValue(1)<<endl;

	cout << "#######################################" << endl;


}

void testControlUnit()
{
	cout << "#######################################" << endl;
	cout << "#######    TESTING ControlUnit  #######" << endl;
	cout << "#######################################" << endl;

	RegisterFile controlRegFile("register1.memory");
	DataMemory controlDataMem("data1.memory");
	ALUControl controlAluControl;
	MUX controlMux1(1);
	MUX controlMux2(2);
	MUX controlMux3(3);
	MUX controlMux4(4);
	MUX controlMux5(5);

	bitset<6> rtype ("000000");
	bitset<6> lw ("100011");
	bitset<6> sw ("101011");
	bitset<6> beq ("000100");
	bitset<6> addi ("001000");
	bitset<6> jump ("000010");
	ControlUnit CU(controlRegFile, controlDataMem, controlMux1, controlMux2, controlMux3, controlMux4, controlMux5, controlAluControl);

	cout << "#######################################" << endl;
	cout << "\tTesting Control Unit with R type insturctions" << endl;
	CU.updateControlValues(rtype, controlRegFile, controlDataMem, controlMux1, controlMux2, controlMux3, controlMux4, controlMux5, controlAluControl);
	CU.printControlValues("");

	cout << "#######################################" << endl;
	cout << "\tTesting Control Unit with lw insturctions" << endl;
	CU.updateControlValues(lw, controlRegFile, controlDataMem, controlMux1, controlMux2, controlMux3, controlMux4, controlMux5, controlAluControl);
	CU.printControlValues("");

	cout << "#######################################" << endl;
	cout << "\tTesting Control Unit with sw insturctions" << endl;
	CU.updateControlValues(sw, controlRegFile, controlDataMem, controlMux1, controlMux2, controlMux3, controlMux4, controlMux5, controlAluControl);
	CU.printControlValues("");

	cout << "#######################################" << endl;
	cout << "\tTesting Control Unit with beq insturctions" << endl;
	CU.updateControlValues(beq, controlRegFile, controlDataMem, controlMux1, controlMux2, controlMux3, controlMux4, controlMux5, controlAluControl);
	CU.printControlValues("");

	cout << "#######################################" << endl;
	cout << "\tTesting Control Unit with addi insturctions" << endl;
	CU.updateControlValues(addi, controlRegFile, controlDataMem, controlMux1, controlMux2, controlMux3, controlMux4, controlMux5, controlAluControl);
	CU.printControlValues("");

	cout << "#######################################" << endl;
	cout << "\tTesting Control Unit with jump insturctions" << endl;
	CU.updateControlValues(jump, controlRegFile, controlDataMem, controlMux1, controlMux2, controlMux3, controlMux4, controlMux5, controlAluControl);
	CU.printControlValues("");
}

void testInstructionMemory()
{
	cout << "#######################################" << endl;
	cout << "##### TESTING InstructionMemory  ######" << endl;
	cout << "#######################################" << endl;

	InstructionMemory instMem("prog1.asm");
	cout << "#######################################" << endl;
	cout << "\tTesting Instruction Memory with all the instructions" << endl;
	instMem.printInstructionMemory("");
	
}


void testMUX()
{
	cout << "#######################################" << endl;
	cout << "############ TESTING MUX  #############" << endl;
	cout << "#######################################" << endl;
	MUX mux1(1);
	mux1.setControl(bitset<1>(1));
	mux1.execute(bitset<32>(1),bitset<32>(0),"");
	cout << "\tTesting MUX Choses the correct input" << endl;
	cout << "All 0's " << mux1.getResult() << endl;
	
}


int main()
{
	testRegFile();
	testALU();
	testALUControl();
	testLeftShift();
	testProgramCounter();
	testSignExtend();
	testProcessor();
	testDataMemory();
	testControlUnit();
	testInstructionMemory();
	testMUX();
	return 0;
}
