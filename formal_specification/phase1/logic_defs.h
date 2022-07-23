/* @predicate valid_memb_structure(memb* m) =
    (sizeof(m->used)/sizeof(char)) == m->num;
    && (sizeof(m->mem)/sizeof(void)) == (m->num)*(m->size);
*/

/* @predicate valid_memb(memb* m) =
    \forall integer k; 0 <= k < m->num
    ==> (m->used)[k] == FREE || (m->used)[k] == USED;
*/

/* @predicate is_empty(memb* m) =
    \forall integer k; 0 <= k < m->num
    ==> (m->used)[k] == FREE;
*/

/* @predicate memb_in(memb* m) =
    \forall integer k; 0 <= k < (m->size)*(m->num)
    ==> valid(((char*)m->mem)[k])
*/
