
# very basic makefile for jgrep
#
# GNU compiler g++
#
CXX= $(INCLUDES) -O2 -I../../../../ -I./ $(CXXFLAGS) $(LDFLAGS)

jgrep : jgrep.cpp main.cpp
	g++ -ojgrep $(CXX) jgrep.cpp main.cpp -L../../lib/gcc -lregex++ $(LIBS)

debug : jgrep.cpp main.cpp
	g++ -ojgrep -I../../../../ -I./ -g jgrep.cpp main.cpp -L../../lib/gcc -lregex++debug $(LIBS)



















