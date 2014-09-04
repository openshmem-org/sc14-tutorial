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



/*
 * PE 1 waits for PE 0 to send something other than 9.
 * Send 4 9s to test wait condition, then some random values until != 9.
 *
 * Include a want-this-to-fail call at the end
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpp/shmem.h>

int
main (void)
{
  int me, npes;
  long *dest;

  {
    time_t now;
    time (&now);
    srand (now + getpid ());
  }

  start_pes (0);
  me = shmem_my_pe ();
  npes = shmem_n_pes ();

  dest = (long *) shmalloc (sizeof (*dest));

  *dest = 9L;
  shmem_barrier_all ();

  if (me == 0)
    {
      int i;
      for (i = 0; i < 4; i += 1)
	{
	  long src = 9L;
	  shmem_long_put (dest, &src, 1, 1);
	  fprintf (stderr, "PE %d put %d\n", me, src);
	}
      fprintf (stderr, "----------------------------\n");
      for (i = 0; i < 1000; i += 1)
	{
	  long src = rand () % 10;
	  shmem_long_put (dest, &src, 1, 1);
	  fprintf (stderr, "PE %d put %d\n", me, src);
	  if (src != 9L)
	    break;
	}
    }

  shmem_barrier_all ();

  if (me == 1)
    {
      shmem_long_wait_until (dest, _SHMEM_CMP_NE, 9L);
      fprintf (stderr, "PE %d finished wait, got %d\n", me, *dest);
    }

  return 0;
}
