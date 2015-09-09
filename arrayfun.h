
//##############################################################################
//
// Mark Wheatley
// CSC304
// ArrayFun
// arrayfun.h
//
//##############################################################################

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <ctime>

class ArrayFun {

public:

  void init( int* a, int n);
  void shuffle( int* a, int n);
  void reverse( int* a, int n);
  static void disp( int* a, int n);
  static void disp0( int* a, int l, int r);
  static void copy( int* cpy, int* src, int l, int r);
  static void swap( int* x, int* y);
  static bool is_sorted( int* a, int n);

  virtual double sort_basic( int* a, int l, int r) { return 1;};
  virtual double sort_basic( int* a, int* b, int l, int r) { return 1;};
  virtual double sort_basic( int* a, int l, int r, int bit) { return 1;};

  virtual double sort_optimized( int* a, int l, int r) { return 1;};
  virtual double sort_optimized( int* &a, int* &b, int l, int r) { return 1;};


  virtual void runTime_basic( int fromPower2, int num_trials) {};
  virtual void runTime_optimized( int fromPower2, int num_trials) {};
};

class Selection : public ArrayFun {

public:

  double sort_basic( int* a, int l, int r);
  void runTime_basic( int fromPower2, int num_trials);
};

class Insertion : public ArrayFun {

public:

  double sort_basic( int* a, int l, int r);
  static void insertion_sort( int* a, int l, int r);
  void runTime_basic( int fromPower2, int num_trials);
};

class Quick : public ArrayFun {

public:

  double sort_basic( int* a, int l, int r);
  double sort_optimized( int* a, int l, int r);
  int medianOfThree( int* a, int l, int r);
  void dispPivot( int* a, int pivot, int l, int r);
  void runTime_basic( int fromPower2, int num_trials);
  void runTime_optimized( int fromPower2, int num_trials);
};

class MergeTd : public ArrayFun {

public:

  double sort_basic( int* a, int* b, int l, int r);
  double sort_optimized( int* a, int*b, int l, int r);
  static void merge( int* a, int* b, int l, int r);
  void runTime_basic( int fromPower2, int num_trials);
  void runTime_optimized( int fromPower2, int num_trials);
};

struct minHeap { int entry, icur, iend; };

class MergeBu : public ArrayFun {

public:

  minHeap* h;

  void buildHeap( int* a, minHeap* h, int f, int g, int k);
  void swim( minHeap* h, int k);
  void heapify( minHeap* h, int n, int k);
  double sort_basic( int* a, int* b, int l, int r);
  double sort_optimized( int* &a, int* &b, int l, int r);
  void k_merge( int* &a, int* &b, minHeap* h, int l, int r, int k);
  void runTime_basic( int fromPower2, int num_trials);
  void runTime_optimized( int fromPower2, int num_trials);

};

class Heap : public ArrayFun {

public:

  double sort_basic( int* a, int l, int r);
  double sort_optimized( int* a, int l, int r);
  void td_heapify( int* a, int n);
  void bu_heapify( int* a, int n);
  void sink( int* a, int n, int k);
  void swim( int* a, int k);
  void runTime_basic( int fromPower2, int num_trials);
  void runTime_optimized( int fromPower2, int num_trials);
  void disp8( int* a);
};

class Radix : public ArrayFun {

public:

  double sort_basic( int* a, int* b, int l, int r);
  static unsigned bits( int x, int k, unsigned j);
  void runTime_basic( int fromPower2, int num_trials);
};

class RadixEx : public ArrayFun {

public:

  double sort_basic( int* a, int l, int r, int bit);
  void runTime_basic( int fromPower2, int num_trials);
};

