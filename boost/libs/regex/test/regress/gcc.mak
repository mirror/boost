
# very basic makefile for regression tests
#
# g++ 2.95 and greater
#
CXX= g++ $(INCLUDES) -I../../../../ -I./ $(CXXFLAGS) -L../../build/gcc $(LDFLAGS)

total : gcc_regress
	./gcc_regress tests.txt

gcc_regress : tests.cpp parse.cpp regress.cpp
	$(CXX) -O2 -o gcc_regress tests.cpp parse.cpp regress.cpp -lboost_regex $(LIBS)

debug : tests.cpp parse.cpp regress.cpp
	$(CXX) -g -o gcc_regress tests.cpp parse.cpp regress.cpp -lboost_regex_debug $(LIBS)











































