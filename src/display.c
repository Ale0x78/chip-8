#include "display.h"
#include "SDL3/SDL.h"
#include "SDL3/SDL_video.h"
#include <stdio.h>


display* create_display() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    return NULL;
  }
  display* this = (display*) malloc(sizeof(display));
  this->window = SDL_CreateWindow(
			    "Emulator",
			    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			    SCREEN_WIDTH, SCREEN_HEIGHT,
			    SDL_WINDOW_SHOWN
			    );
  if (this->window == NULL) {
    fprintf(stderr, "Error: Failed to create a window");
    return NULL;
  }
  return this;
}

void destroy_display(display* self){
  SDL_DestroyWindow(self->window);
  free(self);
  SDL_Quit();
}


