# Makefile for timer application
#
# for SUN workshop 5.0 C++ compiler
#

CXX=CC
CPP_FLAGS = -O -I../../../../ -I./

%.o : %.cpp 
	$(CXX) -c -o $@ $(CPP_FLAGS) $<

timer : regex_timer.o timer.o
	$(CXX) -o $@  $(CPP_FLAGS) timer.o regex_timer.o -L../../lib -lregex++

timer.o : ../../../timer/timer.cpp
	$(CXX) -c $(CPPFLAGS) ../../../timer/timer.cpp

clean:
	rm -rf SunWS_cache
	rm -f timer.o timer



