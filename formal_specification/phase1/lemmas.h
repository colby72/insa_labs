/*@ lemma le_ind:
  \forall integer i, n, s;
  0 < s && i * s < n * s ==> (i+1) * s <= n * s; */

/*@ lemma mul_r_le: 
  \forall integer a, b, c; 
    0 <= a ==> b <= c ==> b * a <= c * a; */

/* @ lemma mul_r_lt: 
  \forall integer a, b, c, e1, e2; 
    0 < a ==> b < c ==> e1 == b * a ==> e2 == c * a ==> e1 < e2 ; */

/*@ lemma div_mul:
  \forall integer a, b; b != 0 ==> (a * b) / b == a; */
