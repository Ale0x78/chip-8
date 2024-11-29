#include "device.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_stdinc.h"
#include <stdlib.h>
#include <time.h>

#define DEBUG 1


device* create_device(display *display){
  device *self = (device *)calloc(sizeof(device), 1);
  self->memory = (char*) calloc(0xfff, 1);
  self->pc = 0x200;

  self->sound_timer = 0;
  self->delay_timer = 0;
  self->update_time = clock();
  self->display = display;
  self->I = 0;
  self->sp = 0;


  return self;
}
void destroy_device(device * self) {
  free(self);
}

int load_program(device *self, char path[]){
  FILE* program_file = fopen(path, "r");

  if(program_file == NULL) {
    return -1;
  }
  fgets((self->memory + 0x200), (0xfff - 0x200), program_file);
  fclose(program_file);
  if(DEBUG){
    printf("[DEBUG] Loaded into memory!");
    int idx = 0;
    for(char* curr = (self->memory + 0x200); curr < (self->memory + 0xfff); curr++) {
      printf("%x ", *curr);
      if(idx % 10 == 0){
        printf("\n");
      }
      idx += 1;
    }
    printf("\n");
  }
  return -1;
}

Uint16 flip_endianness(Uint16 value){
  return ((value & 0x00FF) << 8) | ((value & 0xFF00) >> 8);
}

Uint16 pop(Uint16 *stack){
  // TODO: implement
  return 0;
}

void push(Uint16 *stack, Uint16 value){
  // TODO: Implement
}

void update(device *self){
  clock_t now = clock();
  if((now - self->update_time) >= (1.0/60.0)) { // Limit to 60Hz
    self->update_time = (float) now;
    Uint16 curr = ((Uint16*) self->memory)[self->pc];
    curr = flip_endianness(curr);
    printf("Executing: %x\n", curr);
    self->pc += 2;
    // Let's hard code the first 2 instructions
    if (curr == 0x000E0){
      // Clear display
      return;
    }
    if (curr == 0x00EE){
      self->pc = pop(self->stack);
    }
    switch((curr & 0xf000)){
      case 0x1000:
        self->pc = (0x200 + (0x0fff & curr));
      case 0x2000:
        push(self->stack, self->pc);
      case 0x3000:
        if (self->v[((0x0f00 & curr) >> 8)] == ((0x00ff & curr))) { // TODO: This is readable?
          self->pc += 2;
        }
        break;
      case 0x4000:
        if (self->v[((0x0f00 & curr) >> 8)] != ((0x00ff & curr))) { // TODO: This is readable?
          self->pc += 2;
        }
        break;
      case 0x5000:
        if( self->v[((0x0f00 & curr) >> 8)] == self->v[((0x00f0 & curr) >> 4)]){
          self->pc += 2;
        }
        break;
      case 0x6000:
        self->v[((0x0f00 & curr) >> 8)] = ((0x00ff & curr));
        break;
      case 0x7000:
        self->v[((0x0f00 & curr) >> 8)] += ((0x00ff & curr));
        break;
      case 0x8000:
      {
        Uint8 op_mode = (curr & 0xf);
        switch (op_mode) {
          case 0x0:
            self->v[((0x0f00 & curr) >> 8)] = self->v[((0x00f0 & curr) >> 4)];
          break;
          case 0x1:
            self->v[((0x0f00 & curr) >> 8)] |= self->v[((0x00f0 & curr) >> 4)];
          break;
          case 0x2:
            self->v[((0x0f00 & curr) >> 8)] &= self->v[((0x00f0 & curr) >> 4)];
          break;
          case 0x3:
            self->v[((0x0f00 & curr) >> 8)] ^= self->v[((0x00f0 & curr) >> 4)];
          break;
          case 0x4:
            self->v[((0x0f00 & curr) >> 8)] += self->v[((0x00f0 & curr) >> 4)];
            //TODO If overflow!
          break;
          case 0x5:
            self->v[((0x0f00 & curr) >> 8)] -= self->v[((0x00f0 & curr) >> 4)];
            //TODO If overflow!
          break;
          case 0x6:
            self->v[((0x0f00 & curr) >> 8)] = (self->v[((0x00f0 & curr) >> 4)] >> 1);
            //TODO If overflow!
          break;
          case 0x7:
          self->v[((0x0f00 & curr) >> 8)] = self->v[((0x00f0 & curr) >> 4)] - self->v[((0x0f00 & curr) >> 8)];
          //TODO If overflow!
          break;
          case 0xe:
          self->v[((0x0f00 & curr) >> 8)] = (self->v[((0x00f0 & curr) >> 4)] << 1);
          //TODO If overflow!
          break;
          default:
            printf("Unexpected instruction %x\n", curr);
        }
        break;
      }
      case 0x9000:
        if( self->v[((0x0f00 & curr) >> 8)] != self->v[((0x00f0 & curr) >> 4)]){
          self->pc += 2;
        }
      break;
      case 0xa000:
      break;
      case 0xb000:
      break;
      case 0xc000:
      break;
      case 0xd000:
      break;
      case 0xe000:
      break;
      case 0xf000:
      break;
      default:
        printf("Unexpected instruction %x\n", curr);
    }
  }
}

int vm_tick(device* self){
    SDL_Event e;
    self->display->renderer = SDL_GetRenderer(self->display->window);
    SDL_SetRenderDrawColor(self->display->renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(self->display->renderer, NULL);
    SDL_UpdateWindowSurface(self->display->window);
    while (SDL_PollEvent(&e)){
        if (e.type == SDL_EVENT_QUIT){
            return 0;
        }
        if(e.key.scancode == SDL_SCANCODE_Q){
            return 0;
        }
    }
    update(self);
  return 1;
}
