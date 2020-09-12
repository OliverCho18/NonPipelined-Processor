#include "DataMemory.h"


/*
*The default contstrucotr
*/
DataMemory::DataMemory()
	{
		for(int i = 0; i < 100; i++){//initialize all values to 0
		memory[i] = bitset<32>(0);
		}
		offset = -1;
		memSize = 0;
	}
/*
*Constructor for the class which reads the memory file to enter values into an accesible array
*/
DataMemory::DataMemory(string inputFile){
	offset = -1;
	memSize = 0;
	for(int i = 0; i < 100; i++){//initialize all values to 0
		memory[i] = bitset<32>(0);
	}

	// open the input file
	ifstream in;
	in.open(inputFile.c_str());

	if(in.bad())//check if the input file is of correct format
	{
		cerr << "Input file for Memory couldn't be opened!" << endl;
		exit(1);
	}
	else
	{

		string line;
		while(getline(in, line))//while there are more lines
		{

			if(line == "" || line[0] == '#')
				continue;
			line = line.substr(0, line.find("#"));
			istringstream ss(line);
			long long memIndex;
			char temp;
			long long memHexValue;

			// read values from the memory file
			ss >> hex >> memIndex;
			ss >> temp;
			ss >> hex >> memHexValue;

			// set offset if first line
			if(offset == -1)
			{
				offset = memIndex;
			}
			//convert index to normal values
			int convertedIndex;
			convertedIndex = (memIndex-offset)/4;
			// set register values
			memory[convertedIndex] = bitset<32>(memHexValue);
			memSize++;
		}
	}

	// close the input file
	in.close();
}

/*
 * This method simulates the behavior of DataMemory with given
 * parameters according to control values.
 */
void DataMemory::execute(bitset<32> address, bitset<32> writeData, string output){

	readData = bitset<32>(0);//set readData to 0

	if(getMemWrite()==1){//memWrite is on
		int convertedIndex;
		long long longAddress=address.to_ullong();
		convertedIndex = (longAddress-offset)/4;//find the correct memory location
		memory[convertedIndex]=writeData;//write to that memory location
		readData=memory[convertedIndex];


	}
	if(getMemRead() == 1){//MemRead is on
		int convertedIndex;
		long long longAddress=address.to_ullong();
		convertedIndex = (longAddress-offset)/4;// find the correct memory location
		readData=memory[convertedIndex];//give read data the information in that memory location
	}


	// if output file is not given, print to cout
	if(output == "")
	{
		cout << "\tData Memory" << endl;
		cout << "Input address: 0x" << hex <<  address.to_ulong() << endl;
		if(getMemWrite()==1)
		{
			cout << "Write Data: 0x" << hex << writeData.to_ulong() << endl;
		}
		if(getMemRead()==1)
		{
			cout << "Read Data: 0x" << hex << readData.to_ulong() << endl;
		}

	}
	else
	{

		// open output file
		ofstream out;
		out.open(output.c_str(),ios_base::app);

		// terminate if the output file is "bad"
		if(out.bad())
		{
			cerr << "Output file for Data Memory couldn't be opened!" << endl;
			exit(1);
		}

		else
		{
			out << "\tData Memory" << endl;
			out << "Input address: 0x" << hex <<  address.to_ulong() << endl;
			if(getMemWrite()==1)
			{
				out << "Write Data: 0x" << hex << writeData.to_ulong() << endl;
			}
			if(getMemRead()==1)
			{
				out << "Read Data: 0x" << hex << readData.to_ulong() << endl;
			}
		}

		// close the output file
		out.close();
	}

}
/*
 * This method prints the contents in the memory
 * file to the specified output file.
 */

void DataMemory::printDataMemory(string outputFile){
	if(outputFile == "")
	{
		cout << "\tData Memory Content" << endl;
		for(int i = 0; i < memSize; i++)
		{
			cout << hex << offset+(i*4) << ":"<< setfill('0') << setw(8) << memory[i].to_ulong() << endl;
		}
	}
	else
	{

		// open output file
		ofstream out;
		out.open(outputFile.c_str(), ios_base::app);

		// terminate if the output file is "bad"
		if(out.bad())
		{
			cerr << "Output file for Registers couldn't be opened!" << endl;
			exit(1);
		}

		else
		{
			out << "\tData Memory Content" << endl;
			// print register values to output file
			for(int i = 0; i < memSize; i++)
			{
				out << hex << offset+(i*4) << ":"<< setfill('0') << setw(8) << memory[i].to_ulong() << endl;
			}
		}

		// close the output file
		out.close();
	}


}

/*
 * This method prints the MemWrite and MemRead control
 * value to the given output file.
 */

void DataMemory::printControlValues(string outputFile){
	if(outputFile == "")
	{
		cout<<"memWrite is "<<getMemWrite()<<endl;
		cout<<"memRead is"<<getMemRead()<<endl;
	}
	else
	{

		// open output file
		ofstream out;
		out.open(outputFile.c_str(),ios_base::app);

		// terminate if the output file is "bad"
		if(out.bad())
		{
			cerr << "Output file for Registers couldn't be opened!" << endl;
			exit(1);
		}

		else
		{
			out<<"memWrite is "<<getMemWrite()<<endl;
			out<<"memRead is"<<getMemRead()<<endl;
		}

		// close the output file
		out.close();
	}
}

/*
 * Accessor method for readData.
 */
bitset<32> DataMemory::getReadData(){
	return readData;
}

/*
 * Set MemWrite to new value.
 */

void DataMemory::setMemWrite(bitset<1> c){
	memWrite=c;
}

/*
 * Set MemRead to new value.
 */
void DataMemory::setMemRead(bitset<1> c){
	memRead=c;
}

/*
 * Accessor method for Memory location i.
 */
bitset<32> DataMemory::getMemValue(int i){
	return memory[i];
}

/*
 * Accessor method for MemRead.
 */
bitset<1> DataMemory::getMemRead()
{
	return memRead;
}

/*
 * Accessor method for MemWrite.
 */
bitset<1> DataMemory::getMemWrite()
{
	return memWrite;
}
