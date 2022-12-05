
#include "device.h"

device* create_device(){
  return NULL;
}
void destroy_device(device * self) {
  free(self);
}

int vm_tick(display* self){
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
