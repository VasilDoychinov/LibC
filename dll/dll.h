// dll.h: PUBLIC: definitiions and declarations to implement Double-linked Lists
//


#ifndef _H_DLL_HEADER
#define _H_DLL_HEADER

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>



typedef void (*NFunction_t)(void *) ;
typedef int  (*CFunction_t)(void *, void *) ;

typedef struct NodeDL_ NodeDL_t ;
typedef struct ListDL_ ListDL_t ;


// operations follow

// DLL general(basic) - in dll.c

// get_new_dll(): get an empty list (dl)
ListDL_t* get_new_dll() ;
// drain_dll(): remove all nodes - do not free the data
void drain_dll(ListDL_t* dll) ;
// is_dll_empty() - @return - 0 = empty, -1 = NOT empty
int is_dll_empty(ListDL_t* dll) ;

// register a callback to match _data to a Key
void dll_register_key_match(ListDL_t* dll, int (*cb_key_match)(void*, void*)) ;

// add data: @return - if successful(0), -1: otherwise
int add_data_to_dll(ListDL_t* dll, void* data) ;
int dll_sorted_insert(ListDL_t* dll, void* data) ;

// removes the node that holds the link - no memory release
// @return - NO_ERROR: success, INVALID_ - failure(not found)
int remove_data_from_dll_by_data_ptr(ListDL_t* dll, void *dptr) ;


// DLL utils - in dll_util.c

void  dll_for_each(ListDL_t* dll, NFunction_t f) ;

void  dll_reverse(ListDL_t* dll) ;

void* dll_search_by_key(ListDL_t* dll, void* key) ;

_H_DLL_HEADER
#endif

// eof dll.h
