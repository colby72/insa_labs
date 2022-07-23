The command should be: 

frama-c -wp -rte -wp-prover script,alt-ergo -wp-timeout 10 -wp-script script -wp-prop="-@lemma" -rte-select memb_init,memb_free,memb_inmemb,memb_numfree memb.c

It is because, even with a large timeout, the system is unable to
prove the assertion i * sz < n * sz with a more direct guidance.  The
help is given to the system as a script provided in file 'script'.
