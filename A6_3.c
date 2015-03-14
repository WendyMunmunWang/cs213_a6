
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

void print_number (void* ev) {
  intptr_t e = (intptr_t) ev;
  printf ("%ld\n", e);
}
void print_s (void* ev) {
  char* e = (char*) ev;
  if (ev==NULL) printf("NULL\n");
  else printf ("%s\n", e);
}

/** STEP 2
 *  each string to determine if it is a number, if so, then return the number, otherwise 
 *  return -1
 */
void check_int(void** rv,void* value){ 
    char* v = (char*)value; //value is a string 
	intptr_t* r=(intptr_t*) rv; //the buf will be stored with int type
	char* buf;
	strtol(v,&buf,0);
	if (*buf==0) *r=strtol(v,&buf,0);
	else *r=-1;
}
// STEP 3
// check if the element is a letter;
void check_letter (void** rv,void* letter_value,void* number_value){
	char* letter = (char*) letter_value;
	intptr_t number = (intptr_t) number_value;
	char** r=(char**) rv;
	if (number==-1) *r=letter;
	else *r = (char*)NULL;
}
// STEP 4
//Filter the number list to produce a new list with all negative values removed. The list
//may thus be shorter than the original list. 

int neg_false(void* value){
	intptr_t v = (intptr_t) value;
	if (v<0) return 0;
	else return 1;
}

/** STEP 5
 *  return 1 if it is not null
 *  if it is null, return 0
 */ 
int null_false(void* value){
	char* v = (char*) value;
	return (v!=NULL);
}
/** STEP 6
 *  modify the letter with the given number 
 */

void change_element(void**rv, void* letter, void* number){ 
	char** r = (char**) rv;
	char* l = (char*) letter;
	intptr_t n = (intptr_t) number;
	char* buf = malloc (sizeof(char)*(n+1));
	*r = buf;
	strncpy(*r,l,n);
	
		
}
// /** STEP 7
 // *  find the max in the number list 
 // */
void find_max(void** rv, void* stored_value, void* element){
	intptr_t* r = (intptr_t*) rv;
	intptr_t s = (intptr_t) stored_value;
	intptr_t e = (intptr_t) element;
	if (s>e) *r = s;
	else *r = e;
}

/**
 *  
 */
int main(int argc, char** argv){
	
/** STEP 1
 * created a new list and put all the arguments into the new list.
 */
	list_t new_list1 = list_create();
	for (int i=1;i<argc;i++){
	   list_append(new_list1, argv[i]);   
	}
	
	
/** STEP 2
 *  map the number list to produce a new list with all negative values with -1. 
 */
	list_t new_list2 = (list_t)list_create(); 
	list_map1(check_int,new_list2,new_list1);    //2nd argument is void**
	
	
/** STEP 3
 * map the number list to produce a new list with all positive values with NULL. 
 * a b NULL NULL NULL
 */ 
	list_t new_list3 = (list_t)list_create();
	list_map2(check_letter,new_list3,new_list1,new_list2);
	
	
	
	
/** STEP 4
 * Filter the number list to produce a new list with all negative values removed.
 * 1 2 3
 */
   
	list_t new_list4 = list_create();
    list_filter(neg_false,new_list4,new_list2);
	
	
/** STEP 5
 * Filter the string list to produce a new list with all NULLs removed.
 * a b
 */

    list_t new_list5 = list_create();
	list_filter(null_false,new_list5,new_list3);
	
 //STEP6
    list_t new_list6 = list_create();
    list_map2(change_element,new_list6,new_list5,new_list4);
	printf("step6:\n");
	list_foreach(print_s,new_list6);
//STEP7
    
//STEP8
    intptr_t max = -1;
	list_foldl(find_max,(void**) &max, new_list4);
	printf("step8:\n");
	printf("%ld\n",max);
  
}