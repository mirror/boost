

regress :
	g++ -fprofile-arcs -ftest-coverage -DBOOST_REGEX_RECURSIVE -DBOOST_REGEX_BLOCKSIZE=512 -DBOOST_REGEX_MAX_CACHE_BLOCKS=0 -DBOOST_REGEX_MATCH_EXTRA -g -I../../../../ -o regress ../regress/*.cpp ../../src/*.cpp ../../../test/src/ex*.cpp ../../../test/src/cpp_main.cpp
	./regress
	gcov basic_tests.cpp





