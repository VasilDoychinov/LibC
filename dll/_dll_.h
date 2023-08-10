// _dll_.h: PRIVATE: definitiions and declarations to implement Double-linked Lists
//


#ifndef _H_DLL_LIB_HEADER
#define _H_DLL_LIB_HEADER

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

#define TRUE  (0 == 0)
#define FALSE (0 != 0)
#define true  (0 == 0)
#define false (0 != 0)

#define NO_ERROR   0
#define INVALID_   -1


struct NodeDL_ {
   void*             _data ;
   struct NodeDL_*   _left ;
   struct NodeDL_*   _right ;
} ;

struct ListDL_ {

   struct NodeDL_*   _head ;   // the Leftmost
   struct NodeDL_*   _end ;    // the Rightmost

   // callbacks
   CFunction_t   _key_match ;  // 0: match, <0: lhs < rhs, >0: lhs > rhs
} ;


// PRIVATE: operations(helpers) follow


// DLL general(basic) - in dll.c

int _add_dll_node_front(ListDL_t *l, NodeDL_t *node) ;
int _add_dll_node_end(ListDL_t *l, NodeDL_t *node) ;

NodeDL_t* _new_node(void* data) ;
void*     _remove_node(ListDL_t* dll, NodeDL_t* node) ;

// DLL utils - in dll_util.c

_H_DLL_LIB_HEADER
#endif

// eof dll.h
