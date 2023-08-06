// test_ipm.c: to test the implementation of IP math (ipm) library
// source code of the library to be found in LinuxC/libraries/ipm/

#include <stdio.h>
#include <memory.h>
#include <arpa/inet.h>

#include "../libraries/ipm/ipm.h"

#define true  (0 == 0)
#define false (0 != 0)

void print_bits(uint32_t n) ;
void testing_bit_ops() ;
void testing_mask_conversion() ;
void testing_subnet_cardinality() ;
void testing_ui_string_conversions() ;
void testing_ip_integer_conversions() ;
void testing_broadcast_addr() ;
void testing_subnet_id() ;
void testing_membership() ;

int main()
{
   if (false)   testing_ui_string_conversions() ;
   if (false)   testing_bit_ops() ;
   if (false)   testing_mask_conversion() ;
   if (false)   testing_subnet_cardinality() ;

   if (false)   testing_ip_integer_conversions() ;

   if (false)   testing_broadcast_addr() ;
   if (false)   testing_subnet_id() ;

   if (true)   testing_membership() ;

   printf("\n\n> That's it...\n") ;
   return 0 ;
}


void testing_membership()
{
   char   test_addr[] = "192.168.2.0" ; // "10.1.23.10/20" ;// "10.1.23.10" ; //  ;
   char   mask = 24 ;
   printf("\n\n:  testing subnet id ...") ;
   char   result_addr[PREFIX_LEN + 1] = "192.168.1.33";

   printf("\n: %s is a member of %s: %s", result_addr, test_addr,
          check_ip_subnet_membership(test_addr, mask, result_addr) == 0 ? "true" : "false") ;
   printf("\n> Done.") ;
}


void testing_subnet_id()
{
   char   test_addr[] = "192.168.2.10" ; // "10.1.23.10/20" ;// "10.1.23.10" ; //  ;
   char   mask = 24 ;
   printf("\n\n:  testing subnet id ...") ;

   char   result_addr[PREFIX_LEN + 1] ;
   get_network_id(test_addr, mask, result_addr) ;

   printf("\n: %s / %u -> %s. Done.", test_addr, mask, result_addr) ;

}

void testing_broadcast_addr()
{
   char   test_addr[] = "10.1.23.10" ;// "10.1.23.10" ; // "192.168.2.10" ;
   char   mask = 20 ;
   printf("\n\n:  testing broadcast address ...") ;

   char   result_addr[PREFIX_LEN + 1] ;
   get_broadcast_address(test_addr, mask, result_addr) ;

   printf("\n: %s / %u -> %s. Done.", test_addr, mask, result_addr) ;
}

void testing_ip_integer_conversions()
{
   char   test_addr[] = "10.1.23.10" ; // "10.1.23.10" ; // "192.168.2.10" ;
   printf("\n\n:  testing conversions ip <-> network UI ...") ;

   uint32_t   ia = get_ip_integer_equivalent(test_addr) ;

   printf("\n\n: %s -> %u {", test_addr, ia) ;
   for (int i = 0 ; i < sizeof(ia) ; i++) {
      void* p = &ia ;
      unsigned char* ptr = (unsigned char*)p + i ;
      printf(" %u", *ptr) ;
   }
   printf(" } -> reversed: ") ;

   char   ip_addr[PREFIX_LEN + 1] ;
   get_abcd_ip_format(ia, ip_addr);
   printf(" %s. Done", ip_addr) ;
}

void testing_ui_string_conversions()
{
   printf("\n\n> testing ui - string conversions") ;
   for (unsigned char i = 0 ; i < 255 ; i++) {
       char   txt[4] = {0, 0, 0, 0 } ;
       char*  ptr = ui_to_digits(i, txt) ; *ptr = 0 ;
       ptr = txt ;
       unsigned char wu = digits_to_ui(&ptr) ;

       if (wu != i || *ptr != 0) {
           printf("\n: error expected %d (%d), expected 0(%d)", i, wu, *ptr) ;
       }
   }
   printf("\n> testing ui - string conversions: Done.") ;
}

void testing_subnet_cardinality()
{
   printf("\n\n> testing subnet cardinality") ;
   for (int i = 2 ; i < 31 ; ++i)   {
      printf("\n: mask %2d -> cardinality = %u", i, get_subnet_cardinality(i));
   }
   printf("\n: testing cardinality: Done.\n");
}

void testing_mask_conversion()
{
   printf("\n\n> testing mask to UI conversion") ;
   for (int i = 0 ; i <= MAX_MASK_L ; ++i) {
       printf("\n: mask %2d -> ", i), print_bits(mask_to_ui(i)) ;
   }
   printf("\n: testing mask conversion: Done.\n");
}

void testing_bit_ops()
{
   int   test_data[MAX_MASK_L] ;
   const int test_size = sizeof(test_data) / sizeof(int) ;
   for (int i = 0 ; i < test_size ; ++i)    test_data[i] = i ;

   if (true){ // test IS_BIT_SET()
       printf("\n> testing IS_BIT_SET()") ;
       for (int i = 0 ; i < test_size ; ++i)   {
           printf("\n: %2d -> ", test_data[i]), print_bits(test_data[i]) ;
       }
   }

   if (true) { // test SET_BIT()
       printf("\n> testing SET_BIT()") ;
       for (int i = 0 ; i < test_size ; ++i)   {
           int   n = 0 ;
           printf("\n: %2d -> ", i), print_bits(SET_BIT(n, i)) ;
       }
   }
   if (true) { // test UNSET_BIT()
       printf("\n> testing UNSET_BIT()") ;
       for (int i = 0 ; i < test_size ; ++i)   {
           int   n = 0xFFFFFFFF ; printf("\n: %2d -> ", i), print_bits(UNSET_BIT(n, i)) ;
       }
   }
   if (true) { // test TOGGLE_BIT()
       printf("\n> testing TOGGLE_BIT()") ;
       for (int i = 0 ; i < test_size ; ++i)   {
           int   n = 0 ; printf("\n: %2d -> ", i), print_bits(TOGGLE_BIT(n, i)) ;
           n = 0xFFFFFFFF ; printf("\n: %2d -> ", i), print_bits(TOGGLE_BIT(n, i)) ;
       }
   }
   printf("\n: testing bit ops: Done.\n");
} // testing_bit_ops()


void print_bits(uint32_t n)
{
   printf("{ ") ;
   for (int i = sizeof(n) * 8 - 1 ; i >= 0 ; --i) {
       printf("%c", IS_BIT_SET(n, i) ? '1' : '0') ;
       if (i % 8 == 0)   printf (" ") ;
   }
   printf(" }") ;
}
