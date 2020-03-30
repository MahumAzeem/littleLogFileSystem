#ifndef DISK_H
#define DISK_H
void writeBlock(FILE* disk, int blockNumber, char* data);
void readBlock(FILE* disk, int blockNum, char* data);
void InitLLFS();
#endif
