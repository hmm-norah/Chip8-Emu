#include "system.h"

int main (int argc, char ** argv)
{
  /*
  if(argc != 2)
    return 0;
    */
  /*
  SDL_Window* window = NULL;
            
  SDL_Surface* screenSurface = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) != 0){
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }
  //Create window
  window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN );
  if( window == NULL )
  {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
  }
  else
  {
      //Get window surface
      screenSurface = SDL_GetWindowSurface( window );
  }
  */

  char test_rom[] = "tetris.ch8";
  System ch8(test_rom);
  ch8.run();


  return 0;
}
