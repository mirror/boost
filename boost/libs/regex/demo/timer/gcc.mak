
# very basic makefile for timer.exe
#
# GNU compiler GCC
#
CXX=-I../../../../ -I./

timer : regex_timer.cpp timer.cpp 
	g++ $(CXX) -O2 -o timer regex_timer.cpp timer.cpp -L../../lib/gcc -lregex++

debug : regex_timer.cpp timer.cpp 
	g++ $(CXX) -g -o timer regex_timer.cpp timer.cpp -L../../lib/gcc -lregex++debug


















