/* FIXED POINT REAL ARITHMETIC*/
/* Using APPENDIX B: 4.4 BSD SCHEDULER PAGE 95*/

#ifndef THREADS_FIXED_POINT_H
#define THREADS_FIXED_POINT_H

#define P = 17;
#define Q = 14;
#define F = 1 << Q;

/* Convert n to fixed point: */
int
convert_int(int n)
{
  return (n * F);
}

/* Convert x to integer (rounding toward zero): */
int
convert_fixed_pt(int x)
{
  return (x / F);
}

/* Convert x to intger (rounding to nearest); */
int
convert_fixed_pt_nearest(int x)
{
  if(x >= 0)
  {
    return ((x + F / 2) / F);
  }

  if(x <= 0)
  {
    return ((x - F / 2) / F);
  }
}

/* Add x and y */
int
add_fixed_pts(int x, int y)
{
  return (x + y);
}

/* Subtract x and y */
int
sub_fixed_pts(int x, int y)
{
  return (x - y);
}

/* Add x and n */
int
add_fixed_pt_int(int x, int n)
{
  return (x + n * F);
}

/* Subtract n from x */
int
sub_fixed_pt_int(int x, int n)
{
  return (x - n * F);
}

/* Multiply x by y */
int
mult_fixed_pts(int x, int y)
{
  return (((int64_t)x) * y / F);
}

/* Multiply x by n */
int
mult_fixed_pt_int(int x, int y)
{
  return (x * n);
}

/* Divide x by y */
int
div_fixed_pts(int x, int y)
{
  return (((int64_t)x) * F / y);
}

/* Divide x by n */
int
div_fixed_pt_int(int x, int y)
{
  return (x / n);
}

#endif /* threads/fixed-point.h */
