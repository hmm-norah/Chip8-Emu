#include "system.h"

System::System(char * file): cpu(*memory)
{
  initialize(file);
}

System::~System()
{
}

void System::initialize(char * file)
{
  int file_size;

  ifstream in;
  in.open(file, ios::binary | ios::ate);

  file_size = in.tellg();

  byte * start = &memory[0x200]; 

  in.seekg(0, in.beg);
  /*

  for(int i = 0; i < file_size; ++i)
    in >> (start + i);
    */

  in.read((char *) start, file_size + 1);

}

void System::run()
{
  for(;;)
    cpu.step();
}
