
//##############################################################################
//
// Mark Wheatley
// CSC304
// ArrayFun
// mergesort.cc
//
//##############################################################################

#include "arrayfun.h"

void MergeBu::buildHeap( int* a, minHeap* h, int f, int g, int k)
{
  int i;
  i = 0;
  while( i < k)
  {
    h[i].entry = a[f+(i*(g/k))];
    h[i].icur = f+(i*(g/k));
    h[i].iend = f+((i+1)*(g/k));
    //++i;
    swim( h, i++);
  }

#if 0
  i = k/2;
  while( i >= 0)
  {
    heapify( h, k, i--);
  }
#endif
}
void MergeBu::swim( minHeap* h, int k)
{
  minHeap temp;

  temp = h[k];
  while( k > 0 && h[(k-1)/2].entry >= temp.entry)
  {
    h[k] = h[(k-1)/2];
    k = (k-1)/2;
  }
  h[k] = temp;
}

void MergeBu::heapify( minHeap* h, int n, int k)
{
  minHeap parent;
  int child;

  parent = h[k];
  while( k < n/2)
  {
    child = (2*k)+1;

    if( child < n-1 && h[child].entry > h[child+1].entry)
      ++child;

    if( parent.entry <= h[child].entry)
      break;

    h[k] = h[child];
    k = child;
  }
  h[k] = parent;
}

double MergeTd::sort_basic( int* a, int* b, int l, int r)
{
  clock_t t = clock();
  static int n = r+1;
  int m;

  if( r > l)
  {
    m = ((l+r)/2)+1;
    MergeTd::sort_basic( a, b, l, m-1);
    MergeTd::sort_basic( a, b, m, r);
    merge( a, b, l, r);
    copy( a, b, l, r);
  }
  return (double)(clock()-t)/(double)CLOCKS_PER_SEC;
}

double MergeTd::sort_optimized( int* a, int* b, int l, int r)
{
  clock_t t = clock();
  static int n = r+1;
  int m;

  if( r > l+8)
  {
    m = ((l+r)/2)+1;
    MergeTd::sort_optimized( b, a, l, m-1);
    MergeTd::sort_optimized( b, a, m, r);

    if( a[m-1] < a[m])
    {
      return (double)(clock()-t)/(double)CLOCKS_PER_SEC;
    }
    merge( a, b, l, r);
  }
  else
  {
    Insertion::insertion_sort( b, l, r);
  }
  if( b[l] == l && b[m] == m && b[r] == r)
  {
    copy( a, b, l, r);
  }
  return (double)(clock()-t)/(double)CLOCKS_PER_SEC;
}

void MergeTd::merge( int* a, int* b, int l, int r)
{
  int i, m, lend;

  i = l;
  m = (r+l+1)/2;
  lend = m-1;

  while( (l <= lend) || (m <= r))
  {
    if( l <= lend && m <= r)
    {
      if( a[l] < a[m])
      {
        b[i++] = a[l++];
      }
      else
      {
        b[i++] = a[m++];
      }
    }
    else if( l > lend)
    {
      b[i++] = a[m++];
    }
    else if( m > r)
    {
      b[i++] = a[l++];
    }
  }
}

double MergeBu::sort_basic( int* a, int* b, int l, int r)
{
  clock_t t0, t = clock();
  int i, j, n;

  n = r+1;
  for( i=1; i<n; i*=2)
  {
    for( j=0; j<n; j+=2*i)
    {
      l = j;
      r = j+(2*i)-1;

      MergeTd::merge( a, b, l, r);
      copy( a, b, l, r);
    }
  }
  return (double)(clock()-t)/(double)CLOCKS_PER_SEC;
}

double MergeBu::sort_optimized( int* &a, int* &b, int l, int r)
{
  clock_t t = clock();
  int* temp;
  int i, j, k0, k, m, n0, n = r+1;

  k = 16;
  minHeap* h = new minHeap[k];

  k0 = n;
  while( k0 % k == 0)
  {
    k0 /= k;
  }
  n0 = n/k0;

  i = 1; portal:
  while( i < n0)
  {
    j = 0;
    while( j < n)
    {
      l = j;
      r = (j+=k*i)-1;

      if( r > (l+16))
      {
        buildHeap( a, h, l, (r-l+1), k);
        k_merge( a, b, h, l, r, k);
      }
      else Insertion::insertion_sort( b, l, r);
    }
    i*=k;

    temp = a;
    a = b;
    b = temp;
  }
  if( k0 > 1)
  {
    i = n0;
    n0 = n;
    k = k0;
    k0 = 0; goto portal;
  }
  delete [] h;

  return (double)(clock()-t)/(double)CLOCKS_PER_SEC;
}

