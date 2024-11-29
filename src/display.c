#include "display.h"
#include "SDL3/SDL_video.h"
#include <stdio.h>


display* create_display() {
  if (SDL_Init(SDL_INIT_VIDEO) == false) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    return NULL;
  }
  display* this = (display*) malloc(sizeof(display));
  this->window = SDL_CreateWindow(
			    "Emulator",
			     SCREEN_WIDTH, SCREEN_HEIGHT, 0x00);
  if (this->window == NULL) {
    fprintf(stderr, "Error: Failed to create a window");
    return NULL;
  }
  this->screen = NULL;
  this->renderer = NULL;
  return this;
}



void destroy_display(display* self){
  SDL_DestroyWindow(self->window);
  free(self);
  SDL_Quit();
}
