#include "gfx.h"

GFX::GFX(byte & main_memory, SDL_Texture & tex, SDL_Renderer & ren)
{
  memory = &main_memory;

  texture = &tex;

  renderer = & ren;

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
    buffer[i] = (0x00FFFFFF * screen[i]) | 0xFF000000;

  SDL_UpdateTexture(texture, NULL, buffer, WIDTH * 4);

  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);

}
