#include "gfx.h"

GFX::GFX(byte & main_memory)
{
  memory = &main_memory;


}

GFX::~GFX()
{
}

void GFX::clear()
{
  for(int i = 0; i < PIXELS; ++i)
    *(screen + i) = 0x00;
}

int GFX::put(byte x_coord, byte y_coord, byte nth)
{
  int offset = x_coord * y_coord;
  int collision = 0;

  for(int i = 7; i > -1; --i)
  {
    byte pixel = (nth & (1 << i)) >> i;

    if(pixel && screen[offset + i])
      collision = 1;
    
    if(pixel)
      screen[offset + i] ^= pixel;
  }

  return collision;


}

void GFX::draw()
{
  for(int i = 0; i < PIXELS; ++i)
  {
    if(*(screen + i) == 1)
      printf("█");
    else
      printf(" ");

    if(i + 1 % WIDTH == 0)
      cout << "\n";
  }
}
