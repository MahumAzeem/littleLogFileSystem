#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../io/File.h"
#include "../disk/disk.h"


int main(){
  InitLLFS();
  printf("\n------Test01------\n");

  int block = 100;
  char data[150];
  char c = 'a';
    for(int i = 0; i < 150; i++) {
        data[i] = c++;
    }

  //FILE *test = fopen("test.txt", "rb+");
  bool result = writeBlock(block, data, 0, 150);

  if (result){
    printf("Test 1 passed :).\n");
  }
  else{
    printf("Test 1 failed :(\n");
  }
  return EXIT_SUCCESS;

}
