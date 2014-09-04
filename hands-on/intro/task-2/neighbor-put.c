/*
 * rotate PE id to right neighbor (dest), with wrap-around
 */

#include <stdio.h>
#include <assert.h>

#include <shmem.h>

int
main (int argc, char **argv)
{
  int nextpe;
  int me, npes;
  int src;
  int *dest;

  start_pes (0);
  me = shmem_my_pe ();
  npes = shmem_n_pes ();

  nextpe = (me + 1) % npes;

  src = nextpe;

  dest = (int *) shmalloc (sizeof (*dest)); /* symmetric */
  assert (dest != NULL);

  *dest = -1;
  shmem_barrier_all ();

  shmem_int_put (dest, & src, 1, nextpe);

  shmem_barrier_all ();

  printf ("%4d: got %4d: ", me, *dest);
  if (*dest == me)
    {
      printf ("CORRECT");
    }
  else
    {
      printf ("WRONG, expected %d", me);
    }
  printf ("\n");

  shmem_barrier_all ();

  shfree (dest);

  return 0;
}
