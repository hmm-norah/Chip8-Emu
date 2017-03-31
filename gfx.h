#include "includes.h"


class GFX
{
  public:
    GFX(byte & main_memory);
    ~GFX();

    void clear();
    int put(byte x_coord, byte y_coord, byte sprite);
    void draw();

  private:

    byte screen[WIDTH * HEIGHT];

    byte * memory;
  
};
