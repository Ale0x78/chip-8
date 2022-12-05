#include <stdlib.h>
#include <stdio.h>
#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_video.h"
#include "display.h"

struct device_struct {

} typedef device; 

device* create_device();
void destroy_device(device * self);
int vm_tick(display* self);