#
# auto generated makefile for gcc compiler
#
# usage:
# make
#   brings libraries up to date
# make clean
#   deletes temporary object files (but not archives).
#

#
# the following environment variables are recognised:
# CXXFLAGS= extra compiler options - note applies to all build variants
# INCLUDES= additional include directories
# LDFLAGS=  additional linker options
# LIBS=     additional library files

# compiler:
CXX=g++
LINKER=g++ -shared

#
# compiler options for release build:
#
C1=-c -O2 -I../../../
#
# compiler options for debug build:
#
C2=-c -g -I../../../



ALL_HEADER=../../../boost/cregex.hpp ../../../boost/pattern_except.hpp ../../../boost/regex.hpp ../../../boost/regex_traits.hpp ../../../boost/re_detail/fileiter.hpp ../../../boost/re_detail/regex_compile.hpp ../../../boost/re_detail/regex_config.hpp ../../../boost/re_detail/regex_cstring.hpp ../../../boost/re_detail/regex_format.hpp ../../../boost/re_detail/regex_kmp.hpp ../../../boost/re_detail/regex_library_include.hpp ../../../boost/re_detail/regex_match.hpp ../../../boost/re_detail/regex_options.hpp ../../../boost/re_detail/regex_raw_buffer.hpp ../../../boost/re_detail/regex_split.hpp ../../../boost/re_detail/regex_stack.hpp ../../../boost/re_detail/regex_synch.hpp

all : gcc  gcc gcc/boost_regex ./gcc/libboost_regex.a gcc gcc/boost_regex_debug ./gcc/libboost_regex_debug.a

gcc :
	mkdir -p gcc

clean :  boost_regex_clean boost_regex_debug_clean

install : all



########################################################
#
# section for libboost_regex.a
#
########################################################
gcc/boost_regex/c_regex_traits.o: ../src/c_regex_traits.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o gcc/boost_regex/c_regex_traits.o $(C1) $(CXXFLAGS) ../src/c_regex_traits.cpp

gcc/boost_regex/c_regex_traits_common.o: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o gcc/boost_regex/c_regex_traits_common.o $(C1) $(CXXFLAGS) ../src/c_regex_traits_common.cpp

gcc/boost_regex/cpp_regex_traits.o: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o gcc/boost_regex/cpp_regex_traits.o $(C1) $(CXXFLAGS) ../src/cpp_regex_traits.cpp

gcc/boost_regex/cregex.o: ../src/cregex.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o gcc/boost_regex/cregex.o $(C1) $(CXXFLAGS) ../src/cregex.cpp

gcc/boost_regex/fileiter.o: ../src/fileiter.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o gcc/boost_regex/fileiter.o $(C1) $(CXXFLAGS) ../src/fileiter.cpp

gcc/boost_regex/posix_api.o: ../src/posix_api.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o gcc/boost_regex/posix_api.o $(C1) $(CXXFLAGS) ../src/posix_api.cpp

gcc/boost_regex/regex.o: ../src/regex.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o gcc/boost_regex/regex.o $(C1) $(CXXFLAGS) ../src/regex.cpp

gcc/boost_regex/regex_debug.o: ../src/regex_debug.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o gcc/boost_regex/regex_debug.o $(C1) $(CXXFLAGS) ../src/regex_debug.cpp

gcc/boost_regex/regex_synch.o: ../src/regex_synch.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o gcc/boost_regex/regex_synch.o $(C1) $(CXXFLAGS) ../src/regex_synch.cpp

gcc/boost_regex/w32_regex_traits.o: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o gcc/boost_regex/w32_regex_traits.o $(C1) $(CXXFLAGS) ../src/w32_regex_traits.cpp

gcc/boost_regex/wide_posix_api.o: ../src/wide_posix_api.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o gcc/boost_regex/wide_posix_api.o $(C1) $(CXXFLAGS) ../src/wide_posix_api.cpp

gcc/boost_regex : 
	mkdir -p gcc/boost_regex

