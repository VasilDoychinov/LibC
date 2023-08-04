// dll.h: definitiions and declarations to implement Double-linked Lists
//


#ifndef _H_DLL_HEADER
#define _H_DLL_HEADER

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

#define TRUE  (0 == 0)
#define FALSE (0 != 0)

#define NO_ERROR   0
#define INVALID_   -1

typedef void (*NFunction_t)(void *) ;

typedef struct NodeDL_ {
    void*             _data ;
    struct NodeDL_*   _left ;
    struct NodeDL_*   _right ;
} NodeDL_t ;

typedef struct ListDL_ {

  NodeDL_t*   _head ;   // the Leftmost
  NodeDL_t*   _end ;    // the Rightmost

} ListDL_t ;

// operations follow

// DLL general(basic) - in dll.c

// get_new_dll(): get an empty list (dl)
ListDL_t* get_new_dll() ;
// drain_dll(): remove all nodes - do not free the data
void drain_dll(ListDL_t* dll) ;
// is_dll_empty() - @return - 0 = empty, -1 = NOT empty
int is_dll_empty(ListDL_t* dll) ;

// add_data_to_dll()L @return - if successful
int add_data_to_dll(ListDL_t* dll, void* data) ;

// removes the node that holds the link - no memory release
// @return - NO_ERROR: success, INVALID_ - failure(not found)
int remove_data_from_dll_by_data_ptr(ListDL_t* dll, void *dptr) ;


// DLL utils - in dll_util.c

void dll_for_each(ListDL_t* dll, NFunction_t f) ;

void dll_reverse(ListDL_t* dll) ;


_H_DLL_HEADER
#endif

// eof dll.h
