
# very basic makefile for regression tests
#
# g++ 2.95 and greater
#
CXX= g++ -O2 -pedantic -Wall -I../../../../ -I./ -L../../lib/gcc

total : r2
	./r2 tests.txt

r2 : r2.cpp
	$(CXX) -o r2 r2.cpp -lregex++






































