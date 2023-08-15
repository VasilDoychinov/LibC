// bitsop.h

/*
 * Bit programming Questions and Assignments.

    Create a file bitsop.h and write the implementation of below macros.

     bitsop.h #include stadint.h file.
     Assume n is uint32_t type integer. bit is any number in power of 2 not exceeding 2 ^ 31.

     LSB is designated as 0th bit, and MSB as 31st bit.

    1. Write a function which print the bit pattern of a uint32_t number n.
        For example, if n = 40, then output should be 0010 1000
        void print_bit_pattern(uint32_t n).
        Note : use above fn to verify the solution of correctness of subsequent questions.

    2. Must set xth bit in number n, where bit = 2 ^ x.
        #define SET_BIT(n, bit)

    3. Must unset xth bit in number n, where bit = 2 ^ x.
        #define UNSET_BIT(n, bit )

    4. MUST return TRUE or FALSE depending on xth bit is set or not.
        #define  IS_BIT_SET(n, bit)

    5. Must Toggle xth bit in number not
        #define TOGGLE_BIT(n, bit)

    6. must compute the complement of number n. n itself should not get modified.
        #define COMPLEMENT(n)

    7. fn which returns number of bits set in uint32_t number n.
        For example, for n = 40, it should return 2 because binary of 40 is 0010 1000
        uint8_t count_bit_set(uint32_t n);

    8. Rotate the bit pattern of number n by k units towards right.

        For example, if n = 40 , binary = 0010 1000 and if k = 4,
        then resultatnt bit pattern should be 1000 0010
        ( i have ignored number of leading consecutive zeros in
        binary bit pattern in the example, but those are there )

    9. Given an IP Address and a mask value - 20.1.1.2/24.
        Apply the Mask on IP Address and print
        the bit pattern of resultant ip address obtained.

    10. Given a 32 bit integer, and two integers p and q such that 0 <= p < q <= 31,
        which represent bit positions, print equivalent integer formed by bits in
        interval [p, q] (p, q inclusive) and remaining bits set to zero.

    11. Test whether the integer n is a power of two or not ?
        bool isPowerOfTwo(uint32_t n);
 */


#ifndef _H_BITSOP_HEADER
#define _H_BITSOP_HEADER

#include <stdint.h>
#include <stdio.h>

#define IS_BIT_H(n, pos)   (((n) & (1 << (pos))) != 0)
#define IS_BIT_SET(n, bit) (((n) & (bit)) != 0)

#define SET_POS(n, pos)    (n |= (1 << (pos)))
#define SET_BIT(n, bit)    (n |= (bit))
#define UNSET_BIT(n, bit)  (n &= ~(bit))
#define TOGGLE_BIT(n, bit) (n ^= (bit))
#define COMPLEMENT(n)      ~(n)

// function prototypes

void     print_bit_pattern(uint32_t n) ;
uint8_t  count_bit_set(uint32_t n);
int      isPowerOfTwo(uint32_t n) ;

// extract_bits(): within [p, q]
uint32_t extract_bits(uint32_t num, uint8_t p, uint8_t q) ;
// rotate_....() : k <= bucket_size
uint32_t right_rotate_bits(uint32_t n, uint8_t k, uint8_t bucket_size) ;


_H_BITSOP_HEADER
#endif
// eof bitsop.h
