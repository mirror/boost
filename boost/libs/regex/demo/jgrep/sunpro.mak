# Makefile for timer application
#
# for SUN workshop 5.0 C++ compiler
#

CXX=CC
CPP_FLAGS = -O -I../../../../ -I./

%.o : %.cpp 
	$(CXX) -c -o $@ $(CPP_FLAGS) $<

jgrep : jgrep.o main.o
	$(CXX) -o $@  $(CPP_FLAGS) jgrep.o main.o -L../../lib -lregex++

clean:
	rm -rf SunWS_cache
	rm -f jgrep.o jgrep main.o



