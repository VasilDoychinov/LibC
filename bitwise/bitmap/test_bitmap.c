// test_bits.c
//

#include "../libraries/bitmap/bitmap.h"


int
main()
{
   unsigned int   nb = 19 ;
   BitMap_t*   bm = bitmap_create(nb) ;
   if (bm)   {
      printf("\n: expecting %u LOW           : ", nb), bitmap_print(bm) ;

      bitmap_set_all(bm) ;
      printf("\n: expecting %u HIGH          : ", nb), bitmap_print(bm) ;
      printf("\n: all bits HIGH: %s", bitmap_is_full(bm) ? "yes" : "no") ;
      bool fl = false ;
      ITERATE_BITMAP_BEGIN(bm, fl) {
          if (!fl)    printf("\n: unset bit found") ;
      } ITERATE_BITMAP_END(bitmap_ptr , bit_state)

      bitmap_unset_bit(bm, 18) ;
      printf("\n> bit 18 cleared: "), bitmap_print(bm) ;
      printf("\n: all bits HIGH: %s", bitmap_is_full(bm) ? "yes" : "no") ;

      bitmap_clear(bm) ;
      printf("\n: expecting %u LOW           : ", nb), bitmap_print(bm) ;

      for (int i = 0 ; i < nb ; i++)    {
         if (i % 2) bitmap_set_bit(bm, i) ;
      }
      printf("\n\n: expecting ODDs         HIGH: "), bitmap_print(bm) ;
      printf("\n: all bits HIGH: %s", bitmap_is_full(bm) ? "yes" : "no") ;
      for (int i = 0 ; i < bitmap_size(bm) ; ++i) {
         if (!bitmap_is_bit_set(bm, i) && i % 2)   printf("\n: test odds failed...") ;
      }
      printf("\n: testing odds: done.") ;

      for (int i = 0 ; i < nb ; i++)    {
         if (i % 2) bitmap_unset_bit(bm, i) ;
         else       bitmap_set_bit(bm, i) ;
      }
      printf("\n\n: expecting        COMPLEMENT: "), bitmap_print(bm) ;
      for (int i = 0 ; i < bitmap_size(bm) ; ++i) {
         if (bitmap_is_bit_set(bm, i) && i % 2)   printf("\n: test complements failed...") ;
      }
      printf("\n: testing complement: done.") ;

      bitmap_free(bm) ;
   }

   printf("\n\n> That's it...\n") ;
   return 0 ;
}
