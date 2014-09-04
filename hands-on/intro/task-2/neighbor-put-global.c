/*
 * rotate PE id to right neighbor (dest) in a global, with wrap-around
 */

#include <stdio.h>

#include <shmem.h>

int dest;			/* global => symmetric */

int
main (int argc, char **argv)
{
  int nextpe;
  int me, npes;
  int src;

  start_pes (0);
  me = shmem_my_pe ();
  npes = shmem_n_pes ();

  nextpe = (me + 1) % npes;

  src = nextpe;

  dest = -1;
  shmem_barrier_all ();

  shmem_int_put (& dest, & src, 1, nextpe);

  shmem_barrier_all ();

  printf ("%4d: got %4d: ", me, dest);
  if (dest == me)
    {
      printf ("CORRECT");
    }
  else
    {
      printf ("WRONG, expected %d", me);
    }
  printf ("\n");

  return 0;
}
