#include "system.h"

int main (int argc, char ** argv)
{
  /*
  if(argc != 2)
    return 0;
    */



  char test_rom[] = "tetris.ch8";
  System ch8(test_rom);
  ch8.run();

  return 0;
}
