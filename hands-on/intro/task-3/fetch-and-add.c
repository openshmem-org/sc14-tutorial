/*
 * Demo of remote atomic addition between 2 PEs
 *
 * Expected output (lines can appear in any order):
 *
 * 1: old = 22, dst = 22
 * 0: old = -1, dst = 66
 *
 */

#include <stdio.h>

#include <shmem.h>

/*
 * symmetric target
 */
int dst;

int
main (void)
{
  int me;
  int old;

  start_pes (0);
  me = shmem_my_pe ();

  old = -1;
  dst = 22;
  shmem_barrier_all ();

  if (me == 1)
    {
      old = shmem_int_fadd (&dst, 44, 0);
    }
  shmem_barrier_all ();

  printf ("%d: old = %d, dst = %d\n", me, old, dst);

  return 0;
}
