#include <stdio.h>
#include <stdlib.h>
// #include "display.h"
#include "device.h"



int main(int argc, char* args[]) {
  display* vmDisplay = create_display();
  device* emulator = create_device();
  printf("Everying is in order, entering the event loop!\n");
  while(vm_tick(vmDisplay)){

  }
  printf("Done!\n");
  destroy_display(vmDisplay);
  destroy_device(emulator);
  return 0;
}