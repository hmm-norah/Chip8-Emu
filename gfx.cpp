#include "gfx.h"

GFX::GFX(byte & main_memory)
{
  memory = &main_memory;
  
  window = NULL;
            
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    cout << "SDL_Init Error: " << SDL_GetError() << endl;

  //Create window
  window = SDL_CreateWindow( "Chip 8 Emulator", 
      SDL_WINDOWPOS_CENTERED_DISPLAY(0), 
      SDL_WINDOWPOS_CENTERED_DISPLAY(0),
      WIDTH, 
      HEIGHT, 
      SDL_WINDOW_SHOWN);

  if(!window)
      cout << "Window could not be created! SDL_Error: "  << SDL_GetError() << endl;

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);

  frame = SDL_CreateTexture(renderer, 
      SDL_PIXELFORMAT_ARGB8888, 
      SDL_TEXTUREACCESS_STREAMING, 
      WIDTH, HEIGHT);
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

  SDL_UpdateTexture(frame, NULL, buffer, WIDTH * 4);

  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, frame, NULL, NULL);
  SDL_RenderPresent(renderer);

}
