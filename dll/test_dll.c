// test_dll.c: to test the implementation of DLL library
// source code of the library to be found in LinuxC/libraries/dll/

#include <stdio.h>

#include "../libraries/dll/dll.h"

void print_int_element(void *) ;

void test_remove_ptr(ListDL_t* dll, int test_data[], int test_size) ;

int main()
{
   int   test_data[20] ;
   const int test_size = sizeof(test_data) / sizeof(int) ;
   for (int i = 0 ; i < test_size ; ++i)    test_data[i] = i ;

   ListDL_t   *dll = get_new_dll() ;
   if (!dll)  {
      fprintf(stderr, "\n> Memory allocation error: no empty list created. Exit\n\n") ;
       return 0 ;
   }
   printf("\n: the new List is empty (expected 0): %d", is_dll_empty(dll)) ;

   for (int i = 0 ; i < test_size ; i++) {
       if (add_data_to_dll(dll, test_data + i) != NO_ERROR) {
          fprintf(stderr, "\n> adding element #%d error. Stopped.", i) ;
          break ;
       }
   }
   printf("\n: the new List is NOT empty (expected -1): %d", is_dll_empty(dll)) ;

   printf("\n: the list holds %d elements: { ", test_size) ;
   dll_for_each(dll, print_int_element);
   printf("}") ;

   test_remove_ptr(dll, test_data, test_size) ;

   printf("\n: the reversed list is: { ") ;
   dll_reverse(dll), dll_for_each(dll, print_int_element);
   printf("}") ;


   remove_data_from_dll_by_data_ptr(dll, test_data) ;
   printf("\n: '0' is to be removed: { "), dll_for_each(dll, print_int_element);
   printf("}") ;

   drain_dll(dll) ;
   printf("\n: expected empty list: %d -> { ", is_dll_empty(dll)) ;
   dll_for_each(dll, print_int_element), printf("}") ;

   printf("\n\n> That's it...\n") ;
   return 0 ;
}

void print_int_element(void *data)
{
   printf("%d ", *((int *)data)) ;
}

void test_remove_ptr(ListDL_t* dll, int test_data[], int test_size)
{
   // for (int i = test_size - 1 ; i > 0 ; --i) {
   // for (int i = 0 ; i < test_size ; ++i) {
   for (int i = 0 ; i < test_size / 2 ; ++i) {
      // int j = i ;
      int  j = test_size / 2 ; j += (i % 2 ? i : -i) ;
      printf("\n: removing element %d", j) ;
      if (j >= 0 && j < test_size) remove_data_from_dll_by_data_ptr(dll, &(test_data[j])) ;
      printf("\n: result: { "), dll_for_each(dll, print_int_element), printf("}") ;
   }
}
