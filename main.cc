
//##############################################################################
//
// Mark Wheatley
// CSC304
// ArrayFun
// main.cc
//
//##############################################################################

#include "arrayfun.h"

int main( int argc, char** argv)
{
  std::cout << std::setprecision(3) << std::fixed;

  int power;
  int trials;

  ArrayFun* afp[9];
  afp[0] = new ArrayFun;
  afp[1] = new Selection;
  afp[2] = new Insertion;
  afp[3] = new Quick;
  afp[4] = new MergeTd;
  afp[5] = new MergeBu;
  afp[6] = new Heap;
  afp[7] = new Radix;
  afp[8] = new RadixEx;

#if 0

  double t;
  int size = pow( 2, 24);
  int* a = new int[size];
  int* b = new int[size];

  afp[0]->init( a, size);
  afp[0]->shuffle( a, size);
  //afp[0]->disp( a, size);
  afp[0]->copy( b, a, 0, size-1);

  t = afp[5]->sort_optimized( a, b, 0, size-1);
  std::cout << ((afp[0]->is_sorted(a,size))?("Is sorted. "):("Is not sorted. "));
  std::cout << t << std::endl;

  delete [] a;
  delete [] b;

#else

  power = 20;
  trials = 5;

  //afp[1]->runTime_basic( 14, trials);

  //afp[2]->runTime_basic( 14, trials);

  //afp[3]->runTime_basic( power, trials);
  //afp[3]->runTime_optimized( power, trials);

  //afp[5]->runTime_basic( power, trials);
  afp[5]->runTime_optimized( power, trials);

  //afp[3]->runTime_basic( power, trials);
  //afp[3]->runTime_optimized( power, trials);

  //afp[6]->runTime_basic( power, trials);
  //afp[6]->runTime_optimized( power, trials);

  //afp[7]->runTime_basic( power, trials);

  //afp[8]->runTime_basic( power, trials);

#endif

  return 0;
}

