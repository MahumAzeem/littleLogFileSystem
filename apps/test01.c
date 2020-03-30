#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../io/File.h"
#include "../disk/disk.h"


int main(){
  InitLLFS();
  FILE* disk;
  writeBlock(disk, 2, "hello");
  return EXIT_SUCCESS;

}
