
//##############################################################################
//
// Mark Wheatley
// CSC304
// ArrayFun
// quicksort.cc
//
//##############################################################################

#include "arrayfun.h"

double Quick::sort_basic( int* a, int l, int r)
{
  clock_t t = clock();
  int i, j, temp, pivot;

  i = l-1;
  j = r;

  pivot = medianOfThree( a, l, r);
  //std::cout << "pivot = " << pivot << " ";
  //dispPivot( a, pivot, l, r);
  //std::endl(std::cout);

  if( r-l > 1)
  {
    while(1)
    {
      while( a[++i] < pivot);
      while( a[--j] > pivot);
      if( i >= j) break;

      std::swap( a[i], a[j]);
    }
    std::swap( a[i], a[r]);

    //disp0( a, l, r);
    //std::endl(std::cout);
    //std::endl(std::cout);
    Quick::sort_basic( a, l, i-1);
    Quick::sort_basic( a, i+1, r);
  }
  return (double)(clock()-t)/(double)CLOCKS_PER_SEC;
}

double Quick::sort_optimized( int* a, int l, int r)
{
  clock_t t = clock();
  int i, j, temp, pivot;

  i = l-1;
  j = r;
  pivot = medianOfThree( a, l, r);

  if( r-l > 1)
  {
    while(1)
    {
      while( a[++i] < pivot);
      while( a[--j] > pivot);
      if( i >= j) break;

      temp = a[i];
      a[i] = a[j];
      a[j] = temp;
    }
    temp = a[i];
    a[i] = a[r];
    a[r] = temp;

    if( (i-1)-l > 32)
    {
      //disp0( a, l, i-1);
      //std::endl(std::cout);
      Quick::sort_optimized( a, l, i-1);
    }
    else
    {
      //disp0( a, l, j);
      //std::cout << "bail" << std::endl;
      Insertion::insertion_sort( a, l, i-1);
    }

    if( r-(i+1) > 32)
    {
      //disp0( a, i+1, r);
      //std::endl(std::cout);
      Quick::sort_optimized( a, i+1, r);
    }
    else
    {
      //disp0( a, i+1, r);
      //std::cout << "bail" << std::endl;
      Insertion::insertion_sort( a, i+1, r);
    }
  }
  return (double)(clock()-t)/(double)CLOCKS_PER_SEC;
}

int Quick::medianOfThree( int* a, int l, int r)
{
  int m, pivot, temp;

  m = (l+r+1)/2;

  if( a[l] > a[m])
  {
    temp = a[l];
    a[l] = a[m];
    a[m] = temp;
  }
  if( a[l] > a[r])
  {
    temp = a[l];
    a[l] = a[r];
    a[r] = temp;
  }
  if( a[r] > a[m])
  {
    temp = a[r];
    a[r] = a[m];
    a[m] = temp;
  }
  return a[r];
}
void Quick::dispPivot( int* a, int pivot, int l, int r)
{
  int i;

  std::cout << "[ ";
  for( i=l; i<=r; i++)
  {
    if( a[i] == pivot)
    {
      std::cout << "(" << a[i] << ") ";
    }
    else
    {
      std::cout << a[i] << " ";
    }
  }
  std::cout << "]\n";
}

void Quick::runTime_basic( int fromPower2, int num_trials)
{
  std::ofstream outFile;
  outFile.open( "data/QuickSort/quick.txt");
  outFile << std::setprecision(3) << std::fixed;

  double t;
  int toPower2, size;
  int* a;

  toPower2 = fromPower2 + num_trials;

  std::cout << "\nQuick Sort\n" << std::endl;
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

    t = sort_basic( a, 0, size-1);
    std::cout << std::setw(12) << t;
    outFile << std::setw(12) << t;

    reverse( a, size);

    t = sort_basic( a, 0, size-1);
    std::cout << std::setw(12) << t;
    outFile << std::setw(12) << t;

    shuffle( a, size);

    t = sort_basic( a, 0, size-1);
    std::cout << std::setw(12) << t << std::endl;
    outFile << std::setw(12) << t << std::endl;

    delete [] a;
  }
  std::endl(std::cout);
}

void Quick::runTime_optimized( int fromPower2, int num_trials)
{
  std::ofstream outFile;
  outFile.open( "data/QuickSort/quick_op.txt");
  outFile << std::setprecision(3) << std::fixed;

  double t;
  int toPower2, size;
  int* a;

  toPower2 = fromPower2 + num_trials;

  std::cout << "\nOptimized Quick Sort\n" << std::endl;
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

    t = sort_optimized( a, 0, size-1);
    std::cout << std::setw(12) << t;
    outFile << std::setw(12) << t;

    reverse( a, size);

    t = sort_optimized( a, 0, size-1);
    std::cout << std::setw(12) << t;
    outFile << std::setw(12) << t;

    shuffle( a, size);

    t = sort_optimized( a, 0, size-1);
    std::cout << std::setw(12) << t << std::endl;
    outFile << std::setw(12) << t << std::endl;

    delete [] a;
  }
  std::endl(std::cout);
}
