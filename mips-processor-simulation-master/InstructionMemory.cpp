#include "InstructionMemory.h"


InstructionMemory::InstructionMemory()
{
  numInstructions = 0;
}


InstructionMemory::InstructionMemory(string input_file)
{
  numInstructions = 0;
  for(int i = 0; i < 100; i++)
  {
    instructions[i] = bitset<32>(0);
  }
  readInstructions(input_file);
  
}


void InstructionMemory::readInstructions(string program_input)
{
  // numInstructions = 2;
  // instructions[0] = bitset<32>("00100000010000010000000001100100");
  // instructions[1] = bitset<32>("00000000100010000001100000100000");
  ifstream in;
  in.open(program_input.c_str());
  if(in.bad()){
    cerr << "The input file for program input could not be opened!" << endl;
  }
  
  else{
    string line;
    int temp = 0;
    while( getline(in, line)){
      if(line == "" || line[0] == '#')
      {
        continue;
      }
      instruction_strings[temp] = line.substr(0, line.find("#"));
      temp++;
    }
  }
	ASMParser parser = ASMParser(program_input); 
  

  if(parser.isFormatCorrect() == false)
  {
    cerr << "Format of input file is incorrect " << endl;
    exit(1);
  }

  Instruction i;

  //Iterate through instructions, storing each encoding into the instructions array
  i = parser.getNextInstruction();
  string temp;
  while(i.getOpcode() != UNDEFINED)
  {
    temp = i.getEncoding();
    instructions[numInstructions] = bitset<32>(temp);
    
    //instructions[numInstructions](std::string(temp)); not working
    i = parser.getNextInstruction();
    numInstructions ++;   // Count the number of instructions
  }

}

bitset<32> InstructionMemory::getInstruction(bitset<32> programCounter)
{
  int instructionLocation;
  instructionLocation = (int) (programCounter.to_ulong() - 0x400000)/4;
  return instructions[instructionLocation];

}

void InstructionMemory::printInstructionMemory(string output)
{
  if(output == "")
  {
    cout << "\tInstruction Memory Content" << endl;
    for(int i = 0; i < numInstructions; i++)
    {
      cout << "0x" <<hex << setfill('0') << setw(8) << instructions[i].to_ulong() << endl;
    }
  }
  else
  {
    ofstream out;
    out.open(output.c_str(),ios_base::app);

    out << "\tInstruction Memory Content" << endl;
    for(int i = 0; i < numInstructions; i++)
    {
      out << "0x" <<hex << setfill('0') << setw(8) << instructions[i].to_ulong() << endl;
    }

    out.close();
  }
}

bool InstructionMemory::isFinished(bitset<32> programCounter)
{
  // Divide by 4 to find the correct location instruction location
  int currentInstruction = (int) (programCounter.to_ulong() - 0x400000)/4;
  if(currentInstruction >= numInstructions)
  {
    return true;
  }
  return false;
}


string InstructionMemory::getInstructionString(bitset<32> programCounter)
{
  int currentInstruction = (int) (programCounter.to_ulong() - 0x400000)/4;
  return instruction_strings[currentInstruction];  
}

