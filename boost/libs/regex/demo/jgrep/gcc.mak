
# very basic makefile for jgrep
#
# GNU compiler g++
#
CXX= -O2 -I../../../../ -I./

jgrep : jgrep.cpp main.cpp
	g++ -ojgrep $(CXX) jgrep.cpp main.cpp -L../../lib/gcc -lregex++

debug : jgrep.cpp main.cpp
	g++ -ojgrep -I../../../../ -I./ -g jgrep.cpp main.cpp -L../../lib/gcc -lregex++debug


















