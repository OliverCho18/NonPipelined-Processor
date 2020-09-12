#include "MUX.h"

MUX::MUX()
{
	componentNumber = 0;
	controlValue = 0;
}

MUX::MUX(int i)
{
	componentNumber = i;
	controlValue = 0;
}


void MUX::setControl(bitset<1> control)
{
	controlValue = control;
}

void MUX::execute(bitset<32> input1, bitset<32> input2, string output)
{
	if(controlValue == bitset<1>(1))
	{
		result = input2;
	}
	else
	{
		result = input1;
	}

	if(output == "")
	{
		cout <<"\tMUX " << componentNumber << endl;
		cout << "Input 1: 0x" << hex << input1.to_ulong() << endl;
		cout << "Input 2: 0x" << hex << input2.to_ulong() << endl;
		cout << "Control Value: 0x" << hex << controlValue.to_ulong() << endl;
		cout << "Result: 0x" << hex << result.to_ulong() << endl;
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
			out <<"\tMUX " << componentNumber << endl;
			out << "Input 1: 0x" << hex << input1.to_ulong() << endl;
			out << "Input 2: 0x" << hex << input1.to_ulong() << endl;
			out << "Control Value: 0x" << hex << controlValue.to_ulong() << endl;
			out << "Result: 0x" << hex << result.to_ulong() << endl;
		}

		// close the output file
		out.close();
	}

}

bitset<32> MUX::getResult()
{
	return result;
}
