// bitmap.h: bitmap API defienition, etc
//         - the current holds rational for number of bits longer than
//           long double as the memory is on the heap
//

#ifndef _H_BITMAP_HEADER
#define _H_BITMAP_HEADER


#include <memory.h>
#include <stdbool.h>
#include <stdint.h>


#include <stdio.h>



typedef struct BitMap_ BitMap_t ;


// prototypes follow

BitMap_t* bitmap_create(unsigned int nbits) ;
void      bitmap_free(BitMap_t* bm) ;
unsigned int bitmap_size(BitMap_t* bm) ;

void      bitmap_print(BitMap_t*) ;
void      bitmap_set_bit(BitMap_t* bm, unsigned int ind) ;
void      bitmap_unset_bit(BitMap_t* bm, unsigned int ind) ;
void      bitmap_clear(BitMap_t* bm) ;
void      bitmap_set_all(BitMap_t* bm) ;

bool      bitmap_is_bit_set(BitMap_t* bm, unsigned int ind) ;

// @return: TRUE if all bits in the bitmap are set to 1, else return FALSE
bool bitmap_is_full(BitMap_t *bitmap);

/*
2. binary_string - ptr to the binary string containing dont care bits, for example, 0001010 x010xx01
3. n_bits - no of bits in binary string, in this case it should be 15 ( 0001010 x010xx01 )
4. i - output parameter, must return the starting index where the match starts.

 @return: TRUE - match found, FALSE: otherwise
          API returns as soon as first pattern match is found.
*/
bool bitmap_pattern_match (BitMap_t *bm,
                           char *bs,      // 'x' marks a don't care bit
                           int n_bits,    // length of 'bs'
                           int *i);       //


/* a Looping macros that iterates over bits of a bitmap.
           - bitmap_ptr - is the pointer to the bitmap object
           - bit_state - if the current bit is TRUE/FALSE
*/

#define ITERATE_BITMAP_BEGIN(bitmap_ptr, bit_state) \
{                                                    \
unsigned int   _bm_size = bitmap_size(bitmap_ptr) ;  \
for (unsigned int i = 0 ; i < _bm_size ; ++i)  {     \
   bit_state = bitmap_is_bit_set(bitmap_ptr, i) ;

#define ITERATE_BITMAP_END(bitmap_ptr , bit_state)   }}


_H_BITMAP_HEADER
#endif

// eof bitmap.h
