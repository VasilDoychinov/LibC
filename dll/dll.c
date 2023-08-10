// dll.c: implementation of DL List operations - in C language
//


#include "dll.h"
#include "_dll_.h"


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

int
dll_sorted_insert(ListDL_t* dll, void* data)
{
   if (!dll || !dll->_key_match || !data)   return INVALID_ ;

   NodeDL_t*  node = _new_node(data) ;
   if (node == NULL)                        return INVALID_ ;

   if (is_dll_empty(dll) == 0 || dll->_key_match(dll->_head->_data, data) >= 0)
                                 return _add_dll_node_front(dll, node) ;
   if (dll->_key_match(dll->_end->_data, data) <= 0)
                                 return _add_dll_node_end(dll, node) ;

   // there is at least one node > date and one < data
   for (NodeDL_t* curr = dll->_head->_right ; curr ; curr = curr->_right) {
      if (dll->_key_match(curr->_data, data) >= 0) {
         curr->_left->_right = node, node->_left = curr->_left ;
         curr->_left = node, node->_right = curr ;
         return NO_ERROR ;
      }
   }
   return INVALID_ ;
}

// drain_dll(): remove& free all nodes - do not free the data
void drain_dll(ListDL_t* dll)
{
   if (dll)   {
       for (NodeDL_t* curr = dll->_head ; curr ; curr = dll->_head) {
           dll->_head = curr->_right ;
           free(curr) ;
      }
      dll->_head = dll->_end = NULL ;
   }
}

// is_dll_empty() - @return - 0 = empty, -1 = NOT empty
int is_dll_empty(ListDL_t* dll)
{
   return dll->_head == NULL ? 0 : -1 ;
}

// removes the node that holds the link - no memory release
int remove_data_from_dll_by_data_ptr(ListDL_t* dll, void *dptr)
{
   if (!dll || !dptr)   return INVALID_ ;

   for (NodeDL_t* curr = dll->_head ; curr ; curr = curr->_right) {
      if (curr->_data == dptr)   {
         _remove_node(dll, curr) ;
         return NO_ERROR ;
      }
   }

   return INVALID_ ;
}

void dll_register_key_match(ListDL_t* dll, int (*cb_key_match)(void*, void*))
{
   dll->_key_match = cb_key_match ;
}

// private helpers

void* _remove_node(ListDL_t* dll, NodeDL_t* node)    // @return - pointer to data
{
   if (node->_left && node->_right) {                // L & R neighbours
      node->_left->_right = node->_right, node->_right->_left = node->_left ;
   } else if (node->_left) {                         // Left neighbour only
      node->_left->_right = NULL, dll->_end = node->_left ;
   } else if (node->_right) {                        // Right neoghbour only
      node->_right->_left = NULL, dll->_head = node->_right ;
   } else {                                          // one element only
      dll->_head = dll->_end = NULL ;
   }

   void*   dptr = node->_data ;
   free(node) ;
   return dptr ;
}

NodeDL_t* _new_node(void* data) {   // @return - new node for @data
   NodeDL_t*   wn = calloc(1, sizeof(NodeDL_t)) ;
   if (wn)  wn->_left = wn->_right = NULL, wn->_data = data ;

   return wn ;
}

// add a node to the front
int _add_dll_node_front(ListDL_t *l, NodeDL_t *node)
{
                                                      // printf(" FRONT ") ;
   // no validation checks
   if (!l->_head) { l->_head = l->_end = node ; return NO_ERROR ; }

   l->_head->_left = node, node->_right = l->_head ;  // connect the new
   l->_head = node ;
   return NO_ERROR ;
}

// add a node to the end
int _add_dll_node_end(ListDL_t *l, NodeDL_t *node)
{
                                                    // printf(" END ") ;
   // no validation checks
   if (!l->_end) { l->_head = l->_end = node ; return NO_ERROR ; }

   l->_end->_right = node, node->_left = l->_end ;  // connect the new
   l->_end = node ;
   return NO_ERROR ;
}


// eof dll.c
