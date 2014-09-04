#include <stdio.h>
#include <sys/utsname.h>

#include <shmem.h>

int
main (void)
{
  int me, npes;
  struct utsname u;

  uname (&u);

  start_pes (0);

  me = shmem_my_pe ();
  npes = shmem_n_pes ();

  printf ("%s: Hello from node %4d of %4d\n", u.nodename, me, npes);

  return 0;
}
