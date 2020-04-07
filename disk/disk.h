#ifndef DISK_H
#define DISK_H
bool writeBlock(int blockNumber, char *data, int offset, int data_size);
void readBlock(FILE* disk, int blockNum, char* data);
void InitLLFS();
#endif
