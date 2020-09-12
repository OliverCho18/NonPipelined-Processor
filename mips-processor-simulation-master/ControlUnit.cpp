#include "ControlUnit.h"

ControlUnit::ControlUnit() {
}
/*
*Constructor for ControlUnit
*/
ControlUnit::ControlUnit(RegisterFile &regFile, DataMemory &dataMem, MUX &mux1, MUX &mux2, MUX &mux3, MUX &mux4, MUX &mux5, ALUControl &aluControl){
	opcode = bitset<6>(0);
	regDst=bitset<1>(0);
	jump=bitset<1>(0);
	branch=bitset<1>(0);
	memRead=bitset<1>(0);
	memToReg=bitset<1>(0);
	aluOp0=bitset<1>(0);
	aluOp1=bitset<1>(0);
	memWrite=bitset<1>(0);
	aluSrc=bitset<1>(0);
	regWrite=bitset<1>(0);
	controlRegFile=regFile;
	controlDataMem=dataMem;
	controlAluControl=aluControl;
	controlMux1=mux1;
	controlMux2=mux2;
	controlMux3=mux3;
	controlMux4=mux4;
	controlMux5=mux5;

}

/*
*Updates the corresponding control values based on the given opcode
*/
void ControlUnit::updateControlValues(bitset<6> c, RegisterFile &controlRegFile, DataMemory &controlDataMem, MUX &controlMux1, MUX &controlMux2, MUX &controlMux3, MUX &controlMux4, MUX &controlMux5, ALUControl &controlAluControl){
	opcode = c;
	if(opcode==bitset<6>("000000")){//opcode is r type
		regDst=bitset<1>(1);
		jump=bitset<1>(0);
		branch=bitset<1>(0);
		memRead=bitset<1>(0);
		memToReg=bitset<1>(0);
		aluOp0=bitset<1>(0);
		aluOp1=bitset<1>(1);
		memWrite=bitset<1>(0);
		aluSrc=bitset<1>(0);
		regWrite=bitset<1>(1);
		controlDataMem.setMemWrite(0);
		controlDataMem.setMemRead(0);
		controlRegFile.setRegWrite(1);
		controlAluControl.setALUOp(10);
		controlMux1.setControl(1);
		controlMux2.setControl(0);
		controlMux3.setControl(0);
		controlMux4.setControl(0);
		controlMux5.setControl(0);
	}
	else if(opcode==bitset<6>("100011")){//opcode is lw
		regDst=bitset<1>(0);
		jump=bitset<1>(0);
		branch=bitset<1>(0);
		memRead=bitset<1>(1);
		memToReg=bitset<1>(1);
		aluOp0=bitset<1>(0);
		aluOp1=bitset<1>(0);
		memWrite=bitset<1>(0);
		aluSrc=bitset<1>(1);
		regWrite=bitset<1>(1);

		controlDataMem.setMemWrite(0);
		controlDataMem.setMemRead(1);
		controlRegFile.setRegWrite(1);
		controlAluControl.setALUOp(00);
		controlMux1.setControl(0);
		controlMux2.setControl(0);
		controlMux3.setControl(0);
		controlMux4.setControl(1);
		controlMux5.setControl(1);

	}
	else if(opcode==bitset<6> ("101011")){//opcode is sw

		regDst=bitset<1>(0);
		jump=bitset<1>(0);
		branch=bitset<1>(0);
		memRead=bitset<1>(0);
		memToReg=bitset<1>(0);
		aluOp0=bitset<1>(0);
		aluOp1=bitset<1>(0);
		memWrite=bitset<1>(1);
		aluSrc=bitset<1>(1);
		regWrite=bitset<1>(0);

		controlDataMem.setMemWrite(1);
		controlDataMem.setMemRead(0);
		controlRegFile.setRegWrite(0);
		controlAluControl.setALUOp(00);
		controlMux1.setControl(0);
		controlMux2.setControl(0);
		controlMux3.setControl(0);
		controlMux4.setControl(0);
		controlMux5.setControl(1);

	}
	else if(opcode==bitset<6>("000100")){//opcode is beq

		regDst=bitset<1>(0);
		jump=bitset<1>(0);
		branch=bitset<1>(1);
		memRead=bitset<1>(0);
		memToReg=bitset<1>(0);
		aluOp0=bitset<1>(1);
		aluOp1=bitset<1>(0);
		memWrite=bitset<1>(0);
		aluSrc=bitset<1>(0);
		regWrite=bitset<1>(0);

		controlDataMem.setMemWrite(0);
		controlDataMem.setMemRead(0);
		controlRegFile.setRegWrite(0);
		controlAluControl.setALUOp(01);
		controlMux1.setControl(0);
		controlMux2.setControl(1);
		controlMux3.setControl(0);
		controlMux4.setControl(0);
		controlMux5.setControl(0);
	}
	else if(opcode==bitset<6>("001000")){//opcode is addi

		regDst=bitset<1>(0);
		jump=bitset<1>(0);
		branch=bitset<1>(0);
		memRead=bitset<1>(0);
		memToReg=bitset<1>(0);
		aluOp0=bitset<1>(0);
		aluOp1=bitset<1>(0);
		memWrite=bitset<1>(0);
		aluSrc=bitset<1>(1);
		regWrite=bitset<1>(1);

		controlDataMem.setMemWrite(0);
		controlDataMem.setMemRead(0);
		controlRegFile.setRegWrite(bitset<1>("1"));
		controlAluControl.setALUOp(00);
		controlMux1.setControl(0);
		controlMux2.setControl(0);
		controlMux3.setControl(0);
		controlMux4.setControl(0);
		controlMux5.setControl(1);
	}
	else{//opcode is jump
		regDst=bitset<1>(0);
		jump=bitset<1>(1);
		branch=bitset<1>(0);
		memRead=bitset<1>(0);
		memToReg=bitset<1>(0);
		aluOp0=bitset<1>(0);
		aluOp1=bitset<1>(0);
		memWrite=bitset<1>(0);
		aluSrc=bitset<1>(0);
		regWrite=bitset<1>(0);

		controlDataMem.setMemWrite(0);
		controlDataMem.setMemRead(0);
		controlRegFile.setRegWrite(0);
		controlAluControl.setALUOp(00);
		controlMux1.setControl(0);
		controlMux2.setControl(0);
		controlMux3.setControl(1);
		controlMux4.setControl(0);
		controlMux5.setControl(0);

	}


}
void ControlUnit::printControlValues(string outputFile){
	if (outputFile==""){//print to console
		cout<<"\tControl Unit"<<'\n';
		cout<<"Input opcode: 0x"<< hex << opcode.to_ulong() <<'\n';
		cout<<"regDst: 0x"<< hex << regDst.to_ulong()  <<'\n';
		cout<<"jump: 0x"<< jump.to_ulong() << '\n';
		cout<<"branch: 0x" << branch.to_ulong() <<'\n';
		cout<<"memRead: 0x"<<memRead.to_ulong()<<'\n';
		cout<<"memToReg: 0x"<<memToReg.to_ulong()<<'\n';
		cout<<"aluOp0: 0x"<<aluOp0.to_ulong()<<'\n';
		cout<<"aluOp1: 0x"<<aluOp1.to_ulong()<<'\n';
		cout<<"memWrite: 0x"<<memWrite.to_ulong()<<'\n';
		cout<<"aluSrc: 0x"<<aluSrc.to_ulong()<<'\n';
		cout<<"regWrite: 0x"<<regWrite.to_ulong()<<'\n';
	}
	else{//print to outoutFile
		ofstream outFile;
		outFile.open(outputFile,ios_base::app);
		outFile<<"\tControl Unit"<<'\n';
		outFile<<"Input opcode: 0x"<< hex << opcode.to_ulong() <<'\n';
		outFile<<"regDst: 0x"<< hex << regDst.to_ulong()  <<'\n';
		outFile<<"jump: 0x"<< jump.to_ulong() << '\n';
		outFile<<"branch: 0x" << branch.to_ulong() <<'\n';
		outFile<<"memRead: 0x"<<memRead.to_ulong()<<'\n';
		outFile<<"memToReg: 0x"<<memToReg.to_ulong()<<'\n';
		outFile<<"aluOp0: 0x"<<aluOp0.to_ulong()<<'\n';
		outFile<<"aluOp1: 0x"<<aluOp1.to_ulong()<<'\n';
		outFile<<"memWrite: 0x"<<memWrite.to_ulong()<<'\n';
		outFile<<"aluSrc: 0x"<<aluSrc.to_ulong()<<'\n';
		outFile<<"regWrite: 0x"<<regWrite.to_ulong()<<'\n';

	}

}

