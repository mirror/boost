
# very basic makefile for regress.exe
#
# egcs compiler GCC
#
CXX= g++ -O2 -pedantic -Wall -I../../../../ -I./

total : r2.exe
	r2 tests.txt
	r5 tests.txt

r2.exe : r2.cpp
	$(CXX) -or2.exe r2.cpp -L../../lib -lregex++





































