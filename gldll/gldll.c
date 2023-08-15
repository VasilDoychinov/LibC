// dll.c: implementation of DL List operations - in C language
//

#include "gldll.h"
#include "_gldll_.h"


// private helpers
void _remove_glnode(ListGLDL_t* l, NodeGLDL_t* node) ;


// public interface

ListGLDL_t*
get_new_gldll(unsigned int offs)
{
   ListGLDL_t* wl = calloc(1, sizeof(ListGLDL_t)) ;
   if (wl != NULL)   wl->_head = wl->_end = NULL, wl->_offs = offs ;

   return wl ;
}

void                                                 // no validity checks
init_gldll(ListGLDL_t *l, unsigned int offs)
{
   l->_head = l->_end = NULL ;
   l->_offs = offs ;
}

void init_glnode(NodeGLDL_t* node) { node->_left = node->_right = NULL ; }

// is_gldll_empty() - @return - 0 = empty, -1 = NOT empty
int is_gldll_empty(ListGLDL_t* l)
{
   return l->_head == NULL ? 0 : -1 ;
}


int
gldll_add(ListGLDL_t *l, NodeGLDL_t* node)
{
   if (!l || !node)   return INVALID_ ;

   return _add_gldll_node_front(l, node) ;
}

int
gldll_append(ListGLDL_t *l, NodeGLDL_t* node)
{
   if (!l || !node)   return INVALID_ ;

   return _add_gldll_node_end(l, node) ;
}

int gldll_remove(ListGLDL_t* l, NodeGLDL_t* nn)
{
   if (!l || !nn)   return INVALID_ ;

   _remove_glnode(l, nn) ;
   return NO_ERROR ;
}


// private helpers

void _remove_glnode(ListGLDL_t* l, NodeGLDL_t* node)    // @return - pointer to data
{
   if (node->_left && node->_right) {                // L & R neighbours
       node->_left->_right = node->_right, node->_right->_left = node->_left ;
   } else if (node->_left) {                         // Left neighbour only
       node->_left->_right = NULL, l->_end = node->_left ;
   } else if (node->_right) {                        // Right neoghbour only
       node->_right->_left = NULL, l->_head = node->_right ;
   } else {                                          // one element only
       l->_head = l->_end = NULL ;
   }

   return ;
}


// add a node to the front
int _add_gldll_node_front(ListGLDL_t *l, NodeGLDL_t *node)
{
   // no validation checks
   if (!l->_head) {
      l->_head = l->_end = node ;
      node->_left = node->_right = NULL ;
      return NO_ERROR ;
   }

   l->_head->_left = node, node->_right = l->_head ;  // connect the new
   l->_head = node, node->_left = NULL ;              // node is in the front
   return NO_ERROR ;
}

// add a node to the end
int _add_gldll_node_end(ListGLDL_t *l, NodeGLDL_t *node)
{
    // printf(" END ") ;
   // no validation checks
   if (!l->_end) {
      l->_head = l->_end = node ;
      node->_left = node->_right = NULL ;
      return NO_ERROR ;
   }

   l->_end->_right = node, node->_left = l->_end ;  // connect the new
   l->_end = node, node->_right = NULL ;            // node is in the end
   return NO_ERROR ;
}

/*

void dll_register_key_match(ListDL_t* dll, int (*cb_key_match)(void*, void*))
{
   dll->_key_match = cb_key_match ;
}

*/

// eof dll.c
