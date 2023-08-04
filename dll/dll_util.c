// dll_util.c: implementation of DLL utilities (some)
//

#include "dll.h"


// do 'f' for each element
void dll_for_each(ListDL_t* l, NFunction_t f)
{
    if (l)   {
        for (NodeDL_t* curr = l->_head ; curr ; curr = curr->_right) {
            f(curr->_data) ;
        }
    }
}

// reverse the list
void dll_reverse(ListDL_t* dll)
{
    NodeDL_t*   cn = dll->_head ;
    for (NodeDL_t* wn = NULL ; cn ; cn = wn) {
        wn = cn->_right, cn->_right = cn->_left, cn->_left = wn ;
    }
    cn = dll->_end, dll->_end = dll->_head, dll->_head = cn ;
}


// eof dll_util.c
