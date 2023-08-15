// bitmap.c: the implementation
//

#include <stdlib.h>                        // foro printf()

#include "bitmap.h"
#include "_bitmap_.h"



// public APIs

BitMap_t*
bitmap_create(unsigned int nbits)
{
   assert(nbits > 0) ;   // if (nbits == 0) return NULL ;

   BitMap_t* wbm = calloc(1, sizeof(BitMap_t)) ;
   if (wbm) {
      wbm->_sizea = nbits, nbits = _nbits_to_nbytes(nbits) ;
      if (wbm->_barr = malloc(nbits))   memset(wbm->_barr, 0, nbits) ;
      else                              free (wbm), wbm  = NULL ;
   }
   return wbm ;
}

void
bitmap_free(BitMap_t* bm)
{
   assert(bm) ;
   if (bm)   free(bm->_barr), free(bm) ;
}

unsigned int bitmap_size(BitMap_t *bm)
{
   return bm && bm->_barr ? bm->_sizea : 0 ;
}

void
bitmap_print(BitMap_t* bm)
{
   assert(bm && bm->_barr) ;

   printf("{ ") ;

   unsigned int   num_bytes = _nbits_to_nbytes(bm->_sizea) ;

   // a better in respect of memory addressing would be to iterate
   // through the max size of numericals but ...

   char* ptr = bm->_barr + num_bytes - 1 ; // to the Most significant

   {
      int   rem = (bm->_sizea) % 8 ;
      _print_bits_of_char(*ptr, rem > 0 ? rem : 8) ;
   }

   for (--ptr, --num_bytes ; num_bytes > 0 ; --num_bytes, --ptr) {
      printf(" / "), _print_bits_of_char(*ptr, 8) ;
   }

   printf(" }") ;
}

void
bitmap_set_bit(BitMap_t* bm, unsigned int ind)
{
   assert(bm && bm->_barr) ;
   if (ind < bm->_sizea) {
      // unsigned int bind = _bit_to_byte_index(bm->_sizea, ind) ;
      // printf("\n: bit %u -> byte #: %u", ind, bind) ;
      char*   ptr = bm->_barr + _bit_to_byte_index(bm->_sizea, ind) ;
      *ptr |= (1 << (ind % BTS_IN_CH)) ;
   }
}

void
bitmap_unset_bit(BitMap_t* bm, unsigned int ind)
{
   assert(bm && bm->_barr) ;
   if (ind < bm->_sizea) {
      char*   ptr = bm->_barr + _bit_to_byte_index(bm->_sizea, ind) ;
      *ptr &= ~(1 << (ind % BTS_IN_CH)) ;
   }
}

void
bitmap_clear(BitMap_t* bm)
{
   unsigned int   bs = bitmap_size(bm) ;
   if (bs > 0) memset(bm->_barr, 0, _nbits_to_nbytes(bs)) ;
}

void
bitmap_set_all(BitMap_t* bm)
{
   assert(bm && bm->_barr && bm->_sizea > 0) ;
   unsigned int   bs = _nbits_to_nbytes(bitmap_size(bm)) - 1 ;
   memset(bm->_barr, 0xFF, bs) ;

   *(bm->_barr + bs) = 0xFF >> BTS_IN_CH  - bm->_sizea % BTS_IN_CH ;
}

bool
bitmap_is_bit_set(BitMap_t* bm, unsigned int ind)
{
   assert(bm && bm->_barr && ind < bm->_sizea) ;
   char*   ptr = bm->_barr + _bit_to_byte_index(bm->_sizea, ind) ;
   return *ptr & (1 << (ind % BTS_IN_CH)) ;
}

bool bitmap_is_full(BitMap_t *bm)
{
   unsigned int   bs = bitmap_size(bm) ;
   if (bs == 0)   return false ;

   unsigned char* p = bm->_barr ;
   bs = _nbits_to_nbytes(bs) ;
   for (unsigned int i = 1 ; i < bs ; ++i, ++p) { // without the last byte
      if (*p != 0xFF)   return false ;
   }

   bs = BTS_IN_CH  - bm->_sizea % BTS_IN_CH ;
   return *p == (0xFF >> bs) ;
}

bool
bitmap_pattern_match (BitMap_t *bm,
                      char* bs,        // 'x' marks a don't care bit
                      int   bs_len,    // length of 'bs'
                      int*  ind)       // start of the 1st match
{

   return false ;
}


// private helpers

bool _is_bit_on(char c, unsigned int nb)
{
   return c & (1 << nb) ;
}

unsigned int _nbits_to_nbytes(unsigned int nbts)
{
   return nbts % BTS_IN_CH > 0 ? nbts / BTS_IN_CH + 1 : nbts / BTS_IN_CH ;
}

unsigned int _bit_to_byte_index(unsigned int nbts, unsigned int bn)
{
   return bn / BTS_IN_CH ;
}

void _print_bits_of_char(unsigned char c, unsigned int nbts)
{
   if (nbts > BTS_IN_CH)   nbts = BTS_IN_CH ;   // ???

   unsigned int   pos = nbts - 1 ;   // the highest bit
   for (unsigned int i = 0 ; i < nbts ; ++i, --pos) {
      printf("%c", _is_bit_on(c, pos) ? '1' : '0') ;
      if (i == nbts - 5)   printf (" ") ;
   }
}


// eof bitmap.c
