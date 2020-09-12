#include "RegisterFile.h"


/*
 * Default constructor
 */
RegisterFile::RegisterFile()
{
	for(int i = 0; i < 32; i++)
		registers[i] = bitset<32>(0);

	readData1 = bitset<32>(0);
	readData2 = bitset<32>(0);
	regWrite = bitset<1>(0);
}


/*
 * The constructor of the class, initializes all the registers with
 * the values from the input file.
 */
RegisterFile::RegisterFile(string input)
{
	// set initial values for registers to zero first
	for(int i = 0; i < 32; i++)
		registers[i] = bitset<32>(0);


	// open the input file
	ifstream in;
	in.open(input.c_str());

	// terminate the program if input file is "bad"
	if(in.bad())
	{
		cerr << "Input file for Registers couldn't be opened!" << endl;
		exit(1);
	}
	else
	{
		string line;
		while(getline(in, line))
		{
			// skip empty lines and comment lines
			if(line == "" || line[0] == '#')
				continue;
			istringstream ss(line);
			int regIndex;
			char temp;
			long long regHexValue;

			// read values from the input file
			ss >> dec >> regIndex;
			ss >> temp;
			ss >> hex >> regHexValue;

			// set register values
			registers[regIndex] = bitset<32>(regHexValue);
		}
	}

	// close the input file
	in.close();
}

/*
 * This method simulates the behavior of register file with given
 * parameters according to control value of register file (regWrite).
 */
void RegisterFile::execute(bitset<5> readRegister1, bitset<5> readRegister2,
			 bitset<5> writeRegister, bitset<32> writeData, bool writeStage, string output)
{

	readData1 = bitset<32>(0);
	readData2 = bitset<32>(0);

	// execute write operation if control value is set to write and it's
	// write stage
	if(regWrite.count() == 1 && writeStage == true)
	{
		int regIndex = (int) writeRegister.to_ulong();
		registers[regIndex] = writeData;
	}

	// execute read operation if read registers are given
	if(readRegister1 != -1)
		readData1 = registers[(int) readRegister1.to_ulong() ];
	if(readRegister2 != -1)
		readData2 = registers[(int) readRegister2.to_ulong() ];


	// if output file is not given, print to cout
	if(output == "")
	{
		cout << "\tRegister File" << endl;
		if(readRegister1 != -1)
		{
			cout << "readRegister1: 0x" << hex << setfill('0') << readRegister1.to_ulong() << endl;
			cout << "readData1: 0x" << hex << setfill('0') << setw(8) << readData1.to_ulong() << endl;
		}

		if(readRegister2 != -1)
		{
			cout << "readRegister2: 0x" << hex << setfill('0') << readRegister2.to_ulong() << endl;
			cout << "readData2: 0x" << hex << setfill('0') << setw(8) << readData2.to_ulong() << endl;
		}

		if(writeStage)
		{
			cout << "writeRegister: 0x" << hex << setfill('0') << writeRegister.to_ulong() << endl;
			cout << "writeData: 0x" << hex << setfill('0') << setw(8) << writeData.to_ulong() << endl;
		}
		cout << "regWrite: 0x" << hex << regWrite.to_ulong() << endl;
	}
	else
	{

		// open output file
		ofstream out;
		out.open(output.c_str(),ios_base::app);

		// terminate if the output file is "bad"
		if(out.bad())
		{
			cerr << "Output file for Register File couldn't be opened!" << endl;
			exit(1);
		}

		else
		{
			out << "\tRegister File" << endl;
			if(readRegister1 != -1)
			{
				out << "readRegister1: 0x" << hex << setfill('0') << readRegister1.to_ulong() << endl;
				out << "readData1: 0x" << hex << setfill('0') << setw(8) << readData1.to_ulong() << endl;
			}

			if(readRegister2 != -1)
			{
				out << "readRegister2: 0x" << hex << setfill('0') << readRegister2.to_ulong() << endl;
				out << "readData2: 0x" << hex << setfill('0') << setw(8) << readData2.to_ulong() << endl;
			}

			if(writeStage)
			{
				out << "writeRegister: 0x" << hex << setfill('0')  << writeRegister.to_ulong() << endl;
				out << "writeData: 0x" << hex << setfill('0') << setw(8) << writeData.to_ulong() << endl;
			}
			out << "regWrite: 0x" << hex << regWrite.to_ulong() << endl;
		}

		// close the output file
		out.close();
	}
}

/*
 * This method prints the content of the registers in the register
 * file to the specified output file.
 */
void RegisterFile::printRegisterFile(string output)
{
	// if output file is not given, print to cout
	if(output == "")
	{
		cout << "\tRegister File Content" << endl;
		for(int i = 0; i < 32; i++)
		{
			cout << dec << i << ":" << hex << setfill('0') << setw(8) << registers[i].to_ulong() << endl;
		}
	}
	else
	{

		// open output file
		ofstream out;
		out.open(output.c_str(), ios_base::app);

		// terminate if the output file is "bad"
		if(out.bad())
		{
			cerr << "Output file for Registers couldn't be opened!" << endl;
			exit(1);
		}

		else
		{
			out << "\tRegister File Content" << endl;
			// print register values to output file
			for(int i = 0; i < 32; i++)
			{
				out << dec << i << ":" << hex << setfill('0') << setw(8) << registers[i].to_ulong() << endl;
			}
		}

		// close the output file
		out.close();
	}
}

/*
 * This method prints the read data fields and the regWrite control
 * value to the given output file.
 */
void RegisterFile::printDataAndControlValues(string output)
{
	// if output file is not given, print to cout
	if(output == "")
	{
		cout << "\tRegister File" << endl;
		cout << "readData1: " << hex << setfill('0') << setw(8) << readData1.to_ulong() << endl;
		cout << "readData1 (decimal): " << dec << readData1.to_ulong() << endl;
		cout << "readData2: " << hex << setfill('0') << setw(8) << readData2.to_ulong() << endl;
		cout << "readData2 (decimal): " << dec << readData2.to_ulong() << endl;
		cout << "regWrite: " << hex << regWrite.to_ulong() << endl;
	}
	else
	{

		// open output file
		ofstream out;
		out.open(output.c_str(),ios_base::app);

		// terminate if the output file is "bad"
		if(out.bad())
		{
			cerr << "Output file for Registers couldn't be opened!" << endl;
			exit(1);
		}

		else
		{
			out << "\tRegister File" << endl;
			out << "readData1: " << hex << setfill('0') << setw(8) << readData1.to_ulong() << endl;
			out << "readData1 (decimal): " << dec << readData1.to_ulong() << endl;
			out << "readData2: " << hex << setfill('0') << setw(8) << readData2.to_ulong() << endl;
			out << "readData2 (decimal): " << dec << readData2.to_ulong() << endl;
			out << "regWrite: " << hex << regWrite.to_ulong() << endl;
		}

		// close the output file
		out.close();
	}
}

/*
 * Accessor method for readData1.
 */
bitset<32> RegisterFile::getReadData1()
{
	return readData1;
}

/*
 * Accessor method for readData2.
 */
bitset<32> RegisterFile::getReadData2()
{
	return readData2;
}

/*
 * Acessor method for registers, returns the register numbered i.
 */
bitset<32> RegisterFile::getRegister(int i)
{
	return registers[i];
}

/*
 * Mutator method for regWrite.
 */
void RegisterFile::setRegWrite(bitset<1> c)
{
	regWrite = c;
}

/*
 * Accessor method for regWrite.
 */
bitset<1> RegisterFile::getRegWrite()
{
	return regWrite;
}
