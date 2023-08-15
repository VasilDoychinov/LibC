// bitmap.h: bitmap API defienition, etc
//         - Least significant byte with index 0, ... Little Endian
//

#ifndef _H_BITMAP_LIB_HEADER
#define _H_BITMAP_LIB_HEADER

#include <memory.h>
#include <stdbool.h>
#include <assert.h>

#include "bitmap.h"


#define BTS_IN_CH    8

struct BitMap_ {
   char*        _barr ;   // the buffer ( on the Heap)
   unsigned int _sizea ;  // number of bits to handle
} ;


// private prototypes follow
void _print_bits_of_char(unsigned char ptr, unsigned int num_bytes) ;

unsigned int _nbits_to_nbytes(unsigned int nbts) ;
unsigned int _bit_to_byte_index(unsigned int nbts, unsigned int bn) ;
bool         _is_bit_on(char c, unsigned int nbit) ;

_H_BITMAP_LIB_HEADER
#endif

// eof bitmap.h
