// dll.c: implementation of DL List operations - in C language
//


#include "dll.h"


// private helpers

int _add_dll_node_front(ListDL_t *l, NodeDL_t *node) ;
int _add_dll_node_end(ListDL_t *l, NodeDL_t *node) ;

NodeDL_t* _new_node(void* data) ;

// public interface

ListDL_t* get_new_dll()
{
   ListDL_t* wl = calloc(1, sizeof(ListDL_t)) ;
   if (wl != NULL)   wl->_head = wl->_end = NULL ;

   return wl ;
}

int add_data_to_dll(ListDL_t *l, void *data)
{
   if (!l || !data)   return INVALID_ ;

   NodeDL_t*   wn = _new_node(data) ;
   if (!wn)    return INVALID_ ;

   return _add_dll_node_front(l, wn) ;
}

void dll_for_each(ListDL_t* l, NFunction_t f)
{
   if (l)   {
       for (NodeDL_t* curr = l->_head ; curr ; curr = curr->_right) {
           f(curr->_data) ;
       }
   }
}

void dll_reverse(ListDL_t* dll)
{
   NodeDL_t*   cn = dll->_head ;
   for (NodeDL_t* wn = NULL ; cn ; cn = wn) {
      wn = cn->_right, cn->_right = cn->_left, cn->_left = wn ;
   }
   cn = dll->_end, dll->_end = dll->_head, dll->_head = cn ;
}


// private helpers

NodeDL_t* _new_node(void* data) {   // @return - new node for @data
   NodeDL_t*   wn = calloc(1, sizeof(NodeDL_t)) ;
   if (wn)  wn->_left = wn->_right = NULL, wn->_data = data ;

   return wn ;
}

// add a node to the front
int _add_dll_node_front(ListDL_t *l, NodeDL_t *node)
{
   // no validation checks
   if (!l->_head) { l->_head = l->_end = node ; return NO_ERROR ; }

   l->_head->_left = node, node->_right = l->_head ;  // connect the new
   l->_head = node ;
   return NO_ERROR ;
}

// add a node to the end
int _add_dll_node_end(ListDL_t *l, NodeDL_t *node)
{
   // no validation checks
   if (!l->_end) { l->_head = l->_end = node ; return NO_ERROR ; }

   l->_end->_right = node, node->_left = l->_end ;  // connect the new
   l->_end = node ;
   return NO_ERROR ;
}


// eof dll.c
