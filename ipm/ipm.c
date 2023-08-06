// ipm.c: implementation of DL IP address math - in C language
//


#include "ipm.h"


// private helpers
#define SWAP_UC(uc1, uc2)   ((uc1) ^= (uc2), (uc2) ^= (uc1), (uc1) ^= (uc2))
static uint32_t reorder_ui(uint32_t ui) ;


// public interface

uint32_t                                                    // as /24 to ui
mask_to_ui(char mask)                                       // no validity
{
   uint32_t   wm = 0xFFFFFFFF ;
   for (int i = 0 ; i < MAX_MASK_L - mask ; ++i)   UNSET_BIT(wm, i) ;
   return wm ;
}

void                                                        //
get_broadcast_address(char* ip_addr, char mask, char* output_buffer)
{
   uint32_t   wuip = get_ip_integer_equivalent(ip_addr) ;
   wuip |= ~(mask_to_ui(mask)) ;

   get_abcd_ip_format(wuip, output_buffer) ;
}


uint32_t                                                    // @return:
get_ip_integer_equivalent(char* ip_addr)                    // network UI
{
   uint32_t   wui = host_ip_to_ui(ip_addr) ;
   return reorder_ui(wui) ; // htonl(wui) ;
}

void                                                        // from network UI
get_abcd_ip_format(uint32_t ip, char* output_buffer)
{
   void*          pn = &ip ;
   unsigned char* ptr = pn ; ptr += sizeof(ip) - 1 ;

   for (size_t i = 0 ; i < sizeof(ip) ; ++i, --ptr) {
      output_buffer = ui_to_digits(*((unsigned char*)ptr), output_buffer) ;
      *output_buffer++ = '.' ;
   }
   *(--output_buffer) = 0 ;
}

void                                                        //
get_network_id(char* ip_addr, char mask, char* output_buffer)
{
   uint32_t   wuip = get_ip_integer_equivalent(ip_addr) ;
   wuip &= mask_to_ui(mask) ;

   get_abcd_ip_format((wuip), output_buffer) ;
}

uint32_t                                                    //
get_subnet_cardinality(char mask)
{  // max # = (2 ^ (32 - mask)) - 2
   return (1 << (32 - (unsigned int)mask)) - 2 ;
}

int                                                         //
check_ip_subnet_membership(char* network_id, char mask, char* check_ip)
{
   uint32_t   check_u = get_ip_integer_equivalent(check_ip) ;
   check_u &= mask_to_ui(mask) ;

   uint32_t   net_u= get_ip_integer_equivalent(network_id) ;

   return net_u == check_u ? 0 : -1 ;
}


// (private) helpers

uint32_t                                                    // ip to Host UI
host_ip_to_ui(char* ip_addr)
{
   uint32_t   wui = 0 ;
   void*      ptr = &wui ;
   for (size_t i = 0 ; i < sizeof(wui) ; ++i, ++ptr) {
      *((unsigned char *)ptr) = digits_to_ui(&ip_addr) ;
      ++ip_addr  ; // was over the delimiter - move it
   }
   return wui ;
}

unsigned char
digits_to_ui(char** digs)                                   // seq of Digits to uchar
{
   char*           d = *digs ;
   unsigned char   num = 0 ;
   for ( ; *d >= '0' && *d <= '9' ; ++d) {
      num = num * 10 + (*d - '0') ;
   }
   *digs = d ;
   return num ;
}

unsigned char*                                              // @return - end()
ui_to_digits(unsigned char num, char* digs)                 // UChar to digits
{
   char   txt[4] = { 0, 0, 0, 0 } ;
   char*  p = txt ;
   do {
      *p++ = '0' + num % 10, num /= 10 ;
   } while (num != 0) ;

   for (--p ; p >= txt ; --p)   *digs++ = *p ;
   return digs ;
}

static uint32_t reorder_ui(uint32_t ui) { // as htonl(uint32_t)
   void *ptr = &ui ;
   unsigned char* pb = ptr ;
   unsigned char* pe = pb + sizeof(ui) - 1 ;

   SWAP_UC(*pb, *pe), SWAP_UC(*(pb + 1), *(pe - 1)) ;
   return ui ;
}

// eof ipm.c
