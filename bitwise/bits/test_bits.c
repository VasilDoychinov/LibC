// test_bits.c
//

#include "../libraries/bits/bitsop.h"


int
main()
{
   unsigned int   wi = 40 ;

   printf("\n\n> the bit pattern of %d is: ", wi), print_bit_pattern(wi) ;

   printf("\n> right_rotate by %d in %d: ", 4, 2), print_bit_pattern(right_rotate_bits(wi, 4, 2)) ;

/*   printf("\n> extracted        [0, 31]: "), print_bit_pattern(extract_bits(~0, 0, 31)) ;
   printf("\n> extracted        [1, 30]: "), print_bit_pattern(extract_bits(~0, 1, 30)) ;

   printf("\n> is (16|8)_power_of_2: %d", _isPowerOfTwo(128)) ;
   printf("\n> is (16|8) power of 2: %d", isPowerOfTwo(128)) ;
*/
   printf("\n\n> That's it...\n") ;
   return 0 ;
}
