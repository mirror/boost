#
# auto generated makefile for generic compiler
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
# CXX=      compiler to use
# LINKER=   linker/archiver to use
# name of subdirectory to use for object/archive files:
DIRNAME=generic

#
# default compiler options for release build:
#
C1=-c -O2 -I../../../



ALL_HEADER=../../../boost/cregex.hpp ../../../boost/pattern_except.hpp ../../../boost/regex.hpp ../../../boost/regex_traits.hpp ../../../boost/re_detail/fileiter.hpp ../../../boost/re_detail/regex_compile.hpp ../../../boost/re_detail/regex_config.hpp ../../../boost/re_detail/regex_cstring.hpp ../../../boost/re_detail/regex_format.hpp ../../../boost/re_detail/regex_kmp.hpp ../../../boost/re_detail/regex_library_include.hpp ../../../boost/re_detail/regex_match.hpp ../../../boost/re_detail/regex_options.hpp ../../../boost/re_detail/regex_raw_buffer.hpp ../../../boost/re_detail/regex_split.hpp ../../../boost/re_detail/regex_stack.hpp ../../../boost/re_detail/regex_synch.hpp

all : $(DIRNAME)  $(DIRNAME) $(DIRNAME)/boost_regex ./$(DIRNAME)/libboost_regex.a

$(DIRNAME) :
	mkdir -p $(DIRNAME)

clean :  boost_regex_clean

install : all



########################################################
#
# section for libboost_regex.a
#
########################################################
$(DIRNAME)/boost_regex/c_regex_traits.o: ../src/c_regex_traits.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o $(DIRNAME)/boost_regex/c_regex_traits.o $(C1) $(CXXFLAGS) ../src/c_regex_traits.cpp

$(DIRNAME)/boost_regex/c_regex_traits_common.o: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o $(DIRNAME)/boost_regex/c_regex_traits_common.o $(C1) $(CXXFLAGS) ../src/c_regex_traits_common.cpp

$(DIRNAME)/boost_regex/cpp_regex_traits.o: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o $(DIRNAME)/boost_regex/cpp_regex_traits.o $(C1) $(CXXFLAGS) ../src/cpp_regex_traits.cpp

$(DIRNAME)/boost_regex/cregex.o: ../src/cregex.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o $(DIRNAME)/boost_regex/cregex.o $(C1) $(CXXFLAGS) ../src/cregex.cpp

$(DIRNAME)/boost_regex/fileiter.o: ../src/fileiter.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o $(DIRNAME)/boost_regex/fileiter.o $(C1) $(CXXFLAGS) ../src/fileiter.cpp

$(DIRNAME)/boost_regex/posix_api.o: ../src/posix_api.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o $(DIRNAME)/boost_regex/posix_api.o $(C1) $(CXXFLAGS) ../src/posix_api.cpp

$(DIRNAME)/boost_regex/regex.o: ../src/regex.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o $(DIRNAME)/boost_regex/regex.o $(C1) $(CXXFLAGS) ../src/regex.cpp

$(DIRNAME)/boost_regex/regex_debug.o: ../src/regex_debug.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o $(DIRNAME)/boost_regex/regex_debug.o $(C1) $(CXXFLAGS) ../src/regex_debug.cpp

$(DIRNAME)/boost_regex/regex_synch.o: ../src/regex_synch.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o $(DIRNAME)/boost_regex/regex_synch.o $(C1) $(CXXFLAGS) ../src/regex_synch.cpp

$(DIRNAME)/boost_regex/w32_regex_traits.o: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o $(DIRNAME)/boost_regex/w32_regex_traits.o $(C1) $(CXXFLAGS) ../src/w32_regex_traits.cpp

$(DIRNAME)/boost_regex/wide_posix_api.o: ../src/wide_posix_api.cpp $(ALL_HEADER)
	$(CXX) $(INCLUDES) -o $(DIRNAME)/boost_regex/wide_posix_api.o $(C1) $(CXXFLAGS) ../src/wide_posix_api.cpp

$(DIRNAME)/boost_regex : 
	mkdir -p $(DIRNAME)/boost_regex

boost_regex_clean :
	rm -f $(DIRNAME)/boost_regex/*.o

./$(DIRNAME)/libboost_regex.so : $(DIRNAME)/boost_regex/c_regex_traits.o $(DIRNAME)/boost_regex/c_regex_traits_common.o $(DIRNAME)/boost_regex/cpp_regex_traits.o $(DIRNAME)/boost_regex/cregex.o $(DIRNAME)/boost_regex/fileiter.o $(DIRNAME)/boost_regex/posix_api.o $(DIRNAME)/boost_regex/regex.o $(DIRNAME)/boost_regex/regex_debug.o $(DIRNAME)/boost_regex/regex_synch.o $(DIRNAME)/boost_regex/w32_regex_traits.o $(DIRNAME)/boost_regex/wide_posix_api.o
	$(LINKER) $(LDFLAGS) -o $(DIRNAME)/libboost_regex.so  $(DIRNAME)/boost_regex/c_regex_traits.o $(DIRNAME)/boost_regex/c_regex_traits_common.o $(DIRNAME)/boost_regex/cpp_regex_traits.o $(DIRNAME)/boost_regex/cregex.o $(DIRNAME)/boost_regex/fileiter.o $(DIRNAME)/boost_regex/posix_api.o $(DIRNAME)/boost_regex/regex.o $(DIRNAME)/boost_regex/regex_debug.o $(DIRNAME)/boost_regex/regex_synch.o $(DIRNAME)/boost_regex/w32_regex_traits.o $(DIRNAME)/boost_regex/wide_posix_api.o $(LIBS)

