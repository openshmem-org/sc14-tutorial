/*
 * pull value from left-hand neighbor using get (wrap-around)
 */

#include <stdio.h>

#include <shmem.h>

int src;			/* global => symmetric */

int
main (int argc, char **argv)
{
  int leftpe;
  int me, npes;

  start_pes (0);
  me = shmem_my_pe ();
  npes = shmem_n_pes ();

  leftpe = me - 1;

  src = leftpe;

  shmem_barrier_all ();

  if (me > 0)
    {
      const int expected = me - 2;

      int dest = shmem_int_g (& src, leftpe);

      printf ("%4d: got %4d: ", me, dest);
      if (dest == expected)
	{
	  printf ("CORRECT");
	}
      else
	{
	  printf ("WRONG, expected %d", expected);
	}
      printf ("\n");
    }

  return 0;
}