void MergeBu::k_merge( int* &a, int* &b, minHeap* h, int l, int r, int k)
{
  int i;

  i = l;
  while( i <= r)
  {
    minHeap root = h[0];
    b[i++] = root.entry;

    root.entry = (root.icur < root.iend-1) ? a[++root.icur] : INT_MAX;

    h[0] = root;
    heapify(h, k, 0);
  }
}

void MergeTd::runTime_basic( int fromPower2, int num_trials)
{
  std::ofstream outFile;
  outFile.open( "data/MergeSort/td_merge.txt");
  outFile << std::setprecision(3) << std::fixed;

  double t;
  int toPower2, size;
  int* a;
  int* b;

  toPower2 = fromPower2 + num_trials;

  std::cout << "\nTop-Down Merge Sort\n" << std::endl;
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
    copy( b, a, 0, size-1);

    t = sort_basic( a, b, 0, size-1);
    std::cout << std::setw(12) << t;
    outFile << std::setw(12) << t;

    reverse( a, size);
    copy( b, a, 0, size-1);

    t = sort_basic( a, b, 0, size-1);
    std::cout << std::setw(12) << t;
    outFile << std::setw(12) << t;

    shuffle( a, size);
    copy( b, a, 0, size-1);

    t = sort_basic( a, b, 0, size-1);
    std::cout << std::setw(12) << t << std::endl;
    outFile << std::setw(12) << t << std::endl;

    delete [] a;
    delete [] b;
  }
  std::endl(std::cout);
}

void MergeBu::runTime_basic( int fromPower2, int num_trials)
{
  std::ofstream outFile;
  outFile.open( "data/MergeSort/bu_merge.txt");
  outFile << std::setprecision(3) << std::fixed;

  double t;
  int toPower2, size;
  int* a;
  int* b;

  toPower2 = fromPower2 + num_trials;

  std::cout << "\nBottom-Up Merge Sort\n" << std::endl;
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
    copy( b, a, 0, size-1);

    t = sort_basic( a, b, 0, size-1);
    std::cout << std::setw(12) << t;
    outFile << std::setw(12) << t;

    reverse( a, size);
    copy( b, a, 0, size-1);

    t = sort_basic( a, b, 0, size-1);
    std::cout << std::setw(12) << t;
    outFile << std::setw(12) << t;

    shuffle( a, size);
    copy( b, a, 0, size-1);

    t = sort_basic( a, b, 0, size-1);
    std::cout << std::setw(12) << t << std::endl;
    outFile << std::setw(12) << t << std::endl;

    delete [] a;
    delete [] b;
  }
  std::endl(std::cout);
}

void MergeTd::runTime_optimized( int fromPower2, int num_trials)
{
  std::ofstream outFile;
  outFile.open( "data/MergeSort/td_merge_op.txt");
  outFile << std::setprecision(3) << std::fixed;

  double t;
  int toPower2, size;
  int* a;
  int* b;

  toPower2 = fromPower2 + num_trials;

  std::cout << "\nOptimized Top-Down Merge Sort\n" << std::endl;
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
    copy( b, a, 0, size-1);

    t = sort_optimized( a, b, 0, size-1);
    std::cout << std::setw(12) << t;
    outFile << std::setw(12) << t;

    reverse( a, size);
    copy( b, a, 0, size-1);

    t = sort_optimized( a, b, 0, size-1);
    std::cout << std::setw(12) << t;
    outFile << std::setw(12) << t;

    shuffle( a, size);
    copy( b, a, 0, size-1);

    t = sort_optimized( a, b, 0, size-1);
    std::cout << std::setw(12) << t << std::endl;
    outFile << std::setw(12) << t << std::endl;

    delete [] a;
    delete [] b;
  }
  std::endl(std::cout);
}

void MergeBu::runTime_optimized( int fromPower2, int num_trials)
{
  std::ofstream outFile;
  outFile.open( "data/MergeSort/bu_merge_op.txt");
  outFile << std::setprecision(3) << std::fixed;

  double t;
  int toPower2, size;
  int* a;
  int* b;

  toPower2 = fromPower2 + num_trials;

  std::cout << "\nOptimized Bottom-Up Merge Sort\n" << std::endl;
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
    copy( b, a, 0, size-1);

    t = sort_optimized( a, b, 0, size-1);
    std::cout << std::setw(12) << t;
    outFile << std::setw(12) << t;

    reverse( a, size);
    copy( b, a, 0, size-1);

    t = sort_optimized( a, b, 0, size-1);
    std::cout << std::setw(12) << t;
    outFile << std::setw(12) << t;

    shuffle( a, size);
    copy( b, a, 0, size-1);

    t = sort_optimized( a, b, 0, size-1);
    std::cout << std::setw(12) << t << std::endl;
    outFile << std::setw(12) << t << std::endl;

    delete [] a;
    delete [] b;
  }
  std::endl(std::cout);
}

