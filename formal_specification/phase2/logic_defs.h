/*@ predicate valid_memb_structure(struct memb *m) =
       \valid(m)
    && m->size > 0
    && \valid(m->used + (0 .. (m->num - 1)))
    && m->size * m->num <= INT_MAX
    && \valid((char*) m->mem + (0 .. (m->size * m->num - 1)))
    && \separated(m->used + (0 .. (m->num - 1)),
                 (char*) m->mem + (0 .. m->size * m->num - 1)); */

/*@ predicate valid_memb(struct memb *m) =
        valid_memb_structure(m)
     && \forall integer k; 0 <= k < m->num ==>
                           m->used[k] \in {FREE, USED};
*/

/*@ predicate is_empty{L}(struct memb * m) =
      \forall integer k; 0 <= k < m->num ==> m->used[k] == FREE; */

/*@ predicate memb_in(struct memb * m, char * ptr) =
      (char *)m->mem <= ptr < (char*) m->mem + (m->num * m->size); */

/*@ logic integer numof{L}(integer start, integer end,
                           char * array, char value) =
     (start >= end || start < 0) ? 0 :
       (array[start] == value ? 1 : 0) +
       numof(start + 1, end, array, value); */

/*@ predicate memb_aligned(struct memb * m, char * ptr) =
     (ptr - (char*)m->mem) % m->size == 0; */

/*@ logic integer memb_indexof(struct memb * m, void * ptr) =
     (m->mem - ptr) / m->size; */

/*@ logic integer numfree(struct memb* m) =
    numof(0, m->num-1, m->used, FREE);
*/
