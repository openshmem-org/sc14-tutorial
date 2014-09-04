/*
 * Using a global variable for its symmetric properties.  Note all
 * global variables are allocated at same address everywhere (SPMD =
 * same executable = same bss/data segment)
 *
 */

#include <stdio.h>

#include <shmem.h>

#define ARR_SIZE 1024

int arr[ARR_SIZE];		/* global is symmetric */

int
main (void)
{
  int me;

  start_pes (0);
  me = shmem_my_pe ();

  printf ("PE %d: array \"arr\" allocated at address %p\n", me, arr);

  return 0;
}
