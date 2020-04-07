/***********Basis file of the filesystem************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FILENAME_LENGTH 30
#define BITS_PER_BIT_VECTOR 4096
#define UNAVAILABLE 0
#define AVAILABLE 1

/*
Each inode is 32 bytes long
· First 4 bytes: size of file in bytes; an integer
· Next 4 bytes: flags – i.e., type of file (flat or directory); an integer
· Next 2 bytes, multiplied by 10: block numbers for file’s first ten blocks
· Next 2 bytes: single-indirect block
· Last 2 bytes: double-indirect block
*/
typedef struct inode {
    unsigned int file_size;
    unsigned int flags;
    unsigned short direct[10];
    unsigned short single_ind_block;
    unsigned short double_ind_block;
} inode_t;

/*************************Bit Vectors**************************/
/*Resource used: http://www.mathcs.emory.edu/~cheung/Courses/255/Syllabus/1-C-intro/bit-array.html
  Mapping function:
  Element with index k in the bit vector is:
  Bit position k%8 in the vector element with index k/8S
*/
typedef struct bit_vector {
    unsigned char vector[BITS_PER_BIT_VECTOR]; //1 byte per element, 4096 elements -> 4096 bytes
    short n; // bits marked as unavailable (0)
    short next_available; // smallest bit out of all available (not used so far)
} bitvector_t;

/*
 * Mark as in use. Updates n.
 */
void clear_bit(bitvector_t *vector, short index) {
    unsigned char byte = vector->vector[index/8];
    unsigned char mask = 1; // 0000 0001
    mask = ~(mask << index % 8);
    vector->vector[index/8] = byte & mask;
    vector->n++; // Update n
}

/*
 * Mark as available. Updates n.
 */
void set_bit(bitvector_t *vector, short index) {
    unsigned char byte = vector->vector[index/8];
    unsigned char mask = 1; // 0000 0001
    mask = mask << index % 8;
    vector->vector[index/8] = byte | mask;
    vector->n--;
}

/*
 * Marks every item as used.
 */
void clear_all_bits(bitvector_t *vector) {
    int i;
    unsigned char* arr = vector->vector;
    for(i = 0; i < BITS_PER_BIT_VECTOR/8; i++) {
        arr[i] = 0;
    }
    vector->n = BITS_PER_BIT_VECTOR;
}

/*
 * Marks every item as unused. Sets next_available to 0;
 */
void set_all_bits(bitvector_t *vector) {
    int i;
    unsigned char* arr = vector->vector;
    for(i = 0; i < BITS_PER_BIT_VECTOR/8; i++) {
        arr[i] = 0xff;
    }
    vector->n = 0;
    vector->next_available = 0;
}
