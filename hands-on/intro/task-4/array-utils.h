#include <stdio.h>

#define OFFSET(i, j, n) ( (i) + ( (j) * (n) ) )

/*
 * Set the entire array to "val"
 */

static
inline
void
init_array (double *a, int const xmax, int const ymax, double const val)
{
  int xx, yy;

  for (yy = 0; yy < ymax; yy += 1)
    {
      for (xx = 0; xx < xmax; xx += 1)
	{
	  a[OFFSET (xx, yy, ymax)] = val;
	}
    }
}

/*
 * Print out the contents of the local array to stdio stream
 */

static
inline
void
dump_array (FILE *fp, double *a, int const xmax, int const ymax)
{
  int xx, yy;

  fprintf (fp, "       ");
  for (xx = 0; xx < xmax; xx += 1)
    {
      fprintf (fp, "%-4d ", xx);
    }
  fprintf (fp, "\n");
  for (yy = 0; yy < ymax; yy += 1)
    {
      fprintf (fp, "%4d : ", yy);
      for (xx = 0; xx < xmax; xx += 1)
	{
	  fprintf (fp, "%.2f ", a[OFFSET (xx, yy, ymax)]);
	}
      fprintf (fp, "\n");
    }
}
