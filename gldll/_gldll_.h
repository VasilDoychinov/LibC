// _gldll_.h: PRIVATE: definitiions and declarations to implement
//                     Double-linked Lists to glue data upon
//


#ifndef _H_GLDLL_LIB_HEADER
#define _H_GLDLL_LIB_HEADER

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

#define TRUE  (0 == 0)
#define FALSE (0 != 0)
#define true  (0 == 0)
#define false (0 != 0)

#define NO_ERROR   0
#define INVALID_   -1


struct ListGLDL_ {

   struct NodeGLDL_*   _head ;   // the Leftmost
   struct NodeGLDL_*   _end ;    // the Rightmost
   unsigned int        _offs ;   // the Offset in the Structure to be glued

   // callbacks
   CFunction_t   _key_match ;  // 0: match, <0: lhs < rhs, >0: lhs > rhs
} ;


// PRIVATE: operations(helpers) follow


// GLDLL general(basic) - in gldll.c

int _add_gldll_node_front(ListGLDL_t *l, NodeGLDL_t *node) ;
int _add_gldll_node_end(ListGLDL_t *l, NodeGLDL_t *node) ;

void*       _remove_node(NodeGLDL_t* node) ;

// DLL utils - in dll_util.c

_H_GLDLL_LIB_HEADER
#endif

// eof dll.h
