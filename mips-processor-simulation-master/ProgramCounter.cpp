#include "ProgramCounter.h"

/*
 * Default constructor of the class. Sets the initial value for
 * PC to 0x400000;
 */
ProgramCounter::ProgramCounter()
{
	pc = bitset<32>(0x400000);
}
/*
 * Mutator method for the PC.
 */
void ProgramCounter::setPC(bitset<32> c)
{
	pc = c;
}

/*
 * Accessor method for the PC.
 */
bitset<32> ProgramCounter::getPC()
{
	return pc;
}

/*
 * This method prints the PC to the given output file
 */
void ProgramCounter::printPC(string output)
{
	// if output file is not given, print to cout
	if(output == "")
	{
		cout <<"\tProgram Counter" << endl;
		cout << "PC: 0x" << hex << setfill('0') << setw(8) << pc.to_ulong() << endl;
	}
	else
	{

		// open output file
		ofstream out;
		out.open(output.c_str(),ios_base::app);

		// terminate if the output file is "bad"
		if(out.bad())
		{
			cerr << "Output file for PC couldn't be opened!" << endl;
			exit(1);
		}

		else
		{
			out <<"\tProgram Counter" << endl;
			out << "PC: 0x" << hex << setfill('0') << setw(8) << pc.to_ulong() << endl;
		}

		// close the output file
		out.close();
	}
}