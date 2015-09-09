
//##############################################################################
//
// Mark Wheatley
// CSC304
// ArrayFun
// arrayfun.cc
//
//##############################################################################

#include "arrayfun.h"

void ArrayFun::init( int* a, int n)
{
  int i;

  for( i=0; i<n; i++)
  {
    a[i] = i;
  }
}

void ArrayFun::disp( int* a, int n)
{
  int i;

  std::cout << "[ ";
  for( i=0; i<n; i++)
  {
    std::cout << a[i] << " ";
  }
  std::cout << "]\n";
}

void ArrayFun::disp0( int* a, int l, int r)
{
  int i;

  std::cout << "[ ";
  for( i=l; i<=r; i++)
  {
    std::cout << a[i] << " ";
  }
  std::cout << "] ";
}

void ArrayFun::shuffle( int* a, int n)
{
  int i, j;

  srand(time(NULL));
  for( i=n-1; i>0; i--)
  {
    j = rand() % (i+1);

    swap( &a[i], &a[j]);
  }
}

void ArrayFun::reverse( int* a, int n)
{
  int i, j;

  j = n;
  for( i=0; i<n; i++)
  {
    a[i] = --j;
  }
}

void ArrayFun::copy( int* cpy, int* src, int l, int r)
{
  int i = r+1;

  while( --i >= l)
  {
    cpy[i] = src[i];
  }
}

void ArrayFun::swap( int* x, int* y)
{
  int temp;

  temp = *x;
  *x = *y;
  *y = temp;
}

bool ArrayFun::is_sorted( int* a, int n)
{
  int i;
  for( i=1; i<n; i++)
  {
    if( a[i] <= a[i-1])
    {
      return false;
    }
  }
  return true;
}

