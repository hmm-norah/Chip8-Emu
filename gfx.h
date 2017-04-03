#include "includes.h"


class GFX
{
  public:
    GFX(byte & main_memory, SDL_Texture & tex, SDL_Renderer & ren);
    ~GFX();

    void clear();
    void put(byte x_coord, byte y_coord, byte sprite, byte & collision);
    void draw();

  private:

    byte screen[WIDTH * HEIGHT];
    uint32_t buffer[WIDTH * HEIGHT];

    byte * memory;
    SDL_Texture * texture;
    SDL_Renderer * renderer; 
  
};
