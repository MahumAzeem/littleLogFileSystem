#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../io/File.h"
#include "../disk/disk.h"


int main(){
  InitLLFS();
  printf("\n------Test01------\n");

  short block = 100
  char data[150];

  //FILE *test = fopen("test.txt", "rb+");
  bool result = writeBlock(block, data, 0, 150);

  if (result){
    fprintf("Test 1 passe :).\n");
  }
  else{
    fprintf("Test 1 failed :(\n");
  }
  return EXIT_SUCCESS;

}
