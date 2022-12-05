#include <SDL3/SDL.h>
#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_video.h"
#include <stdlib.h>
#include <stdlib.h>


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 320

struct display_struct {
  SDL_Window *window;
  SDL_Surface *screen;
} typedef display;

display* create_display();
void destroy_display(display* self);
