#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../io/File.h"
#include "../disk/disk.h"


int main(){
  InitLLFS();
  printf("\n------Test01------\n");

  //Set up data
  int block = 100;
  char data[150];
  char buffer[150];
  char c = 'a';
  for(int i = 0; i < 150; i++) {
      data[i] = c++;
  }

  printf("Creating a child process to write to the disk\n");
  int pid = fork();
  if (pid < 0) {
      printf("Fork failed. Cannot run test :(\n");
      exit(1);
  }

  if (pid == 0){
    //Child process
    printf("Child will write to disk.");
    _Bool result_write = writeBlock(block, data, 0, 150);
    if (result_write){
      printf("Write Successful :)\n");
    } else {
      printf("TEST FAILED --> Write failed :(\n");
      return EXIT_SUCCESS;
    }
  } else {
    //Parent process
    wait(NULL); //waits for child to end
    printf("Parent will read from disk\n");
    // _Bool result_read =readBlock(block, buffer);
    //
    // //Check if same
    // if (result_read){
    //   printf("Read Successful :).\n");
    //   //printf("Read: %s", buffer);
    //   // for(int i = 0; i < 150; i++) {
    //   //   if(data[i] != buffer[i]) {
    //   //       printf("Test Failed: Data modified while reading/writing :(\n");
    //   //       return EXIT_SUCCESS;
    //   //   }//if
    //   // }//for
    //   printf("---> TEST 1 PASSED <---");
    // } else{
    //   printf("TEST FAILED --> Read failed :(\n");
    //   return EXIT_SUCCESS;
    // }
  }//else of parent process

  //should not get here
  return EXIT_SUCCESS;

}
