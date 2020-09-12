#include "LeftShift2.h"


/*
 * Default constructor of the class.
 */
LeftShift2::LeftShift2()
{
	componentNumber = 0;
}

/*
 * Constructor of the class.
 */
LeftShift2::LeftShift2(int i)
{
	componentNumber = i;
}

/*
 * This method performs left shift operation on the given input.
 */
bitset<32> LeftShift2::execute(bitset<32> input, string output)
{
	// shift input to the left by 2 bits
	bitset<32> res = input << 2;

	
	// if output file is not given, print to cout
	if(output == "")
	{
		cout << "\tLeft Shift " << componentNumber << endl;
		cout << "Input: 0x" << input.to_ulong() << endl;
		cout << "Result: 0x" << res.to_ulong() << endl;
	}
	else
	{

		// open output file
		ofstream out;
		out.open(output.c_str(),ios_base::app);

		// terminate if the output file is "bad"
		if(out.bad())
		{
			cerr << "Output file for LeftShift2 couldn't be opened!" << endl;
			exit(1);
		}

		else
		{
			out << "\tSign Extend" << endl;
			out << "Input: 0x" << input.to_ulong() << endl;
			out << "Result: 0x" << res.to_ulong() << endl;
		}

		// close the output file
		out.close();
	}

	return res;
}
