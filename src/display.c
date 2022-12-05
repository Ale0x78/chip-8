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

void destory_display(display* self){
  SDL_DestroyWindow(self->window);
  free(self);
  SDL_Quit();
}

int display_tick(display* self){
    SDL_Event e;
    self->screen = SDL_GetWindowSurface(self->window);
    SDL_FillRect(self->screen, NULL, SDL_MapRGB(self->screen->format, 0x00, 0x00, 0x00));
    SDL_UpdateWindowSurface(self->window);
    while (SDL_PollEvent(&e)){
        if (e.type == SDL_QUIT){
            return 0;
        }
    }
  return 1;
}

