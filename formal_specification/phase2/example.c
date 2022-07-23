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
  int result;
  char * x;
  
  store.num = NUM;
  store.size = SIZE;
  store.used = used;
  store.mem = (void *)storage;
  memb_init(&store);
  //@ assert valid_memb(&store);
  //@ assert is_empty(&store);
  int nf = memb_numfree(&store);
  //@ assert nf == numfree(&store);
  // --Begin: A user shouldn't do that,
  //          but call memb_alloc(&store) instead
  store.used[0] = USED;
  //@ assert numfree(&store) == nf - 1;
  x = store.mem;
  // --End. 
  //@ assert \separated(x, store.used + (0..store.num-1));
  //@ assert memb_in(&store, x);
  *x = 'A';
  int in = memb_inmemb(&store, x);
  //@ assert in == \true;
  result = memb_free(&store, x);
  //@ assert result == 0;
  //@ assert store.used[memb_indexof(&store, x)] == FREE;
  //@ assert numfree(&store) == nf;
  result = memb_free(&store, x);
  //@ assert result == -1;
  //@ assert numfree(&store) == nf;
  result = memb_free(&store, NULL);
  //@ assert result == -1;
  //@ assert numfree(&store) == nf;
  //@ assert is_empty(&store);
}
