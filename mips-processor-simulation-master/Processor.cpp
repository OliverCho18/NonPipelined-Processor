#include "Processor.h"

/*
 * The constructor of the class, reads the configuration file
 * and initializes all the components.
 */
Processor::Processor(string filename)
{
	// open the input file
	ifstream in;
	in.open(filename.c_str());

	// terminate the program if input file is "bad"
	if(in.bad())
	{
		cerr << "Configuration file cannot be opened!" << endl;
		exit(1);
	}
	else
	{
		string line;
		string delim = "=";
		while(getline(in, line))
		{
			// remove whitespace
			line.erase(remove(line.begin(), line.end(), ' '), line.end());

			// ignore empty and comment lines
			if(line == "" || line[0] == '#')
				continue;
			line = line.substr(0, line.find("#"));
			string param = line.substr(0, line.find(delim));
			string val = line.substr(line.find(delim)+1, line.size());

			config[param] = val;
		}
	}

	// close the input file
	in.close();

	// if write to file is false, set output file to empty string
	if(config["write_to_file"] == "false")
		config["output_file"] = "";
	// clear any content in the output file
	else
	{
		ofstream out;
		out.open(config["output_file"], ofstream::out | ofstream::trunc);
		out.close();
	}
	regFile = RegisterFile(config["register_file_input"]);
	alu1 = ALU(1);
	alu2 = ALU(2);
	alu3 = ALU(3);
	aluControl = ALUControl();
	instMem = InstructionMemory(config["program_input"]);

	dataMem = DataMemory(config["memory_contents_input"]);
	
	mux1 = MUX(1);
	mux2 = MUX(2);
	mux3 = MUX(3);
	mux4 = MUX(4);
	mux5 = MUX(5);

	cUnit = ControlUnit(regFile, dataMem, mux1, mux2, mux3, mux4, mux5, aluControl);

	programCounter = ProgramCounter();

	signExtend = SignExtend();

	shift_left_1 = LeftShift2(1);
	shift_left_2 = LeftShift2(2);



}

/*
 * The main function of the program. Until program termination,
 * in a while loop, this method fetches the instruction from
 * instruction memory with respect to current program counter
 * and executes it.
 */
