#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../io/File.h"
#include "../disk/disk.h"


int main(){
  InitLLFS();
  FILE *test = fopen("test.txt", "rb+");
  writeBlock(disk, 2, test);
  return EXIT_SUCCESS;

}
