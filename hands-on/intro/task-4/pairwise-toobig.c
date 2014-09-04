/*
 * Demo of pair-wise communication that artificially forces all PEs
 * into a global barrier
 *
 * NB shmalloc()s are unchecked for demo purposes
 */

#include <stdio.h>

#include <shmem.h>

#include "array-utils.h"

/*
 * sample grid size
 */
#define X 5
#define Y 10

int
main (void)
{
  int i;
  int me, npes;
  long *pSync;
  double *A;

  /*
   * Kick the OpenSHMEM program off.  Discover program layout, and
   * prep. the sync work array for barrier
   */
  start_pes (0);
  me = shmem_my_pe ();
  npes = shmem_n_pes ();

  pSync = shmalloc (sizeof (*pSync) * _SHMEM_BARRIER_SYNC_SIZE);
  for (i = 0; i < _SHMEM_BARRIER_SYNC_SIZE; i += 1)
    {
      pSync[i] = _SHMEM_SYNC_VALUE;
    }
  shmem_barrier_all ();

  /*
   * Allocate array everywhere and initialize
   */
  A = shmalloc (sizeof (*A) * X * Y);
  init_array (A, X, Y, 0.0);

  /*
   * Use PEs 0 and 1 as sender and receiver
   */
  if (me == 0)
    {
      double *target = & A[OFFSET (0, 0, Y)];
      shmem_double_p (target, 3.142, 1);
    }

  /*
   * Everyone into the barrier!
   */
  shmem_barrier_all ();

  /*
   * Receiver shows us updated array
   */
  if (me == 1)
    {
      dump_array (stdout, A, X, Y);
    }

  return 0;
}
