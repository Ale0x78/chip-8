#include <stdio.h>
#include <stdlib.h>
// #include "display.h"
#include "device.h"
#include "display.h"


int main(int argc, char* args[]) {
  display* vmDisplay = create_display();
  printf("Everying is in order, entering the event loop!\n");
  while(display_tick(vmDisplay)){

  }
  printf("Done!\n");
  destory_display(vmDisplay);
  return 0;
}