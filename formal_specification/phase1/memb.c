#define NULL 0
#include "memb.h"
#include "lemmas.h"

/*---------------------------------------------------------------------------*/
void
memb_init(struct memb *m)
{
  /* @loop invariant 0 <= i < m->num;
      loop invariant \forall integer k; 0 <= k < m->num ==> m->used[k]==FREE;
      loop assigns i, m->used[0..m->num-1]
      loop variant m->num-i;
  */
  for(int i = 0; i < m->num; i++)
    m->used[i] = FREE;
    /* @loop invariant 0 <= i < m->size*m->num;
        loop invariant \forall integer k; 0 <= k < m->size*m->num ==> m->mem[k]==0;
        loop assigns i, m->mem[0..(m->size*m->num)-1]
        loop variant (m->size*m->num)-i;
    */
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
  while(i < n){
    if(ptr2 == p) break;
    ptr2 += sz;
    ++i;
  }
  if(i == m->num){
    return -1;
  } else {
    char used = m->used[i];
    if(used == FREE){
      return -1;
    } else {
    Before:
      m->used[i] = FREE;
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
  for(i = 0; i < m->num; ++i) {
    if(m->used[i] == FREE) {
      ++num_free;
    }
  }
  return num_free;
}
