#include <stdlib.h>
#include "list.h"

const int INITIAL_SIZE  = 10;
const int GROWTH_FACTOR = 5;

/**
 * Structure describing a list.
 */
struct list {
  void** data;
  int    len;
  int    size;
};

/**
 * Create a new empty list.
 */
list_t list_create () {
  list_t l = malloc (sizeof (*l));
  l->data  = malloc (sizeof (void*) * INITIAL_SIZE);
  l->len   = 0;
  l->size  = INITIAL_SIZE;
  return l;
}

/**
 * Destroy list.
 */
void list_destroy (list_t l) {
  free (l->data);
  free (l);
}

/**
 * Expand the capacity of the list.  
 * New size is old size times GROWTH_FACTOR.
 * Internal helper function.
 */
static void expand_list (list_t l) {
  // TODO
  int old_size = l->size;
  l->size = old_size*GROWTH_FACTOR; //increase the size of the array
  void** expand_data = malloc(sizeof(void*) * l->size);
  for (int i=0;i<l->size;i++){
	  expand_data[i]=l->data[i];
  }
  free(l->data);
  l->data=expand_data;
  
}


/**
 * Append e to end of list.
 */
void list_append (list_t l, void* e) {
  // TODO
  if (l->len==l->size){
      expand_list(l);
  }
	  l->data[l->len]=e;
      l->len++;
}

/**
 * Append a[0] .. a[n-1] to end of list.
 */
void list_append_array (list_t l, void** a, int n) {
  for (int i = 0; i < n; i++)
    list_append (l, a [i]);
}

/**
 * Insert e at position pos (0..len-1).
 * Moves elements down to make room for the new element.
 */
void list_insert (list_t l, int pos, void* e) {
  // TODO
  if (1+(l->len)==l->size) expand_list(l); //plus one because we need to shift data to the right first 
  if (0 <= pos && pos <= l->len-1){           //if pos is between 0 to length-1
	  for (int i=pos;i<l->len;i++){
	  l->data[i+1]=l->data[i]; //shift the data to the right first 
	}
      l->data[pos]=e;
      l->len++;
  }
}

/**
 * Remove element at position pos (0..len-1).
 * Move elements up to occupy position of removed element.
 */
void list_remove (list_t l, int pos) {
  // TODO
  for (int i=pos;i<l->len;i++){
	l->data[i]=l->data[i+1];
  }
  free(l->data[l->len-1]); //delete the last element of the array
  l->len=(l->len)-1;
}

/**
 * Return element at position pos (0..len-1).
 */
void* list_get (list_t l, int pos) {
  return l->data [pos];
}

/**
 * Return the position (0..len-1) of e where equality
 * is established by equality function, which returns 1 
 * iff two objects are equal.
 */
int list_index (list_t l, void* e, int (*equal) (void*, void*)) {
  for (int i = 0; i < l->len; i++)
    if (equal (l->data [i], e))
      return i;
  return -1;
}

/**
 * Return the length of the list.
 */
int list_len (list_t l) {
  return l->len;
}

/**
 * Map function f onto list l placing results in r.
 * The lists r and l must not be the same list.
 */
void list_map1 (void (*f) (void**, void*), list_t r, list_t l) {
  // TODO
   
  for (int i=0;i<l->len;i++){
	 void* pointer;
	 f(&pointer,l->data[i]);//each element will store the modified value in the pointer
	 list_append(r,pointer);//the pointer will append the value to r
  }
}

/**
 * Map function f onto lists l0 and l1 placing results in r.
 * The target list r must not be one of l0 or l1.
 */
void list_map2 (void (*f) (void**, void*, void*), list_t r, list_t l0, list_t l1) {
  // TODO
  int length=0;
  if (l0->len<=l1->len) length=l0->len;
  else length=l1->len;  
	for (int i=0;i<length;i++){
		void* pointer_map2 = 0;
		f(&pointer_map2,l0->data[i],l1->data[i]);
		list_append(r,pointer_map2);
  }
}


/**
 * Fold list l using function f placing result in r.
 */
void list_foldl (void (*f) (void**, void*, void*), void** r,  list_t l) {
  // TODO
  //foldl(number, new_list, original_list);
 
  for(int i=0;i<l->len;i++){
	  
	  f(r,*r,l->data[i]);// r is the addr of acc, void* is an unknown type
	                     
	                     //*r is value of acc
	  
  }
}

/**
 * Filter list l using function f placing result in r.
 * List r contains elements of l for which f returns true (i.e., non-zero).
 * List r and l must not be the same list.
 */
void list_filter (int (*f) (void*), list_t r, list_t l) {
  // TODO
  for (int i=0;i<l->len;i++){
	  if (f(l->data[i])==1) list_append(r,l->data[i]); //if the function return true
	  
  }
}

/**
 * Execute function f for each element of list l.
 */
void list_foreach (void (*f) (void*), list_t l) {
  // TODO
   for (int i=0;i<l->len;i++){
	      f(l->data[i]);
	  }
}
