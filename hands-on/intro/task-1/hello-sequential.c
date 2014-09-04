#include <stdio.h>
#include <sys/utsname.h>

int
main (void)
{
  struct utsname u;

  uname (&u);

  printf ("%s: Hello\n", u.nodename);

  return 0;
}
