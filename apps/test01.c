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
  char buffer[150];
  char c = 'a';
    for(int i = 0; i < 150; i++) {
        data[i] = c++;
    }

    //Write data to disk
  _Bool result_write = writeBlock(block, data, 0, 150);
  _Bool result_read =readBlock(block, buffer);

  if (result_write){
    printf("Write Successful :).\n");
    if (result_read){
      printf("Read Successful :).\n");
      for(int i = 0; i < 150; i++) {
        if(result[i] != oracle[i]) {
            printf("Test Failed: Data modified while reading/writing :(\n");
            return EXIT_SUCCESS;
        }//if
      }//for
    }//result_read if
  }
  else{
    printf("Test 1 failed :(\n");
  }
  return EXIT_SUCCESS;

}
