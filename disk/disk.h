#ifndef DISK_H
#define DISK_H
_Bool writeBlock(int blockNumber, char *data, int offset, int data_size);
_Bool readBlock(int blockNum, char* data);
void InitLLFS();
#endif
