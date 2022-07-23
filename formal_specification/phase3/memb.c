#define NULL 0
#include "memb.h"
#include "lemmas.h"

/*---------------------------------------------------------------------------*/
void
memb_init(struct memb *m)
{
  /*@ loop invariant 0 <= i;
      loop invariant i <= m->num;
      loop invariant \forall integer k; 0 <= k < i ==> m->used[k] == FREE;
      loop assigns i, m->used[0..m->num-1];
      loop variant m->num - i; */
  for(int i = 0; i < m->num; i++)
    m->used[i] = FREE;
  /*@ loop invariant 0 <= i;
      loop invariant i <= m->size * m->num;
      loop invariant \forall integer k; 0 <= k <i ==> ((char*)(m->mem))[k] == 0;
      loop assigns i, ((char*)m->mem)[0..m->size * m->num-1];
      loop variant m->size * m->num - i; */
  for(int i = 0; i < m->size * m->num; i++)
    ((char *)m->mem)[i] = 0;
}
/*---------------------------------------------------------------------------*/
void *
memb_alloc(struct memb *m)
{
  /*@ loop invariant 0 <= i;
      loop invariant i <= m->num;
      loop invariant \forall integer k; 0 <= k < i ==> m->used[i] != FREE;
      loop assigns i, addr;
      loop variant m->num - i;
   */
  while (i < m->num) {
    //@ assert \forall integer k; 0 <= k < m->num ==> m->used[k] \in {FREE,USED};
    const char tmp = m -> used[i];
    if(tmp == FREE) {
      //@ assert m->used[memb_indexof(m, (char*)ptr)] == FREE;
      /*@ assert numof(0, i, m->used, FREE) + numof(i, n, m->used, FREE) ==
           numof(0, n, m->used, FREE); */
      char * addr = (char*)m->mem + i * m->size;
    Before:
      m->used[i] = USED;
      //@ assert (m->size * i) < (m->size * n);
      return (void *)addr;
    }
    //@ assert m->used[memb_indexof(m, (char*)ptr)] == USED;
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
      loop invariant i <= n;
      loop invariant ptr2 == (char*)m->mem + i * m->size;
      loop invariant \forall integer k; 0 <= k < i ==>
                        ptr != (char*)m->mem + k * m->size;
      loop assigns i, ptr2;
      loop variant n - i;
   */
  while(i < n){
    if(ptr2 == p) break;
    ptr2 += sz;
    ++i;
  }
  if(i == m->num){
    // @ assert !memb_in(m, (char*)ptr) || !memb_aligned(m, (char*)ptr);
    return -1;
  } else {
    //@ assert (char*) ptr == (char*)m->mem + i * m->size;
    //@ assert i == memb_indexof(m, (char*) ptr);
    //@ assert (sz * i) < (sz * n);
    //@ assert memb_in(m, (char *)ptr);
    //@ assert memb_aligned(m, (char *)ptr);
    char used = m->used[i];
    if(used == FREE){
      //@ assert m->used[memb_indexof(m, (char*)ptr)] == FREE;
      return -1;
    } else {
      //@ assert m->used[memb_indexof(m, (char*)ptr)] == USED;
      /*@ assert numof(0, i, m->used, FREE) + numof(i, n, m->used, FREE) ==
	         numof(0, n, m->used, FREE); */
      /*@ assert numof(i, n, m->used, FREE) == (m->used[i]==FREE?1:0) +
	                                       numof(i+1, n, m->used, FREE); */
      /*@ assert numfree(m) == numof(0, i, m->used, FREE) + 0 +
                               numof(i+1, n, m->used, FREE); */
    Before:
      m->used[i] = FREE;
      /*@ assert \forall integer k; 0 <= k < i ==>
                                    \at(m->used[k], Before) == m->used[k]; */
      //@ assert numof(0, i, m->used, FREE) == numof{Before}(0, i, m->used, FREE);
      /*@ assert \forall integer k; i+1 <= k < n ==>
                                    \at(m->used[k], Before) == m->used[k]; */
      //@ assert numof(i+1, n, m->used, FREE) == numof{Before}(i+1, n, m->used, FREE);
      // @ assert numfree(m) == ( numof(0, i, m->used, FREE) + numof(i+1, n, m->used, FREE) ) + 1;
      //@ assert numfree(m) == ( numof{Before}(0, i, m->used, FREE) + numof{Before}(i+1, n, m->used, FREE) ) + 1;
      /*@ assert numof{Before}(0,   i, m->used, FREE) + numof{Before}(i+1, n, m->used, FREE) == numfree{Before}(m); */
      //@ assert numfree(m) == numfree{Before}(m) + 1;
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
  /*@ loop invariant 0 <= num_free <= i <= m->num;
      loop invariant numof(0, m->num, m->used, FREE)
                  == num_free + numof(i, m->num, m->used, FREE);
      loop assigns i, num_free;
      loop variant m->num - i; */
  for(i = 0; i < m->num; ++i) {
    if(m->used[i] == FREE) {
      // @ assert m->used[i] == FREE;
      ++num_free;
    }
  }
  return num_free;
}
