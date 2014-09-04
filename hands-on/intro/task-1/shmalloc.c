/*
 * Allocaitng a symmetric variable on the remotely accessible heap.
 * Addresses may not be the same everywhere, depending on the
 * underlying system and/or OpenSHMEM implementation.
 *
 */

#include <stdio.h>
#include <assert.h>

#include <shmem.h>

#define ARR_SIZE 1024

int
main (void)
{
  int me;
  float *fp;

  start_pes (0);
  me = shmem_my_pe ();

  fp = shmalloc (sizeof (*fp) * ARR_SIZE);
  assert (fp != NULL);

  printf ("PE %d: float array \"fp\" allocated at address %p\n", me, fp);

  shfree (fp);

  return 0;
}
