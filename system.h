#include "includes.h"
#include "cpu.h"
#include <unistd.h>

class System
{
  public:
    System(char * file, SDL_Texture & tex, SDL_Renderer & render);
    ~System();

    void run();
    void initialize(char * file);

  private:

    CPU cpu;
    byte memory[0xFFF];

};