void Processor::run()
{


	// ALU1 & ALU2 only perform addition
	alu1.setALUcontrolLine(bitset<4>("0010"));
	alu2.setALUcontrolLine(bitset<4>("0010"));

	// run simulation until all instructions are run
	while(!instMem.isFinished(programCounter.getPC()))
	{

		// fetch the instrution
		currentInst = instMem.getInstruction(programCounter.getPC());

		//print the instruction
		if(config["output_file"] == "")
		{
			cout << "CURRENT INSTRUCTION: " << instMem.getInstructionString(programCounter.getPC()) << endl;
		}
		else
		{
			// open output file
			ofstream out;
			out.open(config["output_file"].c_str(),ios_base::app);

			// terminate if the output file is "bad"
			if(out.bad())
			{
				cerr << "Output file for Registers couldn't be opened!" << endl;
				exit(1);
			}

			else
			{
				out << "Current instruction: " << instMem.getInstructionString(programCounter.getPC()) << endl;
			}

			// close the output file
			out.close();
		}

		// print PC
		programCounter.printPC(config["output_file"]);

		// split instruction to its parts
		bitset<6> inst_31_26(0);
		for(int i = 26; i <=31; i++)
			inst_31_26[i-26] = currentInst[i];

		bitset<5> inst_25_21(0);
		for(int i = 21; i <=25; i++)
			inst_25_21[i-21] = currentInst[i];

		bitset<5> inst_20_16(0);
		for(int i = 16; i <=20; i++)
			inst_20_16[i-16] = currentInst[i];

		bitset<5> inst_15_11(0);
		for(int i = 11; i <=15; i++)
			inst_15_11[i-11] = currentInst[i];

		bitset<16> inst_15_0(0);
		for(int i = 0; i <=15; i++)
			inst_15_0[i-0] = currentInst[i];

		bitset<6> inst_5_0(0);
		for(int i = 0; i <=5; i++)
			inst_5_0[i-0] = currentInst[i];

		bitset<26> inst_25_0(0);
		for(int i = 0; i <=25; i++)
			inst_25_0[i-0] = currentInst[i];

		bitset<32> inst_15_0_extended = signExtend.execute(inst_15_0,config["output_file"]);

		// (Instruction Decode) Passing the opcode to Control Unit, the Control Unit
		// then updates the control values of other components with respect to this opcode.
		cUnit.updateControlValues(inst_31_26, regFile, dataMem, mux1, mux2, mux3, mux4, mux5, aluControl);

		cUnit.printControlValues(config["output_file"]);

		// (Instruction Decode) Passing the required bits to Register File and executing
		// read operation
		regFile.execute(inst_25_21, inst_20_16, bitset<5>(-1), bitset<32>(-1), false, config["output_file"]);
		bitset<32> readData1 = regFile.getReadData1();
		bitset<32> readData2 = regFile.getReadData2();

		// (Execute) Taking the 15-0 bits of the instructions and results from
		// the Register File, passing the values and executing the specified operation
		// using ALU3 with the help of ALU Control and MUX5

		aluControl.setOpcode(inst_5_0);
		aluControl.setALUControl(alu3);

		aluControl.printValues(config["output_file"]);

		mux5.execute(readData2, inst_15_0_extended, config["output_file"]);
		bitset<32> mux5_res = mux5.getResult();

		alu3.execute(readData1, mux5_res, config["output_file"]);

		bitset<32> aluResult = alu3.getALUresult();
		bitset<1> zero = alu3.getZero();


		// (Memory Access) Passing the ALU result and write data to Data Memory object
		// and executing its operation.

		dataMem.execute(aluResult, readData2, config["output_file"]);

		bitset<32> readData = dataMem.getReadData();



		// (Writeback) Taking the result from the Data memory and writing data back
		// to registers with the help of MUX4 and MUX1.
		mux1.execute(bitset<32>(inst_20_16.to_string()), bitset<32>(inst_15_11.to_string()), config["output_file"]);
		bitset<5> writeRegister(0);
		for(int i = 0; i < 5; i++)
			writeRegister[i] = mux1.getResult()[i];
		mux4.execute(aluResult, readData, config["output_file"]);
		bitset<32> writeData = mux4.getResult();
		regFile.execute(bitset<5>(-1), bitset<5>(-1), writeRegister, writeData, true, config["output_file"]);


		// (PC update) Updating the PC with the help of ALU1, ALU2, MUX2 and MUX3
		// with respect to instruction.

		// calculate PC+4
		alu1.execute(programCounter.getPC(), bitset<32>(4),config["output_file"]);
		bitset<32> alu1_result = alu1.getALUresult();


		// Shift-left 1
		bitset<32> temp = bitset<32>(inst_25_0.to_string());
		temp = shift_left_1.execute(temp, config["output_file"]);
		bitset<28> inst_25_0_shifted;
		for(int i = 0; i < 28; i++)
			inst_25_0_shifted[i] = temp[i];



		//calculate jump address
		bitset<32> jump_address(0);

		for(int i = 31; i >= 28; i--)
			jump_address[i] = alu1_result[i];
		for(int i = 27; i >= 0; i--)
			jump_address[i] = inst_25_0_shifted[i];


		//cout << "jump_address: " << jump_address << endl;
		//cout << "jump : " << hex << jump_address.to_ulong() << endl;

		// Shift-left 2
		bitset<32> inst_15_0_extended_shifted = shift_left_2.execute(inst_15_0_extended, config["output_file"]);


		// calculate branch address
		alu2.execute(alu1_result, inst_15_0_extended_shifted, config["output_file"]);
		bitset<32> alu2_result = alu2.getALUresult();

		//cout << "Branch address: " << alu2_result << endl;
		//cout << "branch : " << hex << alu2_result.to_ulong() << endl;

		// choose between branch, jump and PC+4
		mux2.setControl((zero & cUnit.getBranch()));
		mux2.execute(alu1_result, alu2_result, config["output_file"]);
		bitset<32> mux2_res = mux2.getResult();

		mux3.execute(mux2_res, jump_address, config["output_file"]);
		bitset<32> mux3_res = mux3.getResult();

		// update PC
		programCounter.setPC(mux3_res);

		if(config["print_memory_contents"]=="true")
		{
			regFile.printRegisterFile(config["output_file"]);
			dataMem.printDataMemory(config["output_file"]);
			instMem.printInstructionMemory(config["output_file"]);
		}


		if(config["output_file"] == "")
		{
			cout << "#######################################################" << endl;
		}
		else
		{
			// open output file
			ofstream out;
			out.open(config["output_file"].c_str(),ios_base::app);

			// terminate if the output file is "bad"
			if(out.bad())
			{
				cerr << "Output file for Registers couldn't be opened!" << endl;
				exit(1);
			}

			else
			{
				out << "#######################################################" << endl;
			}

			// close the output file
			out.close();
		}


		if(config["output_mode"] == "single_step")
		{
			cout << "Press enter to continue" << endl;
			cin.ignore();
		}
	}

}


/*
 * Accessor method for config map
 */
map<string,string> Processor::getConfig()
{
	return config;
}
