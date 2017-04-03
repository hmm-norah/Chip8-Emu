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

void GFX::put(byte x_coord, byte y_coord, byte sprite_layer, byte & collision)
{
	int b = 7;
  for(int i = 0; i < 8; ++i)
  {
    byte pixel = (sprite_layer & (1 << b)) >> b;

    if(collision == 0x00 && pixel && screen[x_coord + i + y_coord * WIDTH])
      collision = 1;
    
    if(pixel)
      screen[x_coord + i + y_coord * WIDTH] ^= 1;

		--b;
  }
}

void GFX::draw()
{
  for(int i = 0; i < PIXELS; ++i)
  {
    if(*(screen + i) == 1)
      printf("█");
    else
      printf(" ");

    if(i % WIDTH == 0)
      cout << "\n";
  }
}
