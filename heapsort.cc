
//##############################################################################
//
// Mark Wheatley
// CSC304
// ArrayFun
// heapsort.cc
//
//##############################################################################

#include "arrayfun.h"



double Heap::sort_basic( int* a, int l, int r)
{
  clock_t t = clock();
  int temp;

  td_heapify( a, r);

  while( r > 0)
  {
    temp = a[l];
    a[l] = a[r];
    a[r] = temp;
    sink( a, r--, 0);
  }
  return (double)(clock()-t)/double(CLOCKS_PER_SEC);
}

double Heap::sort_optimized( int* a, int l, int r)
{
  clock_t t = clock();
  int temp;

  bu_heapify( a, r);

  while( r > 0)
  {
    temp = a[l];
    a[l] = a[r];
    a[r] = temp;
    sink( a, r--, 0);
  }
  return (double)(clock()-t)/double(CLOCKS_PER_SEC);
}

void Heap::td_heapify( int* a, int n)
{
  int i;

  i = 0;
  while( i <= n)
  {
    swim( a, i++);
  }
}

void Heap::bu_heapify( int* a, int n)
{
  int i;

  i = n/2;
  while( i >= 0)
  {
    sink( a, n, i--);
  }
}

void Heap::sink( int* a, int n, int k)
{
  int parent, child;

  parent = a[k];
  while( k < n/2)
  {
    child = (2*k)+1;

    if( child < n-1 && a[child] < a[child+1])
      child++;

    if( parent >= a[child])
      break;

    a[k] = a[child];
    k = child;
  }
  a[k] = parent;
}

void Heap::swim( int* a, int k)
{
  int temp;

  temp = a[k];
  while( k > 0 && a[(k-1)/2] <= temp)
  {
    a[k] = a[(k-1)/2];
    k = (k-1)/2;
  }
  a[k] = temp;
}

void Heap::runTime_basic( int fromPower2, int num_trials)
{
  std::ofstream outFile;
  outFile.open( "data/HeapSort/td_heap.txt");
  outFile << std::setprecision(3) << std::fixed;

  double t;
  int toPower2, size;
  int* a;

  toPower2 = fromPower2 + num_trials;

  std::cout << "\nTop-Down Constructed Heap Sort\n" << std::endl;
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

void Heap::runTime_optimized( int fromPower2, int num_trials)
{
  std::ofstream outFile;
  outFile.open( "data/HeapSort/bu_heap.txt");
  outFile << std::setprecision(3) << std::fixed;

  double t;
  int toPower2, size;
  int* a;

  toPower2 = fromPower2 + num_trials;

  std::cout << "\nBottom-Up Constructed Heap Sort\n" << std::endl;
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

void Heap::disp8( int* a)
{
  int n = 8;

  std::cout << std::setw((4*n)+2) << " " << 0 << " \n";
  std::cout << std::setw((4*n)+2) << "[" << a[0] << "]";

  std::endl(std::cout);
  std::cout << std::setw(3*n) << " " << 1 << " ";
  std::cout << std::setw((2*n)+2) << " " << 2 << " \n";
  std::cout << std::setw(3*n) << "[" << a[1] << "]";
  std::cout << std::setw((2*n)+2) << "[" << a[2] << "]";

  std::endl(std::cout);
  std::cout << std::setw((2*n)+2) << " " << 3 << " ";
  std::cout << std::setw((n/2)+6) << " " << 4 << " ";
  std::cout << std::setw(6) << " " << 5 << " ";
  std::cout << std::setw((n)+2) << " " << 6 << " \n";
  std::cout << std::setw((2*n)+2) << "[" << a[3] << "]";
  std::cout << std::setw((n/2)+6) << "[" << a[4] << "]";
  std::cout << std::setw(6) << "[" << a[5] << "]";
  std::cout << std::setw((n)+2) << "[" << a[6] << "]\n";

  std::endl(std::cout);
  std::cout << std::setw((2*n)-4) << " " << 7 << " \n";
  std::cout << std::setw((2*n)-4) << "[" << a[7] << "]";
  std::endl(std::cout);
}


