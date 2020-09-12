#include "SignExtend.h"

/*
 * Default constructor of the class.
 */
SignExtend::SignExtend()
{}

/*
 * Method that takes 16-bit input and returns sign extends it to 32-bits.
 * The method also prints the input and output to given file.
 */
bitset<32> SignExtend::execute(bitset<16> input, string output)
{

	bitset<32> res(0);

	for(int i = 0; i < 16; i++)
	{
		res[i] = input[i];
	}
	for(int i = 16; i < 32; i++)
	{
		res[i] = input[15];
	}

	// if output file is not given, print to cout
	if(output == "")
	{
		cout << "\tSign Extend" << endl;
		cout << "Input: 0x" << hex << input.to_ulong() << endl;
		cout << "Result: 0x" << hex << res.to_ulong() << endl;
	}
	else
	{

		// open output file
		ofstream out;
		out.open(output.c_str(),ios_base::app);

		// terminate if the output file is "bad"
		if(out.bad())
		{
			cerr << "Output file for SignExtend couldn't be opened!" << endl;
			exit(1);
		}

		else
		{
			out << "\tSign Extend" << endl;
			out << "Input: 0x" << hex << input.to_ulong() << endl;
			out << "Result: 0x" << hex << res.to_ulong() << endl;
		}

		// close the output file
		out.close();
	}

	return res;
}