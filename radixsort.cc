
//##############################################################################
//
// Mark Wheatley
// CSC304
// ArrayFun
// radixsort.cc
//
//##############################################################################

#include "arrayfun.h"


double Radix::sort_basic( int* a, int* b, int l, int r)
{
  clock_t t = clock();

  int nbits = 32, bpp = 8;
  int m = pow( 2, bpp), count[m];
  int i, j, pass, n = r+1;

  for( pass=0; pass<nbits/bpp; pass++)
  //for( pass=3; pass>2; pass--)
  {
    for( j=0; j<m; j++)
    {
      count[j] = 0;
    }
    for( i=0; i<n; i++)
    {
      count[bits( a[i], pass*bpp, bpp)]++;
    }
    for( j=1; j<m; j++)
    {
      count[j] += count[j-1];
    }
    for( i=n-1; i>=0; i--)
    {
      b[--count[bits( a[i], pass*bpp, bpp)]] = a[i];
    }
    copy( a, b, 0, n-1);
  }
  return (double)(clock()-t)/double(CLOCKS_PER_SEC);
}

double RadixEx::sort_basic( int* a, int l, int r, int bit)
{
  clock_t t = clock();

  if( (r>l) && (bit>=0))
  {
    int i, j, temp;

    i = l;
    j = r;

    while( i != j)
    {
      while( !Radix::bits( a[i], bit, 1) && i<j)
      {
        i++;
      }
      while( Radix::bits( a[j], bit, 1) && j>i)
      {
        j--;
      }
      if( i != j)
      {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
      }
    }
    if( !((a[r]>>bit)&(1)))
    {
      j++;
    }
    RadixEx::sort_basic( a, l, j-1, bit-1);
    RadixEx::sort_basic( a, j, r, bit-1);
  }
  return (double)(clock()-t)/double(CLOCKS_PER_SEC);
}

unsigned Radix::bits( int x, int k, unsigned j)
{
  return (x >> k) & ~(~0 << j);
}

void Radix::runTime_basic( int fromPower2, int num_trials)
{
  std::ofstream outFile;
  outFile.open( "data/RadixSort/radix.txt");
  outFile << std::setprecision(3) << std::fixed;

  double t;
  int toPower2, size;
  int* a;
  int* b;

  toPower2 = fromPower2 + num_trials;

  std::cout << "\nStraight Radix Sort\n" << std::endl;
  std::cout << std::setw(12) << "n";
  std::cout << std::setw(12) << "sorted";
  std::cout << std::setw(12) << "reversed";
  std::cout << std::setw(12) << "shuffled" << std::endl;

  outFile << std::setw(12) << "n";
  outFile << std::setw(12) << "sorted";
  outFile << std::setw(12) << "reversed";
  outFile << std::setw(12) << "shuffled" << std::endl;

  while( fromPower2 < toPower2)
  {
    size = pow( 2, fromPower2++);
    std::cout << std::setw(12) << size;
    outFile << std::setw(12) << size;

    a = new int[size];
    b = new int[size];
    init( a, size);

    t = sort_basic( a, b, 0, size-1);
    std::cout << std::setw(12) << t;
    outFile << std::setw(12) << t;

    reverse( a, size);

    t = sort_basic( a, b, 0, size-1);
    std::cout << std::setw(12) << t;
    outFile << std::setw(12) << t;

    shuffle( a, size);

    t = sort_basic( a, b, 0, size-1);
    std::cout << std::setw(12) << t << std::endl;
    outFile << std::setw(12) << t << std::endl;

    delete [] a;
    delete [] b;
  }
  std::endl(std::cout);
}

void RadixEx::runTime_basic( int fromPower2, int num_trials)
{
  std::ofstream outFile;
  outFile.open( "data/RadixSort/radixEx.txt");
  outFile << std::setprecision(3) << std::fixed;

  double t;
  int toPower2, size;
  int* a;

  toPower2 = fromPower2 + num_trials;

  std::cout << "\nRadix Exchange Sort\n" << std::endl;
  std::cout << std::setw(12) << "n";
  std::cout << std::setw(12) << "sorted";
  std::cout << std::setw(12) << "reversed";
  std::cout << std::setw(12) << "shuffled" << std::endl;

  outFile << std::setw(12) << "n";
  outFile << std::setw(12) << "sorted";
  outFile << std::setw(12) << "reversed";
  outFile << std::setw(12) << "shuffled" << std::endl;

  while( fromPower2 < toPower2)
  {
    size = pow( 2, fromPower2++);
    std::cout << std::setw(12) << size;
    outFile << std::setw(12) << size;

    a = new int[size];
    init( a, size);

    t = sort_basic( a, 0, size-1, 31);
    std::cout << std::setw(12) << t;
    outFile << std::setw(12) << t;

    reverse( a, size);

    t = sort_basic( a, 0, size-1, 31);
    std::cout << std::setw(12) << t;
    outFile << std::setw(12) << t;

    shuffle( a, size);

    t = sort_basic( a, 0, size-1, 31);
    std::cout << std::setw(12) << t << std::endl;
    outFile << std::setw(12) << t << std::endl;

    delete [] a;
  }
  std::endl(std::cout);
}
