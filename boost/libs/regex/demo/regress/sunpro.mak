# Makefile for timer application
#
# for SUN workshop 5.0 C++ compiler
#

CXX=CC
CPP_FLAGS = -O -I../../../../ -I./

all: r2 r5
	r2 tests.txt
	r5 tests.txt

%.o : %.cpp 
	$(CXX) -c -o $@ $(CPP_FLAGS) $<

r2 : tests.cpp parse.cpp regress.cpp
	$(CXX) -o $@  $(CPP_FLAGS) tests.cpp parse.cpp regress.cpp -L../../lib -lregex++

r5 : tests.cpp parse.cpp regress.cpp
	$(CXX) -o $@  $(CPP_FLAGS) -DTEST_UNICODE tests.cpp parse.cpp regress.cpp -L../../lib -lregex++

clean:
	rm -rf SunWS_cache
	rm -f r2.o r2 r5 r5.o





