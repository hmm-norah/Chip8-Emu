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
}

void GFX::draw()
{
}
