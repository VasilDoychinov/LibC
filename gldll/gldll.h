// gldll.h: PUBLIC: definitiions and declarations to implement Double-linked Lists
//


#ifndef _H_GLDLL_HEADER
#define _H_GLDLL_HEADER

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>



typedef void (*NFunction_t)(void *) ;
typedef int  (*CFunction_t)(void *, void *) ;

typedef struct NodeGLDL_ NodeGLDL_t ;
typedef struct ListGLDL_ ListGLDL_t ;


struct NodeGLDL_ {
    struct NodeGLDL_*   _left ;
    struct NodeGLDL_*   _right ;
} ;


#define offsetof(struct_name, field_name) \
        ((unsigned long)(&(((struct_name *)0)->field_name)))

#define GLNODE_TO_BASE(func_name, base_name, field_name)   \
                                                       \
static inline base_name* func_name(NodeGLDL_t* node) {     \
return (base_name *)((char *)node - offsetof(base_name, field_name)) ; \
}



// operations follow

// DLL general(basic) - in dll.c

// init_gldll(): set a variable in an initilal state
void init_gldll(ListGLDL_t* l, unsigned int offs) ;
void init_glnode(NodeGLDL_t* node) ;

// get_new_dll(): get an empty list (dl)
ListGLDL_t* get_new_gldll(unsigned int offset) ;

// is_dll_empty() - @return - 0 = empty, -1 = NOT empty
int is_gldll_empty(ListGLDL_t* l) ;

// register a callback to match _data to a Key
// void gldll_register_key_match(ListGLDL_t* dll, CFunction fm) ;

// add data: @return - if successful(0), -1: otherwise
int gldll_add(ListGLDL_t* l, NodeGLDL_t* nn) ;    // in front
int gldll_append(ListGLDL_t* l, NodeGLDL_t* nn) ; // ... end

// removes the node that holds the link - no memory release
// @return - NO_ERROR: success, INVALID_ - failure(not found)
int gldll_remove(ListGLDL_t* l, NodeGLDL_t* nn) ;

// GLDLL utils - in gldll_util.c

void gldll_for_each(ListGLDL_t* l, NFunction_t f) ;

/*

void  dll_reverse(ListGLDL_t* dll) ;

void* dll_search_by_key(ListGLDL_t* dll, void* key) ;
 */


_H_GLDLL_HEADER
#endif

// eof gldll.h
