#include "memb.h"
#include "stdlib.h"
#include "lemmas.h"

#define NUM 8
#define SIZE sizeof(char)
char used [NUM];
char storage [NUM*SIZE];

int main()
{
  struct memb store;
  store.num = NUM;
  store.size = SIZE;
  store.used = used;
  store.mem = (void *)storage;
  memb_init(&store);
  //@ assert valid_memb(&store);
  //@ assert is_empty(&store);
  /*@ assert \forall integer k; 
    @   0 <= k < store.num ==> store.used[k] == FREE; */
  int nf = memb_numfree(&store);
  //@ assert nf == numfree(&store);
  char * x = (char*) memb_alloc(&store);
  //@ assert numfree(&store) == nf - 1;
  //@ assert store.used[memb_indexof(&store, x)] == USED;
  /*@ assert \forall integer k; 
             0 <= k < store.num && k != memb_indexof(&store, x) 
	     ==> store.used[k] == FREE; */
  //@ assert \valid(x);
  //@ assert \separated(x, store.used + (0..store.num-1));
  //@ assert memb_in(&store, x);
  //@ assert memb_aligned(&store, x);
  *x = 'A';
  int in = memb_inmemb(&store, x);
  //@ assert in == \true;
  int result = memb_free(&store, x);
  //@ assert result == 0;
  //@ assert is_empty(&store);
}