/*
 * Accessor method for RegDst.
 */
bitset<1> ControlUnit::getRegDst(){
	return regDst;
}

/*
 * Accessor method for Jump.
 */
bitset<1> ControlUnit::getJump(){
	return jump;
}

/*
 * Accessor method for Branch.
 */
bitset<1> ControlUnit::getBranch(){
	return branch;
}

/*
 * Accessor method for MemRead.
 */
bitset<1> ControlUnit::getMemRead(){
	return memRead;
}
/*
 * Accessor method for MemToReg.
 */
bitset<1> ControlUnit::getMemToReg(){
	return memToReg;
}

/*
 * Accessor method for AluOp0.
 */
bitset<1> ControlUnit::getAluOp0(){
	return aluOp0;
}

/*
 * Accessor method for AluOp1.
 */
bitset<1> ControlUnit::getAluOp1(){
	return aluOp1;
}

/*
 * Accessor method for MemWrite.
 */
bitset<1> ControlUnit::getMemWrite(){
	return memWrite;
}

/*
 * Accessor method for AluSrc.
 */
bitset<1> ControlUnit::getAluSrc(){
	return aluSrc;
}
/*
 * Accessor method for RegWrite.
 */
bitset<1> ControlUnit::getRegWrite(){
	return regWrite;
}