#include <stdio.h>
#include <stdlib.h>
// #include "display.h"
#include "device.h"



int main(int argc, char* args[]) {
  display* vmDisplay = create_display();
  device* emulator = create_device(vmDisplay);
  printf("Everying is in order, entering the event loop!\n");
  if(load_program(emulator, "test/IBM.ch8") != 0){
    printf("Failed to load program\n");
    return 0;
  }
  while(vm_tick(emulator)){

  }
  printf("Done!\n");
  destroy_display(vmDisplay);
  destroy_device(emulator);

  return 0;
}
