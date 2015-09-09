
//##############################################################################
//
// Mark Wheatley
// CSC304
// ArrayFun
// insertionsort.cc
//
//##############################################################################

#include "arrayfun.h"

double Insertion::sort_basic( int* a, int l, int r)
{
  clock_t t = clock();
  int i, j, temp;

  i = l;
  while( i <= r)
  {
    j = i;
    temp = a[j];

    while( (j > l) && (temp < a[j-1]))
    {
      a[j] = a[j-1];
      --j;
    }
    a[j] = temp;
    ++i;
  }
  return (double)(clock()-t)/(double)CLOCKS_PER_SEC;
}

void Insertion::insertion_sort( int* a, int l, int r)
{
  int i, j, temp;

  i = l;
  while( i <= r)
  {
    j = i;
    temp = a[j];

    while( (j > l) && (temp < a[j-1]))
    {
      a[j] = a[j-1];
      --j;
    }
    a[j] = temp;
    ++i;
  }
}

void Insertion::runTime_basic( int fromPower2, int num_trials)
{
  std::ofstream outFile;
  outFile.open( "data/InsertionSort/insertion.txt");
  outFile << std::setprecision(3) << std::fixed;

  double t;
  int toPower2, size;
  int* a;

  toPower2 = fromPower2 + num_trials;

  std::cout << "\nInsertion Sort\n" << std::endl;
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