boost_regex_clean :
	rm -f gcc/boost_regex/*.o

./gcc/libboost_regex.a : gcc/boost_regex/c_regex_traits.o gcc/boost_regex/c_regex_traits_common.o gcc/boost_regex/cpp_regex_traits.o gcc/boost_regex/cregex.o gcc/boost_regex/fileiter.o gcc/boost_regex/posix_api.o gcc/boost_regex/regex.o gcc/boost_regex/regex_debug.o gcc/boost_regex/regex_synch.o gcc/boost_regex/w32_regex_traits.o gcc/boost_regex/wide_posix_api.o
	ar -r gcc/libboost_regex.a  gcc/boost_regex/c_regex_traits.o gcc/boost_regex/c_regex_traits_common.o gcc/boost_regex/cpp_regex_traits.o gcc/boost_regex/cregex.o gcc/boost_regex/fileiter.o gcc/boost_regex/posix_api.o gcc/boost_regex/regex.o gcc/boost_regex/regex_debug.o gcc/boost_regex/regex_synch.o gcc/boost_regex/w32_regex_traits.o gcc/boost_regex/wide_posix_api.o

########################################################
#
# section for libboost_regex_debug.a
#
########################################################
gcc/boost_regex_debug/c_regex_traits.o: ../src/c_regex_traits.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o gcc/boost_regex_debug/c_regex_traits.o $(C2) $(CXXFLAGS) ../src/c_regex_traits.cpp

gcc/boost_regex_debug/c_regex_traits_common.o: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o gcc/boost_regex_debug/c_regex_traits_common.o $(C2) $(CXXFLAGS) ../src/c_regex_traits_common.cpp

gcc/boost_regex_debug/cpp_regex_traits.o: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o gcc/boost_regex_debug/cpp_regex_traits.o $(C2) $(CXXFLAGS) ../src/cpp_regex_traits.cpp

gcc/boost_regex_debug/cregex.o: ../src/cregex.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o gcc/boost_regex_debug/cregex.o $(C2) $(CXXFLAGS) ../src/cregex.cpp

gcc/boost_regex_debug/fileiter.o: ../src/fileiter.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o gcc/boost_regex_debug/fileiter.o $(C2) $(CXXFLAGS) ../src/fileiter.cpp

gcc/boost_regex_debug/posix_api.o: ../src/posix_api.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o gcc/boost_regex_debug/posix_api.o $(C2) $(CXXFLAGS) ../src/posix_api.cpp

gcc/boost_regex_debug/regex.o: ../src/regex.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o gcc/boost_regex_debug/regex.o $(C2) $(CXXFLAGS) ../src/regex.cpp

gcc/boost_regex_debug/regex_debug.o: ../src/regex_debug.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o gcc/boost_regex_debug/regex_debug.o $(C2) $(CXXFLAGS) ../src/regex_debug.cpp

gcc/boost_regex_debug/regex_synch.o: ../src/regex_synch.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o gcc/boost_regex_debug/regex_synch.o $(C2) $(CXXFLAGS) ../src/regex_synch.cpp

gcc/boost_regex_debug/w32_regex_traits.o: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o gcc/boost_regex_debug/w32_regex_traits.o $(C2) $(CXXFLAGS) ../src/w32_regex_traits.cpp

gcc/boost_regex_debug/wide_posix_api.o: ../src/wide_posix_api.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o gcc/boost_regex_debug/wide_posix_api.o $(C2) $(CXXFLAGS) ../src/wide_posix_api.cpp

gcc/boost_regex_debug : 
	mkdir -p gcc/boost_regex_debug

boost_regex_debug_clean :
	rm -f gcc/boost_regex_debug/*.o

./gcc/libboost_regex_debug.a : gcc/boost_regex_debug/c_regex_traits.o gcc/boost_regex_debug/c_regex_traits_common.o gcc/boost_regex_debug/cpp_regex_traits.o gcc/boost_regex_debug/cregex.o gcc/boost_regex_debug/fileiter.o gcc/boost_regex_debug/posix_api.o gcc/boost_regex_debug/regex.o gcc/boost_regex_debug/regex_debug.o gcc/boost_regex_debug/regex_synch.o gcc/boost_regex_debug/w32_regex_traits.o gcc/boost_regex_debug/wide_posix_api.o
	ar -r gcc/libboost_regex_debug.a  gcc/boost_regex_debug/c_regex_traits.o gcc/boost_regex_debug/c_regex_traits_common.o gcc/boost_regex_debug/cpp_regex_traits.o gcc/boost_regex_debug/cregex.o gcc/boost_regex_debug/fileiter.o gcc/boost_regex_debug/posix_api.o gcc/boost_regex_debug/regex.o gcc/boost_regex_debug/regex_debug.o gcc/boost_regex_debug/regex_synch.o gcc/boost_regex_debug/w32_regex_traits.o gcc/boost_regex_debug/wide_posix_api.o

