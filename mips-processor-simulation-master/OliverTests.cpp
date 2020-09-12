#include "DataMemory.h"
#include "ControlUnit.h"
#include "ALUControl.h"
#include "RegisterFile.h"
#include "MUX.h"
#include "ALU.h"

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
	dataMemory1.execute(address1,NULL,"");

	cout<<"readData" << dataMemory1.getReadData()<<endl;
	

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
int main()
{
	testDataMemory();
	testControlUnit();
	return 0;
}