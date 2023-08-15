// gldll_util.c: implementation of DLL utilities (some)
//


#include "gldll.h"
#include "_gldll_.h"


// do 'f' for each element
void gldll_for_each(ListGLDL_t* l, NFunction_t f)
{
   if (l)   {
      NodeGLDL_t* __curr ;
      for (NodeGLDL_t* curr = l->_head ; curr ; curr = __curr) {
         __curr = curr->_right ;            // delete-safe: as a reminder, only
         f((char *)curr - l->_offs) ;
      }
   }
}

/*
// reverse the list
void dll_reverse(ListDL_t* dll)
{
    NodeDL_t*   cn = dll->_head ;
    for (NodeDL_t* wn = NULL ; cn ; cn = wn) {
        wn = cn->_right, cn->_right = cn->_left, cn->_left = wn ;
    }
    cn = dll->_end, dll->_end = dll->_head, dll->_head = cn ;
}

void*                                           // search by 'key'
dll_search_by_key(ListDL_t* dll, void* key)     // @return: pointer to _data
{
    if (dll && dll->_key_match && key)   {
      CFunction_t  comp = dll->_key_match ;

      for (NodeDL_t* curr = dll->_head ; curr ; curr = curr->_right) {
         if (comp(curr->_data, key) == 0)   return curr->_data ;
      }
   }
   return NULL ;
}
*/

// eof gldll_util.c
