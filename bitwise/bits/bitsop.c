// bitsop.s
//


#include "bitsop.h"

void
print_bit_pattern(uint32_t n)
{
   printf("{ ") ;
   uint32_t   mask = 1 << (sizeof(n) * 8 - 1) ;
   for (int i = (sizeof(n) * 8 - 1) ; i >= 0 ; --i, mask >>= 1) {
      printf("%c", n & mask ? '1' : '0') ;

      if (i % 8 == 0)   printf (" /") ;
      if (i % 4 == 0)   printf (" ") ;
   }
   printf("\b\b}") ;
}

uint8_t count_bit_set(uint32_t n)
{
   uint8_t   count = 0 ;
   for (int i = sizeof(n) * 8 - 1 ; i >= 0 ; --i, n >>= 1) {
      if (n & 1)   ++count ;
      // if (IS_BIT_H(n, i))   ++count ;
   }
   return count ;
}


uint32_t extract_bits(uint32_t num, uint8_t p, uint8_t q)
{
   uint32_t mask = ~0;

   // bits [q+1, ---] to 0
   mask <<= (sizeof(num) * 8 - 1 - q),  mask >>= (sizeof(num) * 8 - 1 - q) ;
   // bits [0, p-1] to 0
   mask >>= p, mask <<= p  ; // set bits [0, p-1] to 0

   return (num & mask);     // apply the mask to the original number
}

uint32_t
right_rotate_bits(uint32_t n, uint8_t k, uint8_t bucket_size) // k <= bucket_size
{
   uint32_t mask = 0;            // for to get the RIGHTmot k-bits
   for (int i = 0 ; i < k ; ++i)   SET_POS(mask, i) ;

   uint32_t w2 = n & mask ;      // w2 holds the rightmost k-bits, only
   w2 <<= bucket_size * 8 - k ;  // rotate the off-scene bits

   n >>= k ;                     // k-bits off the scene; the rest - forwared

   return n | w2 ;
}


int isPowerOfTwo(uint32_t n)
{
   return n > 0 && (!(n & (n - 1))) ;
}

// eof bitsop.c
