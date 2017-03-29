#include "includes.h"
#include "cpu.h"

class System
{
  public:
    System();
    ~System();

  private:
    CPU cpu;
    byte memory[0xFFF];

};
