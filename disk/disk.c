#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******Disk Params******/
#define BLOCK_SIZE 512 //bytes
#define NUM_BLOCKS 4096 //on Disk, numbered 0 to 4095
#define VDISK "../disk/vdisk" //disk location
#define MAGIC_NUMBER 42
#define IONODES 128 //>>>what is this supposed to be?
#define TRUE  1
#define FALSE 0

_Bool writeBlock(int blockNumber, char *data, int offset, int data_size){
  FILE *disk = fopen(VDISK, "rb+");
  fseek(disk, blockNumber * BLOCK_SIZE + offset, SEEK_SET);
  int length = data_size;

  if(data_size > BLOCK_SIZE - offset) {
      int difference = data_size - (BLOCK_SIZE - offset);
      fprintf(stderr, "WARNING: Truncated content by %d bytes on disk write to block %d\n", difference, blockNumber);
      length = BLOCK_SIZE - offset;
  }

  int fwrite_result = fwrite(data, length, 1, disk);
  if(fwrite_result <= 0){
    fprintf(stderr, "FAILURE: fwrite() failed to write to the disk.\n");
    return FALSE;
  }
  fflush(disk);
  fclose(disk);
  return TRUE;
}

_Bool readBlock(int blockNum, char* data){
  FILE *disk = fopen(VDISK, "rb");


  fseek(disk, blockNum * BLOCK_SIZE, SEEK_SET);
  int fread_result = fread(data, BLOCK_SIZE, 1, disk);
  if(fread_result <= 0){
    fprintf(stderr, "FAILURE: fread() failed to read from the disk.\n");
    return FALSE;
  }
  fclose(disk);
  return TRUE;

}

void InitLLFS(){

  FILE *disk = fopen(VDISK, "ab+");
  char *init = calloc(BLOCK_SIZE*NUM_BLOCKS, 1);
  fwrite(init, BLOCK_SIZE * NUM_BLOCKS, 1, disk);
  free(init);
  fclose(disk);

  disk = fopen(VDISK, "rb+");

  // Initialize Block 0
  char* buffer;
  buffer = (char *) malloc(BLOCK_SIZE);
  int magic = MAGIC_NUMBER;
  int blocks = NUM_BLOCKS;
  int ionodes = IONODES;

  memcpy(buffer, &magic, sizeof(magic));
  memcpy(buffer + sizeof(int) * 1, &blocks, sizeof(int));
  memcpy(buffer + sizeof(int) * 2, &ionodes, sizeof(int));

  writeBlock(0, buffer, 0 , BLOCK_SIZE);
  free(buffer);
  fclose(disk);
}
