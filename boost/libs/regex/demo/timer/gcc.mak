
# very basic makefile for timer.exe
#
# egcs compiler GCC
#
CXX= -O2 -I../../../../ -I./

timer : regex_timer.o timer.o 
	g++ -o -L../../lib/gcc timer regex_timer.o timer.o -lregex++

timer.o : ../../../timer/timer.cpp
	g++ -c $(CXX)  ../../../timer/timer.cpp

regex_timer.o : regex_timer.cpp
	g++ -c $(CXX)  regex_timer.cpp


















