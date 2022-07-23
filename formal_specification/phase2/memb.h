/*
 * Copyright (c) 2004, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

/**
 * \addtogroup mem
 * @{
 */


/**
 * \defgroup memb memb: Memory block management functions
 *
 * The memory block allocation routines provide a simple yet powerful
 * set of functions for managing a set of memory blocks of fixed
 * size. A set of memory blocks is statically declared with the
 * MEMB() macro. Memory blocks are allocated from the declared
 * memory by the memb_alloc() function, and are deallocated with the
 * memb_free() function.
 *
 * @{
 */


/**
 * \file
 *         Memory block allocation routines.
 * \author
 *         Adam Dunkels <adam@sics.se>
 *
 */

#ifndef MEMB_H_
#define MEMB_H_

#include <limits.h>

#define FREE (char)0
#define USED (char)1

struct memb {
  unsigned short size;
  unsigned short num;
  char *used;
  void *mem;
};

#include "logic_defs.h"

/**
 * Initialize a memory block that was declared with MEMB().
 *
 * \param m A set of memory blocks previously declared with MEMB().
 */
/*@ requires valid_memb_structure(m);
    ensures valid_memb(m);
    ensures is_empty(m);
    ensures \forall integer k; 0 <= k < m->size * m->num ==>
                               ((char*)m->mem)[k] == 0;
    assigns m->used[0 .. m->num - 1];
    assigns ((char*) m->mem)[0 .. m->size * m->num - 1]; */
void  memb_init(struct memb *m);

/**
 * Allocate a memory block from a block of memory declared with MEMB().
 *
 * \param m A set of memory blocks previously declared with MEMB().
 */
void *memb_alloc(struct memb *m);

/**
 * Deallocate a memory block from a memory block previously declared
 * with MEMB().
 *
 * \param m m A set of memory blocks previously declared with MEMB().
 *
 * \param ptr A pointer to the memory block that is to be deallocated.
 *
 * \return error code, should be 0 if successfully deallocated or -1 if the
 * pointer "ptr" did not point to a legal memory block.
 */

 /*@requires valid_memb(m);
    ensures i = numof(0, m->num, , );
    ensures i == m->num || m->used[i] == FREE ==> \result == -1;
    ensures i != m->num || m->used[i] != FREE ==> \result == 0;
    assigns (char *)m->mem, m->used[i];
  */
int  memb_free(struct memb *m, void *ptr);

/**
 * Check if a given address is within a memory area previously
 * declared with MEMB().
 *
 * \param m m A set of memory blocks previously declared with MEMB().
 *
 * \param ptr A pointer to the address to check
 *
 * \return 1 if the address is part of the memory block; otherwise 0
 */
/*@ requires valid_memb(m);
    ensures \result <==> memb_in(m, (char*)ptr);
    assigns \nothing; */
int memb_inmemb(struct memb *m, void *ptr);

/**
 * Count free memory blocks
 *
 * \param m m A set of memory blocks previously declared with MEMB().
 *
 * \return the number of free (available) memory blocks
 */

 /*@ requires valid_memb(m);
    ensures num_free < m->num;
    ensures \forall integer k; 0 <= k < i ==>
            m->used[k] == FREE ==> num_free = old(num_free) + 1;
    behavior free:
      assumes m->used[k] == FREE;
      ensures num_free = old(num_free) + 1;
    behavior used:
      assumes m->used[k] == USED;
      ensures \nothing;
    complete behaviors;
    disjoint behaviors;
    assigns num_free;
 */
int  memb_numfree(struct memb *m);

/** @} */
/** @} */

#endif /* MEMB_H_ */
