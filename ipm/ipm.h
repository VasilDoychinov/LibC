// ipm.h: definitiions and declarations to implement IP addresses calculation
//    NB: - all output buffers to be able to hold at least PREFIX_LEN bytes
//        - all input addresses to hold PREFIX_LEN(\0 incl.) valid bytes
//        - uint32_t used for compatibility's sake
//        - big-endian format followed, only
//        - all parameters assumed correct: no validity checks
//
//    NB: standard C library conversion function are NOT to be used
//


#ifndef _H_IPM_HEADER
#define _H_IPM_HEADER


#include <stdlib.h>
#include <stdint.h>
#include <arpa/inet.h>


#define PREFIX_LEN      16        // the max length of an IP address (\0 incl.)
#define MAX_MASK_L      32        // for IPv4 - 32 bits; mask in [0, 32]

// macros for bit operaations

#define IS_BIT_SET(n, pos)   (((n) & (1 << (pos))) != 0)
#define SET_BIT(n, pos)      (n |= (1 << (pos)))
#define UNSET_BIT(n, pos)    (n &= ~(1 << (pos)))
#define TOGGLE_BIT(n, pos)   (n ^= (1 << (pos)))


void get_broadcast_address(char* ip_addr, char mask, char* output_buffer) ;

// ip to integer network format
uint32_t get_ip_integer_equivalent(char* ip_addr) ;

void get_abcd_ip_format(unsigned int ip, char* output_buffer) ;

void get_network_id(char* ip_addr, char mask, char* output_buffer) ;

uint32_t get_subnet_cardinality(char mask) ;

int check_ip_subnet_membership(char* network_id, char mask, char* check_ip) ;

// helpers

uint32_t host_ip_to_ui(char* ip_addr) ;
uint32_t mask_to_ui(char mask) ;  // as /24 to ui: no validity checks

unsigned char  digits_to_ui(char**) ;
unsigned char* ui_to_digits(unsigned char, char*) ;


_H_IPM_HEADER
#endif

// eof ipm.h
