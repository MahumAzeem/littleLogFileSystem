#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******Disk Params******/
#define BLOCK_SIZE 512 //bytes
#define NUM_BLOCKS 4096 //on Disk, numbered 0 to 4095
#define VDISK "vdisk" //disk location
#define MAGIC_NUMBER 42
#define IONODES 128 //>>>what is this supposed to be?

void writeBlock(FILE* vdisk, int blockNumber, char* data){
  FILE *disk = fopen(VDISK, "rb+");
  fseek(disk, blockNumber * BLOCK_SIZE, SEEK_SET);
  fwrite(data, BLOCK_SIZE, 1, disk);
}

void readBlock(FILE* disk, int blockNum, char* data){
  fseek(disk, blockNum * BLOCK_SIZE, SEEK_SET);
  fwrite(data, BLOCK_SIZE, 1, disk); //overwrites existing data
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

  writeBlock(disk, 0, buffer);
  free(buffer);
  fclose(disk);
}
