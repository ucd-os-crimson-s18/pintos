/* FIXED POINT REAL ARITHMETIC*/
/* Using APPENDIX B: 4.4 BSD SCHEDULER PAGE 95*/
/* CRIMSON TEAM */

#ifndef THREADS_FIXED_POINT_H
#define THREADS_FIXED_POINT_H


#define P 17
#define Q 14
#define F (1 << Q) 

typedef struct
{

  int value;

}fixed_point_t;


/* Return fixed point value */
static inline fixed_point_t
fixed_point (int n)
{
  fixed_point_t fx_pt;

  fx_pt.value = n;
  
  return fx_pt;
}

/* Convert n to fixed point: */
static inline fixed_point_t
convert_int (int n)
{
  return fixed_point (n * F);
}

/* Convert x to integer (rounding toward zero): */
static inline int
convert_fixed_pt (fixed_point_t x)
{
  return (x.value / F);
}

/* Convert x to integer (rounding to nearest integer); */
static inline int
convert_fixed_pt_nearest (fixed_point_t x)
{
  if(x.value >= 0)
  {
    return ((x.value + F / 2) / F);
  }

  if(x.value <= 0)
  {
    return ((x.value - F / 2) / F);
  }
}

/* Add x and y */
static inline fixed_point_t
add_fixed_pts (fixed_point_t x, fixed_point_t y)
{
  return fixed_point(x.value + y.value);
}

/* Subtract x and y */
static inline fixed_point_t
sub_fixed_pts (fixed_point_t x, fixed_point_t y)
{
  return fixed_point(x.value - y.value);
}

/* Add x and n */
static inline fixed_point_t
add_fixed_pt_int (fixed_point_t x, int n)
{
  return fixed_point(x.value + n * F);
}

/* Subtract n from x */
static inline fixed_point_t
sub_fixed_pt_int (fixed_point_t x, int n)
{
  return fixed_point(x.value - n * F);
}

/* Multiply x by y */
static inline fixed_point_t
mult_fixed_pts (fixed_point_t x, fixed_point_t y)
{
  return fixed_point((long long) x.value * y.value / F);
}

/* Multiply x by n */
static inline fixed_point_t
mult_fixed_pt_int (fixed_point_t x, int n)
{
  return fixed_point(x.value * n);
}

/* Divide x by y */
static inline fixed_point_t
div_fixed_pts (fixed_point_t x, fixed_point_t y)
{
  return fixed_point((long long) x.value * F / y.value);
}

/* Divide x by n */
static inline fixed_point_t
div_fixed_pt_int (fixed_point_t x, int n)
{
  return fixed_point(x.value / n);
}

#endif /* threads/fixed-point.h */
