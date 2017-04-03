#include "system.h"

int main (int argc, char ** argv)
{
  /*
  if(argc != 2)
    return 0;
    */

  SDL_Window* window = NULL;
            
  if (SDL_Init(SDL_INIT_VIDEO) != 0){
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }
  //Create window
  window = SDL_CreateWindow( "SDL Tutorial", 900, 900, WIDTH * 2, HEIGHT * 2, SDL_WINDOW_SHOWN );
  if( window == NULL )
  {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
  }

  SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_RenderSetLogicalSize(renderer, WIDTH * 2, HEIGHT * 2);

  SDL_Texture * tex = SDL_CreateTexture(renderer, 
      SDL_PIXELFORMAT_ARGB8888, 
      SDL_TEXTUREACCESS_STREAMING, 
      64, 32);


  char test_rom[] = "tetris.ch8";
  System ch8(test_rom, *tex, *renderer);
  ch8.run();

  SDL_Delay(6000);

  return 0;
}
