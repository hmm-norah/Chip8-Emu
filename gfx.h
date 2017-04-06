#include "includes.h"


class GFX
{
  public:
    GFX(byte & main_memory);
    ~GFX();

    void clear();
    void put(byte x_coord, byte y_coord, byte sprite, byte & collision);
    void draw();

  private:

    byte screen[WIDTH * HEIGHT];
    uint32_t buffer[WIDTH * HEIGHT];

    byte * memory;

    SDL_Window * window;
    SDL_Texture * frame;
    SDL_Renderer * renderer; 
  
};
