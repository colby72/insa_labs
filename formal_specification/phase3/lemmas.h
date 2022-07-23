/*@ lemma le_ind:
  \forall integer i, n, s;
  0 < s && i < n ==> (i+1) * s <= n * s; */

/*@ lemma mul_r_le: 
  \forall integer a, b, c; 
    0 <= a ==> b <= c ==> b * a <= c * a; */

/*@ lemma mul_r_eq_lt: 
  \forall integer a, b, c, d, e1, e2; 
    0 < a <= b ==> c < d ==> e1 == a * c ==> e2 == b * d ==> e1 < e2; */

/*@ lemma div_mul:
  \forall integer a, b; b != 0 ==> (a * b) / b == a; */ 

/*@ lemma numof_def:
  \forall char * a, char value, integer start, end;
  0 <= start < end ==> numof(start, end, a, value) == (a[start]==value?1:0) + numof(start+1, end, a, value); */

/*@ lemma numof_split:
  @   \forall char * a, char value, integer start, middle, end;
  @   0 <= start && start <= middle <end ==>
  @   numof(start, middle, a, value) + numof(middle, end, a, value)
  @   == numof(start, end, a, value);
*/


/*@ lemma numof_split_left:
  \forall char * a, char value, integer start, middle, end;
  0 <= start && start <= middle <end ==>
  numof(start, middle, a, value) == 0 ==>
  numof(start, end, a, value) == numof(middle, end, a, value);
*/

/*@ lemma is_empty_numfree:
       \forall struct memb * m; 
       valid_memb(m) ==> (is_empty(m) <==> ( numfree(m) == m->num )); */

/*@ lemma numof_unchanged{L1,L2}:
    \forall char * a, char value, integer start, end;
    ( \forall integer k; start <= k < end ==> 
       \at(a[k], L1) == \at(a[k], L2) ) 
    ==>
    numof{L1}(start, end, a, value) == numof{L2}(start, end, a, value); 
*/

/*@ lemma in_aligned_index_of:
      \forall struct memb * m, char * ptr; 
      memb_in(m, ptr) && memb_aligned(m, ptr) ==>
      0 <= memb_indexof(m, ptr) < m->num; */

/*@ lemma aligned_shift:
      \forall struct memb * m, integer k;
      0 <= k < m->num ==> memb_aligned(m, ((char*)m->mem) + k * m->size); */

/*@ lemma aligned_in_characterization:
      \forall struct memb * m, char * ptr;
      memb_aligned(m, ptr) && memb_in(m, ptr) 
      ==> \exists integer k; 0 <= k < m->num 
       && ptr == ((char*)m->mem) + k * m->size; */

/*@ lemma indexof_shift:
      \forall struct memb * m, integer k;
      0 <= k < m->num 
      ==> memb_indexof(m, (char*)m->mem + k * m->size) == k; */
