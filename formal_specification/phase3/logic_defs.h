/*@ predicate valid_memb_structure(struct memb *m) =
       \valid(m)
    && m->size > 0
    && \valid(m->used + (0 .. (m->num - 1)))
    && \valid((char*) m->mem + (0 .. (m->size * m->num - 1)))
    && m->size * m->num <= INT_MAX
    && \separated(m->used + (0 .. (m->num - 1)), 
                 (char*) m->mem + (0 .. m->size * m->num - 1)); */

/*@ predicate valid_memb(struct memb *m) =
          valid_memb_structure(m)
       && \forall integer k; 0 <= k < m->num ==> m->used[k] \in {FREE, USED}; */

/*@ predicate is_empty{L}(struct memb * m) =
      \forall integer k; 0 <= k < m->num ==> m->used[k] == FREE; */

/*@ logic integer numof{L}(integer start, integer end, char * array, char value) =
     (start >= end || start < 0) ? 0 :
       (array[start] == value ? 1 : 0) + 
       numof(start + 1, end, array, value); */

/*@ logic integer numfree(struct memb * m) =
   numof(0, m->num, m->used, FREE); */

/*@ predicate memb_in( struct memb *m, void *ptr ) =
    (char *) m->mem <= (char *) ptr < (char *) ( m->mem + sizeof(char) * m->num * m->size );
*/

/*@ predicate memb_in(struct memb * m, char * ptr) =
      (char *)m->mem <= ptr < (char*) m->mem + (m->num * m->size); */

/*@ predicate memb_aligned(struct memb * m, char * ptr) = 
  \exists integer k; 0 <= k < m->num && ptr == (char*)m->mem + k * m->size; */

/*@ logic integer memb_indexof(struct memb * m, void * ptr) = 
     (ptr - m->mem) / m->size; */

