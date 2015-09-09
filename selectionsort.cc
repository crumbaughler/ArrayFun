
//##############################################################################
//
// Mark Wheatley
// CSC304
// ArrayFun
// selectionsort.cc
//
//##############################################################################

#include "arrayfun.h"

double Selection::sort_basic( int* a, int l, int r)
{
  clock_t t = clock();
  int i, j, cur, temp;

  for( i=l; i<r; i++)
  {
    cur = i;
    for( j=i+1; j<=r; j++)
    {
      if( a[j] < a[cur])
      {
        cur = j;
      }
    }
    if( cur != i)
    {
      temp = a[i];
      a[i] = a[cur];
      a[cur] = temp;
    }
  }
  return (double)(clock()-t)/(double)CLOCKS_PER_SEC;
}

void Selection::runTime_basic( int fromPower2, int num_trials)
{
  std::ofstream outFile;
  outFile.open( "data/SelectionSort/selection.txt");
  outFile << std::setprecision(3) << std::fixed;

  double t;
  int toPower2, size;
  int* a;

  toPower2 = fromPower2 + num_trials;

  std::cout << "\nSelection Sort\n" << std::endl;
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
