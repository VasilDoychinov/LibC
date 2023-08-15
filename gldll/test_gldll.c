// test_dll.c: to test the implementation of DLL library
// source code of the library to be found in LinuxC/libraries/dll/


#include <stdio.h>

#include "../libraries/glued_ds/gldll.h"



typedef NodeGLDL_t glthread_node_t ;

typedef struct emp_ {
    char name[32];
    unsigned int salary;
    char designation[32];
    unsigned int emp_id;
    glthread_node_t glnode;
} emp_t ;

void print_emp_details(glthread_node_t *glnode) ;
void print_employee_info(void *emp) ;

void print_gldll(ListGLDL_t* l) ;

int main()
{   
   /*Creating one employee object*/
   emp_t *emp  = calloc(1, sizeof(emp_t));
   strncpy(emp->name, "1111", strlen("1111"));
   emp->salary = 50000;
   strncpy(emp->designation, "HR", strlen("HR"));
   emp->emp_id = 11;
   /*Invoking fn to print employee details*/
   print_emp_details (&emp->glnode);

   unsigned int   offs = (unsigned int)offsetof(emp_t, glnode) ;
   ListGLDL_t* gl = get_new_gldll(offs) ;
   printf("\n\n> expecting emtpy: "), print_gldll(gl) ;

   gldll_add(gl, &(emp->glnode)) ;
   printf("\n\n> expecting 1 element: "), print_gldll(gl) ;

   emp_t *emp2  = calloc(1, sizeof(emp_t));
   strncpy(emp2->name, "2222", strlen("2222"));
   emp2->salary = 50000;
   strncpy(emp2->designation, "HR", strlen("HR"));
   emp2->emp_id = 22;

   gldll_append(gl, &(emp2->glnode)) ;

   emp_t *emp3  = calloc(1, sizeof(emp_t));
   strncpy(emp3->name, "3333", strlen("3333"));
   emp3->salary = 50000;
   strncpy(emp3->designation, "HR", strlen("HR"));
   emp3->emp_id = 33;

   gldll_append(gl, &(emp3->glnode)) ;

   printf("\n\n> expecting 3 elements: "), print_gldll(gl) ;

   gldll_remove(gl, &(emp2->glnode)) ;
   printf("\n\n> expecting 1&3 elements: "), print_gldll(gl) ;
   gldll_remove(gl, &(emp->glnode)) ;
   printf("\n\n> expecting 3: "), print_gldll(gl) ;
   gldll_remove(gl, &(emp3->glnode)) ;
   printf("\n\n> expecting empty: "), print_gldll(gl) ;

   gldll_append(gl, &(emp2->glnode)) ;
   gldll_add(gl, &(emp->glnode)) ;
   printf("\n\n> expecting 1&2 elements: "), print_gldll(gl) ;

   printf("\n\n> That's it...\n") ;
   return 0 ;
}


void print_gldll(ListGLDL_t* l)
{
   gldll_for_each(l, print_employee_info) ;
}

GLNODE_TO_BASE(emp_base_ptr, emp_t, glnode)      // preprocessor

/*Implement the below function*/
void print_emp_details(glthread_node_t *node) {
   // unsigned long offs = offsetof(emp_t, glnode) ;

   // printf("\n: offset of glnode: %lu", offs) ;
   print_employee_info(emp_base_ptr(node)) ;
}

/*Function to print employee details*/
void
print_employee_info(void* p)
{
   emp_t* emp = (emp_t*)p ;
   printf("\nEmployee name = %s\n", emp->name);
   printf("salary = %u\n", emp->salary);
   printf("designation = %s\n", emp->designation);
   printf("emp_id = %u\n", emp->emp_id);
   printf("---------------------------------") ;
}
