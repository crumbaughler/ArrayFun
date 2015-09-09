
################################################################################
#
# Mark Wheatley
# CSC304
# ArrayFun
# Makefile
#
################################################################################

a.out: main.cc arrayfun.o selectionsort.o insertionsort.o quicksort.o mergesort.o heapsort.o radixsort.o
	g++ -O2 main.cc arrayfun.o selectionsort.o insertionsort.o quicksort.o mergesort.o heapsort.o radixsort.o

arrayfun.o: arrayfun.cc arrayfun.h 
	g++ -O2 -c arrayfun.cc 

selectionsort.o: selectionsort.cc arrayfun.h 
	g++ -O2 -c selectionsort.cc 

insertionsort.o: insertionsort.cc arrayfun.h 
	g++ -O2 -c insertionsort.cc 

quicksort.o: quicksort.cc arrayfun.h 
	g++ -O2 -c quicksort.cc 

mergesort.o: mergesort.cc arrayfun.h 
	g++ -O2 -c mergesort.cc 

heapsort.o: heapsort.cc arrayfun.h 
	g++ -O2 -c heapsort.cc 

radixsort.o: radixsort.cc arrayfun.h 
	g++ -O2 -c radixsort.cc 

