
# very basic makefile for regression tests
#
# g++ 2.95 and greater
#
CXX= g++ $(INCLUDES) -pedantic -Wall -I../../../../ -I./ $(CXXFLAGS) -L../../build/gcc $(LDFLAGS)

total : r2
	./r2 tests.txt

r2 : tests.cpp parse.cpp regress.cpp
	$(CXX) -O2 -o r2 tests.cpp parse.cpp regress.cpp -lboost_regex $(LIBS)

debug : tests.cpp parse.cpp regress.cpp
	$(CXX) -g -o r2 tests.cpp parse.cpp regress.cpp -lboost_regex_debug $(LIBS)









































