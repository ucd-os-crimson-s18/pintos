// FIXED POINT REAL ARITHMETIC
// Using APPENDIX B: 4.4 BSD SCHEDULER PAGE 95

#ifndef THREADS_FIXED_POINT_H
#define THREADS_FIXED_POINT_H

#define p = 17;
#define q = 14;
#define f = 1 << q;

// Convert n to fixed point:
int convert_int(int n)
{
  return (n * f);
}

// Convert x to integer (rounding toward zero):
int convert_fixed_pt(int x)
{
  return (x / f);
}

// Convert x to intger (rounding to nearest);
int convert_fixed_pt_nearest(int x)
{
  if(x >= 0)
  {
    return ((x + f / 2) / f);
  }

  if(x <= 0)
  {
    return ((x - f / 2) / f);
  }
}

// Add x and y
int add_fixed_pts(int x, int y)
{
  return (x + y);
}

// Subtract x and y
int sub_fixed_pts(int x, int y)
{
  return (x - y);
}

// Add x and n
int add_fixed_pt_int(int x, int n)
{
  return (x + n * f);
}

// Subtract n from x
int sub_fixed_pt_int(int x, int n)
{
  return (x - n * f);
}

// Multiply x by y
int mult_fixed_pts(int x, int y)
{
  return (((int64_t)x) * y / f);
}

// Multiply x by n
int mult_fixed_pt_int(int x, int y)
{
  return (x * n);
}

// Divide x by y
int div_fixed_pts(int x, int y)
{
  return (((int64_t)x) * f / y);
}

// Divide x by n
int div_fixed_pt_int(int x, int y)
{
  return (x / n);
}

#endif /* threads/fixed-point.h */
