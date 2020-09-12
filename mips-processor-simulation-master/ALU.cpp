#include "ALU.h"


/*
 * Default constructor for ALU class. Sets ALUresult to 0.
 */
ALU::ALU()
{
	ALUresult = bitset<32>(0);
	ALUcontrolLine = bitset<4>(0);
	zero = bitset<1>(0);
}

/*
 * Constructor for ALU class. Sets ALUresult to 0. Sets component number to
 * given integer value.
 */
ALU::ALU(int i)
{
	ALUresult = bitset<32>(0);
	ALUcontrolLine = bitset<4>(0);
	zero = bitset<1>(0);
	componentNumber = i;
}



/*
 * This function will simulate an ALU applied to the given information
 * in data1 and data 2. Also the if ALUcontrol holds a value, the
 * ALU will apply what the ALUcontrolLine function says to do on data1 data2.
 */
void ALU::execute(bitset<32> data1, bitset<32> data2, string output)
{
	bitset<4> ANDcontrol("0000");
	bitset<4> ORcontrol("0001");
	bitset<4> ADDcontrol("0010");
	bitset<4> SUBcontrol("0110");
	bitset<4> SLTcontrol("0111");
	bitset<4> NORcontrol("1100");

	ALUresult = bitset<32>(0);
	zero = bitset<1>(0);

	if(ALUcontrolLine == ANDcontrol)
	{
		// perform AND operation
		ALUresult = (data1 & data2);
	}
	else if(ALUcontrolLine == ORcontrol)
	{
		// perform OR operation
		ALUresult = (data1 | data2);
	}
	else if(ALUcontrolLine == ADDcontrol)
	{
		// perform ADD operation
		int data1_val = (int) data1.to_ulong();
		int data2_val = (int) data2.to_ulong();
		int res  = data1_val + data2_val;
		ALUresult = bitset<32>(res);
	}
	else if(ALUcontrolLine == SUBcontrol)
	{
		// perform SUB operation
		int data1_val = (int) data1.to_ulong();
		int data2_val = (int) data2.to_ulong();
		int res  = data1_val - data2_val;
		ALUresult = bitset<32>(res);
	}
	else if(ALUcontrolLine == SLTcontrol)
	{
		// perform SLT operation
		int data1_val = (int) data1.to_ulong();
		int data2_val = (int) data2.to_ulong();

		if(data1_val < data2_val)
			ALUresult = bitset<32>(1);
		else
			ALUresult = bitset<32>(0);

	}
	else if(ALUcontrolLine == NORcontrol)
	{
		// perform NOR operation
		ALUresult = ~(data1 | data2);
	}

	// set zero
	if(ALUresult.count() == 0)
	{
		zero = bitset<1>(1);
	}
	else
	{
		zero = bitset<1>(0);
	}


	// print the execution input and output to given file (or to the console)
	if(output == "")
	{
		cout <<"\tALU " << componentNumber << endl;
		cout << "Data 1: 0x" << hex << setw(8) << data1.to_ulong() << endl;
		cout << "Data 2: 0x" << hex << setw(8) << data2.to_ulong() << endl;
		cout << "Result: 0x" << hex << setw(8) << ALUresult.to_ulong() << endl;
		cout << "Zero: 0x" << hex << zero.to_ulong() << endl;
	}
	else
	{

		// open output file
		ofstream out;
		out.open(output.c_str(),ios_base::app);

		// terminate if the output file is "bad"
		if(out.bad())
		{
			cerr << "Output file for ALU couldn't be opened!" << endl;
			exit(1);
		}

		else
		{
			out <<"\tALU " << componentNumber << endl;
			out << "Data 1: 0x" << hex << setw(8) <<  data1.to_ulong() << endl;
			out << "Data 2: 0x" << hex << setw(8) << data2.to_ulong() << endl;
			out << "Result: 0x" << hex << setw(8) << ALUresult.to_ulong() << endl;
			out << "Zero: 0x" << hex << zero.to_ulong() << endl;
		}

		// close the output file
		out.close();
	}
}

/*
 * Accessor method for ALUresult
 */
bitset<32> ALU::getALUresult()
{
	return ALUresult;
}


/*
 * Mutator method for ALUcontrolLine
 */
void ALU::setALUcontrolLine(bitset<4> c)
{
	ALUcontrolLine = c;
}

/*
 * Accessor method for ALUcontrolLine
 */
bitset<4> ALU::getALUcontrolLine()
{
	return ALUcontrolLine;
}


/*
 * Accessor method for zero
 */
bitset<1> ALU::getZero()
{
	return zero;
}
