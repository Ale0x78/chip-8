#include <stdlib.h>
#include <stdio.h>
#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_video.h"
#include <SDL3/SDL_init.h>
#include "display.h"

struct device_struct {
  char* memory;
  Uint16 pc;
  char v[0xf];
  Uint8 sound_timer;
  Uint8 delay_timer;
  clock_t update_time;
  Uint16 I;
  char sp;
  display *display;
  Uint16 stack[16];
} typedef device;

device* create_device(display *display);
int load_program(device *self, char path[]);
void destroy_device(device *self);
void update(device *self);
int vm_tick(device* self);
