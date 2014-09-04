/*
 *
 * Copyright (c) 2011 - 2014
 *   University of Houston System and Oak Ridge National Laboratory.
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * o Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * 
 * o Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * 
 * o Neither the name of the University of Houston System, Oak Ridge
 *   National Laboratory nor the names of its contributors may be used to
 *   endorse or promote products derived from this software without specific
 *   prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */



#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <mpp/shmem.h>

static long pSync[_SHMEM_BCAST_SYNC_SIZE];

static int src[4] = { 11, 12, 13, 14 };

#define DST_SIZE 128

static int dst[DST_SIZE];

int npes;
int me;

static
void
show_dst (char *tag)
{
  int i;
  printf ("%8s: dst[%d/%d] = ", tag, me, npes);
  for (i = 0; i < DST_SIZE; i += 1)
    {
      printf ("%d ", dst[i]);
    }
  printf ("\n");
}

int
main (void)
{
  int i;

  start_pes (0);
  npes = shmem_n_pes ();
  me = shmem_my_pe ();

  for (i = 0; i < _SHMEM_BCAST_SYNC_SIZE; i += 1)
    {
      pSync[i] = _SHMEM_SYNC_VALUE;
    }

  for (i = 0; i < DST_SIZE; i++)
    {
      dst[i] = -1;
    }

  shmem_barrier_all ();

  shmem_fcollect32 (dst, src, 2, 0, 0, npes, pSync);

  show_dst ("AFTER");

  return 0;
}
