#include "memb.h"
#include "stdlib.h"

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
  //@ assert valid_memb_structure(&store);
  memb_init(&store);
  //@ assert valid_memb(&store);
  //@ assert is_empty(&store);
  //@ assert memb_in(&store, (char*)store.mem);

  // EXAMPLE USING OTHER FUNCTIONS OF THE API
  /*
  int nf = memb_numfree(&store);
  if (0 < nf){
    char * x = (char*) memb_alloc(&store);
    *x = 'A';
    int in = memb_inmemb(&store, x);
    int result = memb_free(&store, x);
  }
  */
}
