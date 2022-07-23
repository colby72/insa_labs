#define NULL 0
#include "memb.h"
#include "lemmas.h"

/*---------------------------------------------------------------------------*/
void
memb_init(struct memb *m)
{
  /*@ loop invariant 0 <= i;
      loop invariant i <= m->num;
      loop invariant \forall integer k; 0 <= k < i ==>
                     m->used[k] == FREE;
      loop assigns i, m->used[0..m->num-1];
      loop variant m->num - i; */
  for(int i = 0; i < m->num; i++)
    m->used[i] = FREE;
  /*@ loop invariant 0 <= i;
      loop invariant i <= m->size * m->num;
      loop invariant \forall integer k; 0 <= k <i ==>
                     ((char*)(m->mem))[k] == 0;
      loop assigns i, ((char*)m->mem)[0..m->size * m->num-1];
      loop variant m->size * m->num - i; */
  for(int i = 0; i < m->size * m->num; i++)
    ((char *)m->mem)[i] = 0;
}
/*---------------------------------------------------------------------------*/
void *
memb_alloc(struct memb *m)
{
  int i = 0;
  while (i < m->num) {
    const char tmp = m -> used[i];
    if(tmp == FREE) {
      char * addr = (char*)m->mem + i * m->size;
    Before:
      m->used[i] = USED;
      return (void *)addr;
    }
    ++i;
  }
  /* No free block was found, so we return NULL to indicate failure to
     allocate block. */
  return NULL;
}
/*---------------------------------------------------------------------------*/
int
memb_free(struct memb *m, void *ptr)
{
  int i = 0 ;
  char *ptr2 = (char *)m->mem;
  const int n = m->num;
  const int sz = m->size;
  const char * p = (char*) ptr;
  /*@ loop invariant 0 <= i;
      loop invariant i < m->num;
      loop invariant \forall integer k; 0 <= k <i ==>
                     ((char*)(m->mem))[k] == 0;
      loop assigns i, ((char*)m->mem)[0..m->num-1], (char *)m->mem;
      loop variant m->num - i;
  */
  while(i < n){
    if(ptr2 == p) break;
    ptr2 += sz;
    ++i;
  }
  if(i == m->num){
    return -1;
  } else {
    //@ assert (char*) ptr == (char*)m->mem + i * m->size;
    //@ assert i == memb_indexof(m, (char*) ptr);
    //@ assert memb_in(m, (char *)ptr);
    //@ assert memb_aligned(m, (char *)ptr);
    char used = m->used[i];
    if(used == FREE){
      //@ assert m->used[memb_indexof(m, (char*)ptr)] == FREE;
      return -1;
    } else {
      //@ assert m->used[memb_indexof(m, (char*)ptr)] == USED;
      /*@ assert numof(0, n, m->used, FREE) ==
  	         numof(0, i, m->used, FREE) + numof(i, n, m->used, FREE); */
      /*@ assert numof(i, n, m->used, FREE) == (m->used[i]==FREE?1:0) +
	                                       numof(i+1, n, m->used, FREE); */
    Before:
      m->used[i] = FREE;
      /*@ assert \forall integer k; 0 <= k < i ==>
                                    \at(m->used[k], Before) == m->used[k]; */
      //@ assert numof{Before}(0, i, m->used, FREE) == numof(0, i, m->used, FREE);
      /*@ assert \forall integer k; i+1 <= k < n ==>
                                    \at(m->used[k], Before) == m->used[k]; */
      //@ assert numof{Before}(i+1, n, m->used, FREE) == numof(i+1, n, m->used, FREE);
      //@ assert m->used[memb_indexof(m, (char*)ptr)] == FREE;
      return 0;
    }
  }
}
/*---------------------------------------------------------------------------*/
int
memb_inmemb(struct memb *m, void *ptr)
{
  return (char *)ptr >= (char *)m->mem &&
    (char *)ptr < (char *)m->mem + (m->num * m->size);
}
/*---------------------------------------------------------------------------*/
int
memb_numfree(struct memb *m)
{
  int i;
  int num_free = 0;
  /*@ loop invariant 0 <= i;
      loop invariant i <= m->num;
      loop invariant \forall integer k; 0 <= k < i ==>
                     m->used[k] == FREE ==> num_free = old(num_free) + 1;
      loop assigns i, m->used[0..m->num-1];
      loop variant m->num - i;
  */
  for(i = 0; i < m->num; ++i) {
    if(m->used[i] == FREE) {
      ++num_free;
    }
  }
  return num_free;
}
