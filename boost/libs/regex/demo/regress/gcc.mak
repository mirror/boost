
# very basic makefile for regression tests
#
# g++ 2.95 and greater
#
CXX= g++ -pedantic -Wall -I../../../../ -I./ -L../../lib/gcc

total : r2
	./r2 tests.txt

r2 : tests.cpp parse.cpp regress.cpp
	$(CXX) -O2 -o r2 tests.cpp parse.cpp regress.cpp -lregex++

debug : tests.cpp parse.cpp regress.cpp
	$(CXX) -g -o r2 tests.cpp parse.cpp regress.cpp -lregex++debug







































